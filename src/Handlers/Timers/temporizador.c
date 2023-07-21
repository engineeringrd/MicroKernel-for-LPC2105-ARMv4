/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Octubre de 2022
* DESCRIPCIÓN: Implementación de las funciones para utilizar el temporizador
*/

#include "timer0.h"
#include "timer1.h"

void temporizador_iniciar(void){
    timer1_setup();
}

void temporizador_empezar(void){
    timer1_init();
}

uint32_t temporizador_leer(void){
    return timer1_read_int_count();
}

void temporizador_parar(void){
     timer1_stop();
}

void temporizador_reloj(int periodo){
    timer0_setup(periodo);
    timer0_init();
}

void temporizador_reloj_parar(void){
    timer0_stop();
}
