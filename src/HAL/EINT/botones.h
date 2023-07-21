/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Noviembre de 2022
* DESCRIPCIÓN: Definición de los tipos botones
*/
#ifndef __INTERRUPCIONES_H__
#define __INTERRUPCIONES_H__

void inicializar_EINT(void);

void habilitar_EINT1(void);

void habilitar_EINT2(void);

void deshabilitar_EINT1(void);

void deshabilitar_EINT2(void);

int sigueValor_EINT1(void);

int sigueValor_EINT2(void);

int quitarValor_EINT1(void);

int quitarVlor_EINT2(void);

void bajar_eint1(void);

void bajar_eint2(void);

// Funciones de tratamiento de interrupciones para los botones
void boton1_ISR (void) __irq ;
void boton2_ISR (void) __irq ;

#endif
