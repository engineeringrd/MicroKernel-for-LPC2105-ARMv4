/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Octubre de 2022
* DESCRIPCIÓN: Definición de las funciones para utilizar el watchDog
*/

#ifndef __PH_WT_H__
#define __PH_WT__

/* Incializar el watchDog */
void WD_init(int sec);

/* Alimentar el watchDog */
void WD_feed (void);

#endif //PH_WT_H
