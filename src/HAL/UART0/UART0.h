/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Diciembre de 2022
* DESCRIPCIÓN: Definición de las funciones para la gestión serie
*/
#ifndef __UART0_H__
#define __UART0_H__


// Incializa la UART
void UART0_init(void);

// Obtiene el caracter introducido mediante la UART
char UART0_getChar(void);

// Envia un cracater a la UART
void UART0_sendChar(char c);

// Devuelve el tipo de interrupcion que se ha producido
int UART0_getInterrupt(void);

#endif
