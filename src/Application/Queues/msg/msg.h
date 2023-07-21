/*
* AUTORES:     Raul Cosmin Daramus Raica 796682
*              Ibón Cañete Bielsa 776561
* ASIGNATURA:  30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			   Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA:       Noviembre de 2022
* DESCRIPCIÓN: Definición de los tipos de mensaje
*/

#ifndef __MSG_H__
#define __MSG_H__
#include "stdint.h"

//#define SET_ALARMA 0 // Se ha pedido fijar una alarma

// Tipos de alarma
enum { 
		SET_ALARMA = 0,
    ALARMA_BOTON_1 = 1, // Programar de la alarma que comprueba si sigue pulsado EINT1
    ALARMA_BOTON_2 = 2, // Programar la alarma que comprueba si sigue pulsado EINT2
		ALARMA_TIME_OUT = 3, // Programar el timeoutç
		ALARMA_COLUMNA = 4, // Programar alarma que actualice la visualización de si la columna marcada está llena.
    ALARMA_LATIDO = 5, // Programar alarma que muestre el latido
    ALARMA_CONFIRMAR_JUGADA = 6, // Programar alarma para comprobar si no han cancelado la jugada
    ALARMA_INACTIVIDAD = 7, // Programar alarma para comprobar la inactividad del sistema
    MSG_COMANDO_CORRECTO = 8 // Se ha escrito un comando correcto
};

#endif

