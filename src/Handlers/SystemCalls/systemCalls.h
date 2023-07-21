/*
* AUTORES:     Raul Cosmin Daramus Raica 796682
*              Ibón Cañete Bielsa 776561
* ASIGNATURA:  30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			   Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA:       Noviembre de 2022
* DESCRIPCIÓN: Definición de las llamadas al sistema
*/

#ifndef PH_SYSTEMCALLS_H
#define PH_SYSTEMCALLS_H
#include <inttypes.h>

// Para leer el tiempo transcurrido en microsegundos utilizando el
// timer 1. Sustituye a la llamada timer1_leer() que ya no podrá ser invocada desde
// espacio de usuario.
uint32_t __swi(0) clock_getus (void);

// Para leer el tiempo transcurrido en segundos usando el real-time clock
uint32_t __swi(1) clock_gettime(void);

// Para activar sólo las interrupciones irq en el registro de estado
void __swi(0xFF) enable_fiq (void);

// Para desactivar sólo las interrupciones irq en el registro de estado
void __swi(0xFE) disable_fiq (void);

// Para activar interrupciones irq y fiq en el registro de estado.
void __swi(0xFD) enable_irq_fiq (void);

// Para desactivar interrupciones irq y fiq en el registro de estado.
void __swi(0xFC) disable_irq_fiq (void);

// Lee el bit IRQ del registro de estado para saber si
// las interrupciones están habilitadas o deshabilitadas (ver instrucción MRS. En A4.74 del manual de ARM)
uint32_t __swi(0xFB) read_IRQ_bit(void);

// Lee el bit FIQ del registro de estado para saber si
// las interrupciones están habilitadas o deshabilitadas (ver instrucción MRS. En A4.74 del manual de ARM)
uint32_t __swi(0xFA) read_FIQ_bit(void);


#endif //PH_SYSTEMCALLS_H
