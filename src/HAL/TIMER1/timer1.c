/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			   Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Octubre de 2022
* DESCRIPCIÓN: Implementación de las funciones para utilizar el timer1
*/
#include <LPC210X.H>                            // LPC21XX Peripheral Registers
#include "timer1.h"
#include "constantes.h"

static volatile uint32_t timer1_int_count = 0; // variable para contabilizar el numero de interrupciones

void timer1_ISR (void) __irq;    // generar interrupción Interrupt


void timer1_setup (void) {
    timer1_int_count = 0;
		T1MR0 = 149999;                   			// Interrumpe cada 0,05ms = 150.000-1 counts
    T1MCR = 3;                             // Genera una interrupción y resetea la cuenta cuando el valor de MRO es alcanzado
    T1TCR = ENABLE;                        // Activamos el TIMER1

    // configuración del IRQ slot number 1 del VIC para la interrupcion del Timer 1
	VICVectAddr1 = (unsigned long)timer1_ISR;          // Establecer la interrupción del vector en 0
	VICVectCntl1 = DEFAULT | 5; // 5 Es el numero del timers 1. (ver tabla 40 del LPC2105 user manual)
}

void timer1_init (void) {
    VICIntEnable = VICIntEnable | 0x00000020;
}

void timer1_stop (void){
    VICIntEnable = VICIntEnable & 0xFFFFFFDF;
    timer1_int_count = RESET;
}

void timer1_ISR (void) __irq {
    timer1_int_count++;
    T1IR = ENABLE;                              // Clear interrupt flag
    VICVectAddr = RESET;                       // Acknowledge Interrupt
}

uint32_t timer1_read_int_count(void){
	
	return (timer1_int_count * 10000)+ (T1TC/15);
};



