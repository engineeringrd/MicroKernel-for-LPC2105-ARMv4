/*
* AUTORES:     Raul Cosmin Daramus Raica 796682
*              Ibón Cañete Bielsa 776561
* ASIGNATURA:  30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			   Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA:       Noviembre de 2022
* DESCRIPCIÓN: Implementacion del scheduler del sistema
*/
#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"

/* Colas */
#include "cola_async.h"
#include "eventos.h"
#include "cola_mensajes.h"
#include "msg.h"

/* Temporizador */
#include "temporizador.h"

/* Gestores */
#include "gestor_boton.h"
#include "gestor_energia.h"
#include "gestor_io.h"
#include "gestor_alarmas.h"
#include "gestor_juego.h"
#include "gestor_interrupciones.h"
#include "gestor_serie.h"
#include "mensaje_t.h"
#include "systemCalls.h"
#include "scheduler.h"
#include "gestor_serie.h"
#include "WT.h"

#include <stdint.h>

void tratarEventos(void){

    // Desencolamos el evento
    evento_t evento = cola_desencolar_eventos();
    switch (evento.ID_evento) {

        // Comprueba si hay que disparar alguna alarma esto se hace cada vez
        // que le llegue el evento del temporizador periódico
        case EV_TEMPORIZADOR_PERIODICO:
            G_ALARMA_gestionarAlarmas();
            break;

        //Se ha pulsado el Boton 1
        case EV_BOTON_1:
            G_JUEGO_cancelarJugada();
            cola_encolar_mensajes(SET_ALARMA, evento.auxData ,clock_getus());
            break;

        //Se ha pulsado el Boton 2
        case EV_BOTON_2:
            G_JUEGO_reiniciarPartida();
            cola_encolar_mensajes(SET_ALARMA, evento.auxData ,clock_getus()); 
            break;

        // Se ha introducido un caracter nuevo 
        case EV_ENTRADA_P_SERIE:
            G_SERIE_gestion_char(evento.auxData);
            break;

        // Se esta escribiendo   
        case EV_SALIDA_P_SERIE:
            G_SERIE_gestion_envio();
            break;		
        // Se lanza el confirmar   
        case EV_CONFIRMAR:
            cola_encolar_mensajes(SET_ALARMA,evento.auxData,temporizador_leer());
            break;		
		}


}


void tratarMensajes(void){

    // Desencolamos el mensaje
    mensaje_t mensaje = cola_desencolar_mensajes();
    switch (mensaje.ID_msg) {

		/* EXPIRAN ALARMAS */

        // Si el planificador pasa más de un segundo sin procesar ningún mensaje o evento
        // se reseteará el sistema. Teniendo en cuenta que estamos generando interrupciones y mensajes periódicos, 
        // esto sólo ocurrirá si el sistema se ha quedado colgado.
         case ALARMA_INACTIVIDAD:
           while (1);
            break;
        
        // Comprueba si el boton 1 sigue pulsada
        case ALARMA_BOTON_1:
            G_BOTON_actualizar_boton1();
            break;

         // Comprueba si el boton 2 sigue pulsada
        case ALARMA_BOTON_2:
            G_BOTON_actualizar_boton2();
            break;
				
         // Ha expirado time_out
        case ALARMA_TIME_OUT:
            G_ENERGIA_power_down_mode(); // ponemos el procesador en modo power_down
            break;
        
        // Ha expirado la alarma que comrpueba la visualizacion de la columna
        case ALARMA_COLUMNA:
            G_JUEGO_comprobarColumna();
            break;
       
        // Ha expirado la alarma que muestra el latido
        case ALARMA_LATIDO:
            G_IO_mostrarLatido();
            break;
        // Se quiere configurar una alarma
        case SET_ALARMA:
            G_ALARMA_Set_Alarma(mensaje);
            break;
        // Ha expirado la alarma que da margen de tiempo para cancelar la jugada
        case ALARMA_CONFIRMAR_JUGADA:
				{
						if(alarmaDisparada()){
							G_JUEGO_confirmarJugada();
						}
				}
            break;
        // Ha habido un comando correcto
        case MSG_COMANDO_CORRECTO:
				{
            // En funcion del comando
            int comando = (mensaje).mensaje;

            // Reiniciar partida
            if(comando == NEW){
                G_JUEGO_partidaNueva();
            }
            // Finalizar partida
            else if(comando == END){
                G_JUEGO_finalizarPartida(CAUSA_END,0);
            }
            // Realizar jugada
            else if(comando == C_1 || comando == C_2 || comando == C_3 || comando == C_4 || comando == C_5 || comando == C_6 || comando == C_7){
                int columna = 8 - comando; // las columnas van al reves en el conecta4_2022
                G_JUEGO_realizarJugada(columna);
            }
					}
						
            break;
        

    }
  
}


void scheduler(void){


    // Se ejecuta un bucle infinito que monitoriza la cola de eventos e invoca a las
    // funciones que deben tratar cada uno de ellos.
    while (1)
    {
	    WD_feed();
        // Si no hay ningún evento en la cola, el planificador solicitará
        // a G_Energia el paso del procesador a modo IDLE para ahorrar energía.
        if (cola_isEmpty_eventos() && cola_isEmpty_mensajes())
        {
            G_ENERGIA_idle_mode();
        }

        // En caso contrario tratará primero los eventos
        if(!cola_isEmpty_eventos()) {

            tratarEventos();
        }
        // Y despues los mensajes
        if(!cola_isEmpty_mensajes()) {
            tratarMensajes();
        }
    }
}
