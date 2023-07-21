/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Noviembre de 2022
* DESCRIPCIÓN: Definición de la cola de mensajes
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cola_mensajes.h"
#include "gestor_io.h"
#include "gestor_alarmas.h"
#include "gestor_interrupciones.h"
#include "systemCalls.h"


static volatile int tiempoInicio = 0;
static volatile int tiempoFinal = 0;
static volatile int tiempoMedio = 0;

struct ColaMensajes
{
    struct mensaje_t mensajes[MAX_SIZE_COLA_MENSAJES];     // array para almacenar elementos de la queue
    int maxsize;    // capacidad máxima de la queue
    int front;      // front apunta al elemento frontal en la queue (si lo hay)
    int rear;       // la parte trasera apunta al último elemento de la queue
    int size;       // capacidad actual de la queue
};

typedef struct ColaMensajes ColaMensajes;



static struct ColaMensajes colaMensajes;

void calcular_tiempoMedio(void){
    static int n = 0;
    n++;
    tiempoMedio = tiempoMedio + ((tiempoFinal - tiempoInicio) - tiempoMedio) / n;
}

int cola_size_mensajes(void) {
    return colaMensajes.size;
}
 
int cola_isEmpty_mensajes(void) {
    return !cola_size_mensajes();
}
 
mensaje_t cola_front_mensajes(void)
{
    if (cola_isEmpty_mensajes())
    {
        exit(EXIT_FAILURE);
    }
 
    return colaMensajes.mensajes[colaMensajes.front];
}
 
mensaje_t cola_desencolar_mensajes(void)
{
    tiempoFinal = clock_getus();
    G_ALARMA_reiniciarINACTIVIDAD();
    G_INTERRUPCIONES_disable();
    if (cola_isEmpty_mensajes())    // front == rear
    {
        exit(EXIT_FAILURE);
    }

    mensaje_t devolver = colaMensajes.mensajes[colaMensajes.front];
 
    colaMensajes.front = (colaMensajes.front + 1) % colaMensajes.maxsize;  // ColaMensajes circular
    colaMensajes.size--;
    calcular_tiempoMedio();
    G_INTERRUPCIONES_enable();
    return devolver;
    
}

void cola_inicializar_mensajes(void){
    colaMensajes.maxsize = MAX_SIZE_COLA_MENSAJES;
    colaMensajes.front = 0;
    colaMensajes.rear = -1;
    colaMensajes.size = 0;
}

void cola_encolar_mensajes(uint8_t ID_msg, uint32_t mensaje, uint32_t timeStamp){
    tiempoInicio = clock_getus();
    G_ALARMA_reiniciarINACTIVIDAD();
    G_INTERRUPCIONES_disable();    
    mensaje_t msg_nuevo = crear_mensaje(ID_msg,mensaje,timeStamp);
 
    if (cola_size_mensajes() == colaMensajes.maxsize)
    {
        G_IO_mostrarPIN_OVERFLOW(); // Encedemos el LED de PIN_OVERFLOW
        exit(EXIT_FAILURE);
    }
    
    colaMensajes.rear = (colaMensajes.rear + 1) % colaMensajes.maxsize;    // colaMensajes circular
    colaMensajes.mensajes[colaMensajes.rear] = msg_nuevo;
    colaMensajes.size++;
    G_INTERRUPCIONES_enable();
}




int cola_devolver_tiempoMedio_mensajes(void){
    return tiempoMedio ;
}
