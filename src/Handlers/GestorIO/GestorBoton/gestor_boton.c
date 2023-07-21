/*
* AUTORES:     Raul Cosmin Daramus Raica 796682
*              Ibón Cañete Bielsa 776561
* ASIGNATURA:  30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			   Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA:       Noviembre de 2022
* DESCRIPCIÓN: Implementacion de las funciones del gestor de boton
*/
#include "gestor_boton.h"
#include "cola_mensajes.h"
#include "configuraciones.h"
#include "eventos.h"
#include "msg.h"
#include "constantes.h"
#include "evento_t.h"
#include "temporizador.h"
#include "botones.h"
#include "cola_async.h"
#include "gestor_alarmas.h"
#include <LPC210X.H>



#define PROCESANDO 0
#define NO_PULSADO 1


struct boton_t{
    int estado; // Procesando o no pulsado
    int hayNuevaPulsacion; // TRUE o FALSE
    int vecesPulsado; // numero de veces que se ha pulsado
    
};
typedef struct boton_t boton_t;



// Constructor
boton_t crear_Boton(int estado, int hayNuevaPulsacion, int vecesPulsado){
	boton_t boton;
	boton.estado = estado;
	boton.hayNuevaPulsacion = hayNuevaPulsacion;
	boton.vecesPulsado = vecesPulsado;
	return boton;
}

// Botones
static boton_t boton1;
static boton_t boton2;


/* BOTONES */
void G_BOTON_inicializar(void) {

    // Inicializamos el estado del boton a no pulsado
    boton1 = crear_Boton(NO_PULSADO,FALSE,0);
    boton2 = crear_Boton(NO_PULSADO,FALSE,0); 

    //Se habilita las interrumpciones EINT1 Y EINT2 para permitir pulsar los botones
    inicializar_EINT();

}
int G_BOTON_getVecesPulsadoBoton1(void){
    return boton1.vecesPulsado;
}

int G_BOTON_getVecesPulsadoBoton2(void){
    return boton2.vecesPulsado;
}
void G_BOTON_actualizar_boton1(void){
	 //bajar boton (EINT) | 2  el otro 4
		bajar_eint1();
		// Si y solo si NO sigue pulsada se volverá a
		//habilitar la interrupción de EINT1 
		if( sigueValor_EINT1() == FALSE ){
				G_BOTON_despulsar_boton1(); // Actualizamos la informacion
				habilitar_EINT1();
		}
    
}

void G_BOTON_actualizar_boton2(void){
		bajar_eint2();
    // Si y solo si NO sigue pulsada se volverá a
    //habilitar la interrupción de EINT2
    if( sigueValor_EINT2() == FALSE ){
        G_BOTON_despulsar_boton2();
        habilitar_EINT2();
    }
}


void G_BOTON_pulsar_boton1(void){
   boton1.estado = PROCESANDO;
   boton1.hayNuevaPulsacion = TRUE;
   boton1.vecesPulsado = boton1.vecesPulsado + 1;

}

void G_BOTON_pulsar_boton2(void){
    boton2.estado = PROCESANDO;
    boton2.hayNuevaPulsacion = TRUE;
    boton2.vecesPulsado = boton2.vecesPulsado + 1;
}

void G_BOTON_despulsar_boton1(void){
    boton1.estado = NO_PULSADO;
    boton1.hayNuevaPulsacion = FALSE;
   
}

void G_BOTON_despulsar_boton2(void){
    boton2.estado = NO_PULSADO;
    boton2.hayNuevaPulsacion = FALSE;
}
