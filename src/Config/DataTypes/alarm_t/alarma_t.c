/*
* AUTORES:     Raul Cosmin Daramus Raica 796682
*              Ibón Cañete Bielsa 776561
* ASIGNATURA:  30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			   Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA:       Noviembre de 2022
* DESCRIPCIÓN: Definición del tipo alarma
*/
#include "alarma_t.h"
// Crea una alarma identificada por el id y iniciliza a 0
alarma_t crear_alarma(uint8_t id, uint32_t conf, int activada, int tiempoActual){
    alarma_t alarma;
    alarma.ID = id;
    alarma.configuracion = conf;
    alarma.activa = activada;
    alarma.tiempo = tiempoActual;
    return alarma;
}

