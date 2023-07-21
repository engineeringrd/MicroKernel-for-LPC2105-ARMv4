/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Noviembre de 2022
* DESCRIPCIÓN: Definición del tipo de mensaje
*/
#ifndef MENSAJE_T_H
#define MENSAJE_T_H

#include <stdint.h>

struct mensaje_t
{
    uint8_t ID_msg; // Definido en msg.h
    uint32_t mensaje; // Por ejemplo la alarma a disparar, definido en alarmas.h 
    uint32_t timeStamp; // Marca de tiempo en que se genero el mensaje


};
typedef struct mensaje_t mensaje_t;

/* Funcion para crear un tipo de dato mensaje */
mensaje_t crear_mensaje( uint8_t ID_msg,uint32_t msg, uint32_t time);

#endif // MENSAJE_T_H
