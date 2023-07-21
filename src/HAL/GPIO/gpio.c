/*
* AUTORES:     Raul Cosmin Daramus Raica 796682
*              Ibón Cañete Bielsa 776561
* ASIGNATURA:  30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			   			 Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA:       Noviembre de 2022
* DESCRIPCIÓN: Implementación de las funciones de la GPIO
*/
#include "gpio.h"
#include <LPC210X.H>

void GPIO_iniciar(void){
    // Inicializamos todos los pines
    //IODIR = 0x00000000;		
    PINSEL0 = 0x00000000; 
    PINSEL1 = 0x00000000;	
}

int generarMascara(int bitInicial,int numBits){

    int mascara = (1 << numBits) - 1;

    //Desplazamos la mascara hasta la posicion correspondiente
    return (mascara << bitInicial);  
}

int GPIO_leer(int bitInicial, int numBits){
 
    // Generamos la mascara
    int mascara = generarMascara(bitInicial,numBits);

    // Leemos
    int valor = IOPIN & mascara; 
	
    return (valor >> bitInicial);

}

void GPIO_escribir(int bitInicial, int numBits, int valor){

    // Generamos la mascara
    int mascara = generarMascara(bitInicial,numBits);
    
    // Generamos el valor desplazado
    int valorDesplazado = valor << bitInicial;
    
    // Generamos el valor negado
	int valorNegado = ~valorDesplazado & mascara;

    valorDesplazado = mascara & valorDesplazado;

   

    // Escribimos
    IOSET = IOSET | valorDesplazado;  
    // Limpiamos
    IOCLR = IOCLR | valorNegado;

}
void GPIO_marcar_entrada(int bitInicial,int numBits){
		
    // Generamos la mascara
    int mascara = generarMascara(bitInicial,numBits);

    // Negamos PRUEBA SI FUNCIONA ASI
    mascara = ~mascara; 

    //Marcamos los pines para entrada
    IODIR = IODIR & mascara; 
}


void GPIO_marcar_salida(int bitInicial,int numBits){

    // Generamos la mascara
    int mascara = generarMascara(bitInicial,numBits);

    //Marcamos los pines para salida
    IODIR = IODIR | mascara; 

}

void GPIO_clear_salida(int bit_inicial, int num_bits)
{

    // Generamos la mascara
    int mascara = generarMascara(bit_inicial,num_bits);

    //Limpiamos la salida
	IOCLR = IOCLR | mascara;
	
}


