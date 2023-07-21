/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Octubre de 2022
* DESCRIPCIÓN: Definición de las funciones para utilizar el Real Time-Clock
*/


#ifndef PH_RTC_H
#define PH_RTC_H

#include <stdint.h>
void RTC_init(void);
void RTC_leer(uint8_t* minutos, uint8_t* segundos);

#endif //PH_RTC_H
