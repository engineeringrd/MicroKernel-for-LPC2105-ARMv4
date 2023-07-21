/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Noviembre de 2022
* DESCRIPCIÓN: Definición de las funciones del gestor de energia
*/
#ifndef __GESTOR_ENERGIA_H__
#define __GESTOR_ENERGIA__


// Pone al procesador en modo "power_down"
// NOTA: El Watchdog no puede despertar al procesador del modo "power_down"
void G_ENERGIA_power_down_mode (void);

// Pone al procesador en modo "idle"
void G_ENERGIA_idle_mode (void);

#endif
