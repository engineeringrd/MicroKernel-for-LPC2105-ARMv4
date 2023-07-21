/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Noviembre de 2022
* DESCRIPCIÓN: Definición del tipo de mensaje
*/
#include "mensaje_t.h"

mensaje_t crear_mensaje( uint8_t ID_msg,uint32_t msg, uint32_t time){
    mensaje_t mens;
    mens.ID_msg = ID_msg;
    mens.mensaje = msg;
    mens.timeStamp = time;
    return mens;
}
