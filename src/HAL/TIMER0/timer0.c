/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Octubre de 2022
* DESCRIPCIÓN: Implementación de las funciones para utilizar el timer0
*/
#include <LPC210X.H>                            // LPC21XX Peripheral Registers
#include "timer0.h"
#include "eventos.h"
#include "cola_async.h"
#include "constantes.h"
#include "gestor_interrupciones.h"
#include <inttypes.h>

static int timer0_int_count;

extern void timer0_ISR (void) __irq;    // Funcion de interrupción

void timer0_setup(int periodo) {

    int ciclos = calcularCiclos(periodo);
    timer0_int_count = 0;
		T0MR0 = ciclos;                 // Interrumpe cada 0,05ms = 150.000-1 counts
    T0MCR = 3;                     // Generates an interrupt and resets the count when the value of MR0 is reached
    T0TCR = ENABLE;                // Timer0 Enable

    // configuration of the IRQ slot number 0 of the VIC for Timer 0 Interrupt
	//VICVectAddr0 = (unsigned long)timer0_ISR;          // set interrupt vector in 0
    // 0x20 bit 5 enables vectored IRQs. 
	// 4 is the number of the interrupt assigned. Number 4 is the Timer 0 (see table 40 of the LPC2105 user manual  
	VICVectCntl0 = DEFAULT | 4;
	//vic de fiq o irq
	VICIntSelect = VICIntSelect | 0x00000010;

}

void timer0_init (void) {
    VICIntEnable = VICIntEnable | 0x00000010;                  // Enable Timer0 Interrupt
}

void timer0_ISR(void) __irq {
    cola_encolar_eventos(EV_TEMPORIZADOR_PERIODICO,timer0_int_count,NO_AUX_DATA); // Encolamos el evento, (Se corresponda con lo eventos.h definidos)
    T0IR = ENABLE;                              // Clear interrupt flag
    VICVectAddr = RESET;                            // Acknowledge Interrupt
}

void timer0_stop (void){
    VICIntEnable = VICIntEnable & 0xFFFFFFEF;
    timer0_int_count = RESET;
	T0TCR = DISABLE;  
}


int calcularCiclos(int periodo){
	return (periodo * PLC_CLOCK) - 1; // (Se resta uno ya que empieza desde 0)
}
