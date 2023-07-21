/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Noviembre de 2022
* DESCRIPCIÓN: Definición del tipo de evento
*/
#ifndef EVENTO_T_H
#define EVENTO_T_H


#include <stdint.h>

struct evento_t
{
    uint8_t ID_evento; // Definido en eventos.h
    uint32_t veces; 
    uint32_t auxData; 
};

typedef struct evento_t evento_t;

/* Funcion para crear un tipo de dato evento */
evento_t crear_evento(uint8_t id,  uint32_t veces, uint32_t data);

#endif // EVENTO_T_H
