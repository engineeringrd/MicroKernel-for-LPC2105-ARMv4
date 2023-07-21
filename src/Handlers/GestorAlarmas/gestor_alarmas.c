/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Octubre de 2022
* DESCRIPCIÓN: Implementación de las funciones para la gestión de la alarma
*/

#include <stdint.h>
#include "constantes.h"
#include "gestor_alarmas.h"
#include "cola_async.h"
#include "eventos.h"
#include "cola_mensajes.h"
#include "msg.h"
#include "alarma_t.h"
#include "temporizador.h"
#include "configuraciones.h"
#include "systemCalls.h"


#define NUM_ALARMAS 8 // MAXIMO NUMERO DE ALARMAS
static alarma_t alarmas[NUM_ALARMAS]; // Vector que guarda las alarmas
static int disparada = FALSE;

void G_ALARMA_inicializar(void){

    // Se utiliza una alarma al comenzar la ejecución con periodo de 10 segundos.
    // Si hay un cambio se reinicia la alarma, si no hay y vence se pone el procesador en power_down.
    alarma_t alarma3 = crear_alarma(ALARMA_TIME_OUT,CONFIG_TIME_OUT,ENABLE, clock_getus());
    //cola_encolar_mensajes(SET_ALARMA,CONFIG_TIME_OUT,temporizador_leer());
    
    // Se utiliza una alarma para monitorizar la pulsación de EINT1 cada 10ms
    alarma_t alarma1 = crear_alarma(ALARMA_BOTON_1,CONFIG_BOTON_1,DISABLE, (clock_getus()/1000));
   
    // Se utiliza una alarma para monitorizar la pulsación de EINT2 cada 10ms
    alarma_t alarma2 = crear_alarma(ALARMA_BOTON_2,CONFIG_BOTON_2,DISABLE, (clock_getus()/1000));
    
    //Se programará una alarma periódica para que 10 veces por segundo se actualice la visualización de si la columna marcada está llena.
    alarma_t alarma4 = crear_alarma(ALARMA_COLUMNA,CONFIG_COLUMNA,DISABLE,(clock_getus()/1000));
    cola_encolar_mensajes(SET_ALARMA,CONFIG_COLUMNA,(clock_getus()/1000));
    
    alarma_t alarma5 = crear_alarma(ALARMA_LATIDO,CONFIG_LATIDOS,DISABLE,(clock_getus()/1000));
    cola_encolar_mensajes(SET_ALARMA,CONFIG_LATIDOS,(clock_getus()/1000));
    
    alarma_t alarma6 = crear_alarma(ALARMA_CONFIRMAR_JUGADA,CONFIG_ALARMA_CONFIRMAR_JUGADA,DISABLE,(clock_getus()/1000));


    alarma_t alarma7 = crear_alarma(ALARMA_INACTIVIDAD,CONFIG_ALARMA_ALARMA_INACTIVIDAD,ENABLE,(clock_getus()/1000));
    //cola_encolar_mensajes(SET_ALARMA,CONFIG_ALARMA_ALARMA_INACTIVIDAD,clock_getus());


    alarmas[ALARMA_BOTON_1] = alarma1;
    alarmas[ALARMA_BOTON_2] = alarma2;
    alarmas[ALARMA_TIME_OUT] = alarma3;
    alarmas[ALARMA_COLUMNA] = alarma4;
    alarmas[ALARMA_LATIDO] = alarma5;
    alarmas[ALARMA_CONFIRMAR_JUGADA] = alarma6;
    alarmas[ALARMA_INACTIVIDAD] = alarma7;
}

void crearAlarmaConfirmar(void){
    cola_encolar_eventos(EV_CONFIRMAR,0,CONFIG_ALARMA_CONFIRMAR_JUGADA);
    //cola_encolar_mensajes(SET_ALARMA,CONFIG_ALARMA_CONFIRMAR_JUGADA,temporizador_leer());
}

// Devuelve si existe la alarma en el sistema true y su indice 0 no 1 si
int existeAlarma(alarma_t alarma){

    int existe = FALSE;
    int indice = 0;
    int i = 0;
    while(i < NUM_ALARMAS && existe == FALSE){
        if(alarmas[i].ID == alarma.ID ){
            existe = TRUE;
            indice = i;
        }
        i++;
    }
    return indice;
}


void G_ALARMA_Set_Alarma(mensaje_t msg){
    
	int indice = 0;

    //Extaemos del mensaje con la informacion de la nueva alarma
    uint32_t configuracion = msg.mensaje;

    uint8_t ID_MSG = obtenerID(configuracion);
	
    cola_encolar_mensajes(ID_MSG, configuracion, clock_getus());
    

    // Creamos la alarma con la nueva configuracion
    alarma_t nuevaAlarma = crear_alarma(ID_MSG, configuracion, DISABLE,(clock_getus()/1000));

    // Si y solo si existe el tipo de alarma registrada en el sistema se modificara
    indice = existeAlarma(nuevaAlarma);
	
    if( indice != FALSE){

        //Reprogramar
        alarmas[indice] = nuevaAlarma;

        // Activar si y solo si el retardo no es 0
        if(obtenerRetardo(alarmas[indice].configuracion) != 0){
            alarmas[indice].activa = ENABLE;
        }
    }
}



void G_ALARMA_dispararAlarma(alarma_t alarma){
    
    // Encolar el mensaje de que se ha disparado una alarma 
    uint8_t ID_MSG = obtenerMensaje(alarma);
	uint32_t tiempo = clock_getus()/1000;
    cola_encolar_mensajes(ID_MSG, alarma.configuracion, tiempo);
}

int alarmaDisparada(void){
	if(disparada){
		disparada=FALSE;
		return 1;
	}
	return 0;
}

void G_ALARMA_gestionarAlarmas(void){

    int retardo = 0;
    int tiempo_actual = 0;

    // Comprobamos todas las alarmas del sistema registradas
	int indice = 0;
    for(indice = 0; indice < NUM_ALARMAS; indice++){

        // Calculo de tiempos
        retardo = 1000 * (obtenerRetardo(alarmas[indice].configuracion));

        tiempo_actual = (clock_getus() - (alarmas[indice].tiempo * 1000) );// / 1000;

        // Si y solo si esta activa y hay que dispararla
        if(alarmas[indice].activa == TRUE && retardo <= tiempo_actual){
            if(alarmas[indice].ID==6){
                G_ALARMA_dispararAlarma(alarmas[indice]);
								disparada = TRUE;
								
            }{
                //disparamos la alarma
                G_ALARMA_dispararAlarma(alarmas[indice]);
            }


            // Si es periodica actualizamos el timestamp
            if(esPeriodica(alarmas[indice].configuracion) == TRUE){
                alarmas[indice].tiempo = clock_getus()/1000;
            }

            // Si no la desactivamos
            else{
                alarmas[indice].activa = DISABLE;
            }

        }

    }
}


void G_ALARMA_reiniciarTIMEOUT(void){
	alarmas[ALARMA_TIME_OUT].tiempo = clock_getus()/1000;
}

void G_ALARMA_reiniciarINACTIVIDAD(void){
	alarmas[ALARMA_INACTIVIDAD].tiempo = clock_getus()/1000;
}
