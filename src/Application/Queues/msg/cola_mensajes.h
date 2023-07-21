/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Noviembre de 2022
* DESCRIPCIÓN: Implementacion de la cola de mensajes
*/
#ifndef COLA_MENSAJES_H
#define COLA_MENSAJES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mensaje_t.h"

#define MAX_SIZE_COLA_MENSAJES 32




/* ---- PRINCIPALES ---- */
// Inicializa la cola de eventos
void cola_inicializar_mensajes(void);

// Encola un mensaje
void cola_encolar_mensajes(uint8_t ID_msg, uint32_t mensaje, uint32_t timeStamp);

// Función de utilidad para sacar de la queue el elemento frontal
mensaje_t cola_desencolar_mensajes(void);

// Función de utilidad para verificar si la queue está vacía o no
int cola_isEmpty_mensajes(void);

// Devuelve el tiempo medio desde que se encola un menaje hasta que se atiende
int cola_devolver_tiempoMedio_mensajes(void);
 


#endif // COLA_MENSAJES_H
