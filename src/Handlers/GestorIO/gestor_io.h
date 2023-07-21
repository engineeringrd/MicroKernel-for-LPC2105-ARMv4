/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Noviembre de 2022
* DESCRIPCIÓN: Definición de las funciones del gestor de IO
*/
#ifndef __GESTOR_IO_H__
#define __GESTOR_IO__



void G_IO_inicializar (void);

void G_IO_mostrarTurno(int jugador);

void G_IO_mostrarJugadaRealizada(void);

void G_IO_clearJugadaRealizada(void);

void G_IO_mostrarJugadaNoValida(void);

void G_IO_clearJugadaNoValida(void);

void G_IO_mostrarFinalPartida(int causa, int jugador);

void G_IO_mostrarPIN_OVERFLOW(void);

void G_IO_encenderLED_ERROR_BUFFER(void);

void G_IO_apagarLED_ERROR_BUFFER(void);

void G_IO_mostrarLatido(void);

void G_IO_clearAll(void);

int G_IO_columnaSeleccionada(void);

void G_IO_mostrar_leyenda(void);

void G_IO_enviar_tablero(int jugador);

void G_IO_nueva_partida(void);

void G_IO_mensajeEmpezar(void);

void G_IO_mostrar_paraCancelar(void);

void G_IO_mostrar_cancelada(void);

void G_IO_mostrarEsperarAEscribir(void);



#endif
