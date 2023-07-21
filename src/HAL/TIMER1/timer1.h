/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Octubre de 2022
* DESCRIPCIÓN: Definición de las funciones para utilizar el timer1
*/

#include <inttypes.h>
// Configura el timer1
void timer1_setup(void);

// Inicializa el timer1
void timer1_init(void);

// Para el timer1
void timer1_stop(void);

// Devuelve el numero de veces que ha sido ejecutada la interrupción
uint32_t timer1_read_int_count(void);
