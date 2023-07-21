/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Octubre de 2022
* DESCRIPCIÓN: Definición de las funciones para la gestión de la alarma
*/
#ifndef __GESTOR_ALARMAS_H__
#define __GESTOR_ALARMAS_H__

#include "alarma_t.h"
#include "mensaje_t.h"

void crearAlarmaConfirmar(void);
// Inicializa las alarmas del sistema
void G_ALARMA_inicializar(void);

// Función que se ofrece al Scheduler para configurar alarmas a la que se le pasa
// un mensaje con la nueva alarma a programar
void G_ALARMA_Set_Alarma(mensaje_t msg);

// Disparar la alarma encolando en la cola de mensajes
// el mensaje asociado a la alarma
void G_ALARMA_dispararAlarma(alarma_t alarma);

// Cada vez que le llegue el evento del temporizador periódico se comprueba si hay que disparar
// el mensaje asociado a alguna de las alarmas programadas pendientes. Si lo hay se dispararán y
// se cancelará la alarma si no es periódica.
void G_ALARMA_gestionarAlarmas(void);

// Reinicia la alarma TIMEOUT 
void G_ALARMA_reiniciarTIMEOUT(void);

void G_ALARMA_reiniciarINACTIVIDAD(void);

int alarmaDisparada(void);

#endif
