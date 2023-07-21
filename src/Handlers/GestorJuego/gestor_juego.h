/*
 * AUTORES:     Raul Cosmin Daramus Raica 796682
 *              Ib�n Ca�ete Bielsa 776561
 * ASIGNATURA:  30220 Proyecto Hardware del Grado de Ingenier�a en Inform�tica
 *			   Escuela de Ingenier�a y Arquitectura - Universidad de Zaragoza
 * FECHA:       Noviembre de 2022
 * DESCRIPCI�N: Funciones relativas a la gestion del juego
 */

/* Causas por la que termina la partida*/
#define CAUSA_VICTORIA 0
#define CAUSA_EMPATE 1
#define CAUSA_REINICIAR 2 
#define CAUSA_END 3


 
void G_JUEGO_iniciarJuego(void);

void G_JUEGO_inicializarTurno(void);

void G_JUEGO_reiniciarPartida(void);

void G_JUEGO_realizarJugada(int columna);

void G_JUEGO_comprobarColumna(void);

void G_JUEGO_finalizarPartida(int causa, int jugador);

void G_JUEGO_partidaNueva(void);

void G_JUEGO_confirmarJugada(void);

void G_JUEGO_cancelarJugada(void);
