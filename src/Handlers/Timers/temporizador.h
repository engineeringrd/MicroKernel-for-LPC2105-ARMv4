/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Octubre de 2022
* DESCRIPCIÓN: Defincion de las funciones para utilizar el temporizador
*/


#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_H
#include <inttypes.h>
// Programa un contador para que pueda ser utilizado.
void temporizador_iniciar(void);

// Inicia la cuenta de un contador de forma indefinida.
void temporizador_empezar(void);

/* Lee el tiempo que lleva contando el contador desde la última vez que se ejecuta
 * temporizador_empezar y lo devuelve en microsegundos. */
uint32_t temporizador_leer(void);

/* Detiene el contador y devuelve el tiempo (en microsegundos)
 * transcurrido desde que se ejecuto el temporizador_empezar. */
void temporizador_parar(void);

/* Programa el reloj para que encole un evento periódicamente, donde
 * el periodo se indica en ms. */
void temporizador_reloj(int periodo);

void temporizador_reloj_parar(void);

#endif
