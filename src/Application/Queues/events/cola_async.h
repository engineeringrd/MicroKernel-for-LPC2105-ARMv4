/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Noviembre de 2022
* DESCRIPCIÓN: Definición de la cola de eventos
*/
#ifndef COLA_ASYN_H
#define COLA_ASYN_H

#include "evento_t.h"


// Inicializa la cola de eventos
void cola_inicializar_eventos(void);

// Encola un evento
void cola_encolar_eventos(uint8_t ID_evento, uint32_t veces, uint32_t auxData);

// Función de utilidad para verificar si la queue está vacía o no
int cola_isEmpty_eventos(void);

// Función de utilidad para sacar de la queue el elemento frontal
evento_t cola_desencolar_eventos(void);



#endif // COLA_ASYN_H
