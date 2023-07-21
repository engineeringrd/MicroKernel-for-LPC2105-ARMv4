/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Octubre de 2022
* DESCRIPCIÓN: Definición de las funciones para la gestión serie
*/
#ifndef __GESTOR_SERIE_H__
#define __GESTOR_SERIE_H__

// comandos
#define END 9 //Acabar la partida: #END!
#define NEW 8 //Nueva partida: #NEW!

#define C_1 1 //jugada: #C!
#define C_2 2 //jugada: #C!
#define C_3 3 //jugada: #C!
#define C_4 4 //jugada: #C!
#define C_5 5 //jugada: #C!
#define C_6 6 //jugada: #C!
#define C_7 7

void G_SERIE_init(void);
void G_SERIE_gestion_char(int c);
int G_SERIE_comandoCorrecto(void);
void G_SERIE_enviar_array(char string[]);
int G_SERIE_estaEscribiendo(void);
void G_SERIE_continuar_envio(void);
void G_SERIE_gestion_envio(void);
int G_SERIE_comprobarComando(void);
#endif
