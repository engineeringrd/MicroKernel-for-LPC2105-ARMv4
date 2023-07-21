/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Octubre de 2022
* DESCRIPCIÓN: Definición de las funciones para utilizar el watchDog
*/

#include <LPC210x.H>                       /* LPC210x definitions */
#include "gestor_interrupciones.h"
#include "WT.h"

void WD_feed (void) {	

	G_INTERRUPCIONES_disable();
	WDFEED = 0xAA;						   
	WDFEED = 0x55;  
	G_INTERRUPCIONES_enable();

}

void WD_init(int sec){
	if( WDMOD & 0x04 ) {					   /* Check for watchdog time out. El bit 2 se activa si se ha disparado el watchdog*/
		WDMOD &= ~0x04;						   /* Clear time out flag           */
  	}
	//WDTC = sec * 4 * 256
	WDTC  = sec*4*3750000;						   // Set watchdog time out value
	WDMOD = 0x03;    /* Enable watchdog timer (bit 0) and reset (bit 1).  */   
	WD_feed();                        
}

