/*
* AUTORES:     Raul Cosmin Daramus Raica 796682
*              Ibón Cañete Bielsa 776561
* ASIGNATURA:  30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			   Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA:       Noviembre de 2022
* DESCRIPCIÓN: Definición de los tipos de eventos
*/

#ifndef __EVENTOS_H__
#define __EVENTOS_H__
#include "stdint.h"


enum {
    EV_TEMPORIZADOR_PERIODICO = 0,// El evento ha sido pedido por timer0
    EV_BOTON_1 = 1, // Se ha pulsado el boton EINT1
    EV_BOTON_2 = 2, // Se ha pulsado el boton EINT2
    EV_ENTRADA_P_SERIE = 3, // Se ha escrito nuevo caracter en la UART
    EV_SALIDA_P_SERIE = 4, // TODO
    EV_CONFIRMAR = 5
};


#endif
