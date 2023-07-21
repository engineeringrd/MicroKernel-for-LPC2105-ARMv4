/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Octubre de 2022
* DESCRIPCIÓN: Definicion del tipo de dato Alarma
*/


#ifndef PH_ALARM_H
#define PH_ALARM_H
#include <stdint.h>

#include "constantes.h"

//Tipo de dato alarma
struct alarma_t{

    // Identificador de la alarma
   uint8_t ID;

    // 8 bits de mayor peso el mensaje a generar cuando venzca la alarma,
    // 1 bit indica si es alarma periódica o no,
    // 23 bits restantes los milisegundos de retardo
    uint32_t configuracion;

    //Indica si la alarma esta activada o no 1 si sí 0 si no
    int activa;

    //Indica el tiempo que ha pasado en ms
    int tiempo;
};
typedef struct alarma_t alarma_t;

// Crea una alarma identifiada por el id y iniciliza a 0
alarma_t crear_alarma(uint8_t id, uint32_t conf, int activada, int tiempoActual);

// Devuelve el ID del evento a disparar
__inline static uint8_t obtenerID(uint32_t configuracion) {
    return (configuracion & 0xff000000) >> 24; // Desplazo 24 bits para quedarme con los 8 y obtener el ID
}

// Devuelve el ID del evento a disparar
__inline static uint8_t obtenerMensaje(alarma_t alarma) {
    return (alarma.configuracion & 0xff000000) >> 24; // Desplazo 24 bits para quedarme con los 8 y obtener el ID
}
// Devuelve los bits de retardo de la alarma
__inline static uint32_t obtenerRetardo(uint32_t configuracion) {
    return (configuracion & 0x007fffff);
}
// Devuelve el bit que indican si una alarma es periodica o no
__inline static int esPeriodica(uint32_t configuracion) {
    return (configuracion & 0x00800000) == 0x00800000;
}



/* ------------------------------- */

#endif //PH_ALARM_H
