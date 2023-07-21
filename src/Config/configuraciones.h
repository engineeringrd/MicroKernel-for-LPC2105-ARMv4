/*
* AUTORES:     Raul Cosmin Daramus Raica 796682
*              Ib�n Ca�ete Bielsa 776561
* ASIGNATURA:  30220 Proyecto Hardware del Grado de Ingenier�a en Inform�tica
*			   Escuela de Ingenier�a y Arquitectura - Universidad de Zaragoza
* FECHA:       Noviembre de 2022
* DESCRIPCI�N: Definici�n de los tipos de configuracion de alarma
*/

#ifndef __CONF_H__
#define __CONF_H__

enum{ 
    CONFIG_BOTON_1 = 0x0180000A,
    CONFIG_BOTON_2 = 0x0280000A,
    CONFIG_TIME_OUT = 0x03802710,
    CONFIG_COLUMNA = 0x04800064,
    CONFIG_LATIDOS = 0x058000FA,
    CONFIG_ALARMA_CONFIRMAR_JUGADA = 0x060003E8,
    CONFIG_ALARMA_ALARMA_INACTIVIDAD = 0x07800FFF
};


#endif
