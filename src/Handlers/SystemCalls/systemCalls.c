/*
* AUTORES:     Raul Cosmin Daramus Raica 796682
*              Ibón Cañete Bielsa 776561
* ASIGNATURA:  30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			   Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA:       Diciembre de 2022
* DESCRIPCIÓN: Definición de las llamadas al sistema
*/

#include "systemCalls.h"
#include <inttypes.h>
#include "RTC.h"
#include "timer1.h"
static uint8_t *minutos, *segundos;
// Para leer el tiempo transcurrido en microsegundos utilizando el
// timer 1. Sustituye a la llamada timer1_leer() que ya no podrá ser invocada desde
// espacio de usuario.
uint32_t __SWI_0 (void) {
    return timer1_read_int_count();
}

// Para leer el tiempo transcurrido en segundos usando el real-time clock
uint32_t __SWI_1 (void) {
    
    RTC_leer(minutos, segundos);
	return 0;
}
