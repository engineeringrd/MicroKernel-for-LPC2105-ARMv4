/*
* AUTORES:     Raul Cosmin Daramus Raica 796682
*              Ibón Cañete Bielsa 776561
* ASIGNATURA:  30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			   Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA:       Noviembre de 2022
* DESCRIPCIÓN: Espeficicacion de las funciones de la GPIO
*/
#ifndef GESTOR_GPIO_H
#define GESTOR_GPIO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

// Permite emplear el GPIO y debe ser invocada antes de poder llamar al resto de funciones de la biblioteca.
void GPIO_iniciar(void);			

// bit_inicial indica el primer bit a leer.
// num_bits indica cuántos bits queremos leer. 
// La función devuelve un entero con el valor de los bits indicados.
int GPIO_leer(int bitInicial, int numBits);

// Similar al anterior, pero en lugar
// de leer escribe en los bits indicados el valor (si valor no puede
// representarse en los bits indicados se escribirá los num_bits menos
// significativos a partir del inicial)
void GPIO_escribir(int bitInicial, int numBits, int valor);

// Los bits indicados se utilizarán como pines de entrada.
void GPIO_marcar_entrada(int bitInicial,int numBits);

//Los bits indicados se utilizarán como pines de salida.
void GPIO_marcar_salida(int bitInicial,int numBits);

// Limpia los bits indicados
void GPIO_clear_salida(int bit_inicial, int num_bits);

#endif // GESTOR_GPIO_H
