/*
* AUTORES:     Raul Cosmin Daramus Raica 796682
*              Ibón Cañete Bielsa 776561
* ASIGNATURA:  30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			   Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA:       Noviembre de 2022
* DESCRIPCIÓN: Implementacion de los tipos botones
*/
#include <LPC210X.H>

#include "botones.h"
#include "msg.h"
#include "gestor_boton.h"
#include "gestor_alarmas.h"
#include "eventos.h"
#include "constantes.h"
#include "configuraciones.h"
#include "cola_async.h"

#include "gestor_interrupciones.h"


/* CONSTANTES DE EINT1*/
enum {
  EINT1_vic = 0x00008000, // bits para el VIC del EINT1
  EINT1_extint = 0x02 // bits para el EXTINT del EINT1
};

/* CONSTANTES DE EINT2*/
enum{
   EINT2_vic = 0x00010000,// bits para el VIC del EINT2
   EINT2_extint = 0x04 // bits para el EXTINT del EINT2
};

void inicializar_EINT(void){

    // Limpia flags de interrupción que contienen EXTINT1 y EXTINT2 (Ver tabla 10 del LPC2105 user manual)
    //EXTINT = EINT1_extint + EINT2_extint; 
		EXTINT = EINT1_extint + EINT2_extint;
    // Se conecta a los Pines del sistema para poder usar EINT1 y EINT2 (Ver seccion 7.2.1 del LPC2105 user manual)
    PINSEL0 = PINSEL0 & 0x0FFFFFFF;				// Hacemos un clear de los bits que vamos a utilizar
		PINSEL0 = PINSEL0 | 0xA0000000;				// Selecionamos EINT1 Y EINT2

    // Configuracion del IRQ del VIC para EINT1_ISR y EINT2_ISR 
    VICVectAddr2 = (unsigned long)boton1_ISR; 
    VICVectAddr3 = (unsigned long)boton2_ISR;
    
    VICVectCntl2 = VICVectCntl2 & 0xFFFFFFC0; // Hacemos un clear de los bits que vamos a utilizar
    VICVectCntl2 = DEFAULT | 15; // 15 Es el numero del EINT1  (ver tabla 40 del LPC2105 user manual)
    
		VICVectCntl3 = VICVectCntl3 & 0xFFFFFFC0; // Hacemos un clear de los bits que vamos a utilizar
    VICVectCntl3 = DEFAULT | 16; // 16 Es el numero del EINT2  (ver tabla 40 del LPC2105 user manual)

    // Habilitamos las interrupciones EXTINT1 y EXTINT2
    habilitar_EINT1();
    habilitar_EINT2();
}

void habilitar_EINT1(void){

    //Habilitamos la interrupcion EXTINT1
    VICIntEnable = VICIntEnable | EINT1_vic;

}

void habilitar_EINT2(void){

    //Habilitamos la interrupcion EXTINT2
    VICIntEnable = VICIntEnable | EINT2_vic;
    
}

void deshabilitar_EINT1(void){

    // Deshabilitamos las interrupciones de EINT1
    VICIntEnClr = VICIntEnClr | EINT1_vic; 
 
    // Limpiamos la interrupción EINT1
    EXTINT =  EXTINT | EINT1_extint;  
		VICVectAddr = RESET;

}

void deshabilitar_EINT2(void){

    // Deshabilitamos las interrupciones de EINT2
    VICIntEnClr = VICIntEnClr | EINT2_vic; 
 
    // Limpiamos la interrupción EINT2
		EXTINT = EXTINT | EINT2_extint;
		
		VICVectAddr = RESET;
    
}
void bajar_eint1(void){
	EXTINT = EXTINT | EINT1_extint;
}

void bajar_eint2(void){
	EXTINT = EXTINT | EINT2_extint;
}

int sigueValor_EINT1(void){
   	if( (EXTINT & EINT1_extint) == EINT1_extint ) return TRUE;
		return FALSE;
}

int sigueValor_EINT2(void){
    if( (EXTINT & EINT2_extint) == EINT2_extint ) return TRUE;
		return FALSE;
}

void boton1_ISR (void) __irq {
	  
    G_ALARMA_reiniciarTIMEOUT();
    
    // Deshabilitamos las interrupciones
    deshabilitar_EINT1();

    // Ha habido pulsacion
    G_BOTON_pulsar_boton1();

    // Encolar evento de pulsacion
    cola_encolar_eventos(EV_BOTON_1, G_BOTON_getVecesPulsadoBoton1(), CONFIG_BOTON_1);


}

void boton2_ISR (void) __irq {
	
  G_ALARMA_reiniciarTIMEOUT();

	// Deshabilitamos las interpciones
    deshabilitar_EINT2();

    // Ha habido pulsacion
    G_BOTON_pulsar_boton2();

    // Encolar evento de pulsacion
    cola_encolar_eventos(EV_BOTON_2, G_BOTON_getVecesPulsadoBoton2(), CONFIG_BOTON_2);

}
