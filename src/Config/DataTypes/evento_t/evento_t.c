/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Noviembre de 2022
* DESCRIPCIÓN: Definición del tipo de evento
*/
#include "evento_t.h"


evento_t crear_evento(uint8_t id,  uint32_t veces, uint32_t data){
    evento_t evento;
    evento.ID_evento = id;
    evento.veces = veces;
    evento.auxData = data;
 
    return evento;
}
