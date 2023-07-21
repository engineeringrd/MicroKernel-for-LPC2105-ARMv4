/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Octubre de 2022
* DESCRIPCIÓN: Definición de las funciones para utilizar el timer0
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Configura el timer0
void timer0_setup(int PERIODO);

// Inicializa el timer0
void timer0_init (void);


// Para el timer0 
void timer0_stop (void);

// Devuelve el numero de ciclos para configurar el timer 0 para que interrumpa cada "periodo" ms
int calcularCiclos(int periodo);
