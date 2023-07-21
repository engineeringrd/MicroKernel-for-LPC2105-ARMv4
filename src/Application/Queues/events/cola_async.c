/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Noviembre de 2022
* DESCRIPCIÓN: Implementación de la cola de eventos
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cola_async.h"
#include "gestor_io.h"
#include "gestor_alarmas.h"
#include "gestor_interrupciones.h"

#define MAX_SIZE_COLA_EVENTOS 32 // Tamaño maximo de la cola de eventos

struct ColaEventos
{
    struct evento_t eventos[MAX_SIZE_COLA_EVENTOS];     // array para almacenar elementos de la queue
    int maxsize;    // capacidad máxima de la queue
    int front;      // front apunta al elemento frontal en la queue (si lo hay)
    int rear;       // la parte trasera apunta al último elemento de la queue
    int size;       // capacidad actual de la queue
};

typedef struct ColaEventos ColaEventos;

static struct ColaEventos colaEventos;


int cola_size_eventos(void) {
    return colaEventos.size;
}
 

int cola_isEmpty_eventos(void) {
    return !cola_size_eventos();
}
 
evento_t cola_front_eventos(void)
{
    if (cola_isEmpty_eventos())
    {
        exit(EXIT_FAILURE);
    }
 
    return colaEventos.eventos[colaEventos.front];
}
 
evento_t cola_desencolar_eventos(void)
{
    G_ALARMA_reiniciarINACTIVIDAD();
     G_INTERRUPCIONES_disable();
    
    if (cola_isEmpty_eventos())    // front == rear
    {
        exit(EXIT_FAILURE);
    }
    evento_t devolver = colaEventos.eventos[colaEventos.front];
    colaEventos.front = (colaEventos.front + 1) % colaEventos.maxsize;  // ColaEventos circular
    colaEventos.size--;

    G_INTERRUPCIONES_enable();
    return devolver;


}

void cola_inicializar_eventos(void){
    colaEventos.maxsize = MAX_SIZE_COLA_EVENTOS;
		colaEventos.front = 0;
    colaEventos.rear = -1;
    colaEventos.size = 0 ;
}

void cola_encolar_eventos(uint8_t ID_evento, uint32_t veces, uint32_t auxData){
    G_ALARMA_reiniciarINACTIVIDAD();

     G_INTERRUPCIONES_disable();
        
    evento_t dato_nuevo = crear_evento(ID_evento,veces,auxData);
    
    if (cola_size_eventos() == colaEventos.maxsize)
    {
        G_IO_mostrarPIN_OVERFLOW(); // Encedemos el LED de PIN_OVERFLOW
        exit(EXIT_FAILURE);
    }
    
    colaEventos.rear = (colaEventos.rear + 1) % colaEventos.maxsize;    // ColaEventos circular
    colaEventos.eventos[colaEventos.rear] = dato_nuevo;
    colaEventos.size++;

     G_INTERRUPCIONES_enable();
   
}

