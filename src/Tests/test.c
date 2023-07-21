/*
 * AUTORES:     Raul Cosmin Daramus Raica 796682
 *              Ibón Cañete Bielsa 776561
 * ASIGNATURA:  30220 Proyecto Hardware del Grado de Ingeniería en Informática
 *			   Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
 * FECHA:       Noviembre de 2022
 * DESCRIPCIÓN: Funciones de test del microKernel
 */

#include "constantes.h"
#include "temporizador.h"
#include "gpio.h"
#include "gestor_alarmas.h"
#include "gestor_energia.h"
#include "gestor_boton.h"
#include "gestor_io.h"
#include "scheduler.h"
#include "cola_mensajes.h"
#include "cola_async.h"
#include "msg.h"
#include "test.h"
#include "gestor_serie.h"
#include "systemCalls.h"

/* Constantes del Scheduler */
const int periodo_default = 1/100000;
const int MAX_SIZE_COLA_EVENTOS = 32;
int test(void){
    //int probarColas = testColas();
		//int probar = probarEntrada();
		//int probarSalida();
		return 1;

}

int probarColaMensajes(void){
    cola_inicializar_mensajes();
		int i = 0;
    while(i < MAX_SIZE_COLA_EVENTOS){
        uint32_t tiempo = clock_getus();
        cola_encolar_mensajes(ALARMA_BOTON_1, NO_AUX_DATA,tiempo);
				i++;
    }
    while(!cola_isEmpty_mensajes()){
        cola_desencolar_mensajes();
    }
    return TRUE;
}

int probarColaEventos(void){
    cola_inicializar_eventos();
	int i = 0;
    while(i < MAX_SIZE_COLA_EVENTOS){
        uint8_t id = 1;
        uint32_t veces = 0x00000002;
        uint32_t auxData = 0x00000000;
        cola_encolar_eventos(id,veces,auxData);
			i++;
    }
    while(!cola_isEmpty_eventos()){
        cola_desencolar_eventos();
    }
    return TRUE;
}
int testColas(void){
    if(probarColaEventos() == TRUE && probarColaMensajes() == TRUE){
        return TRUE;
    }
    return FALSE;
}
int probarTimer(void){
    cola_inicializar_eventos();
    temporizador_reloj(periodo_default);
		if(!cola_isEmpty_eventos()){
					temporizador_reloj_parar();
					while(!cola_isEmpty_eventos()){
							cola_desencolar_eventos();
					}
					return TRUE;
		}
    
		return FALSE;
}

int probarIdl(void){
	/*while(1){
		G_ENERGIA_idle_mode();
	}*/
	return FALSE;
}

int probarPD(void){
	/*while(1){
		G_ENERGIA_power_down_mode();
	}*/
	return FALSE;
}

int probarGestorEnergia(void){
	int probarIDL = probarIdl();
	int probarPowerDown = probarPD();
	return TRUE;
}


int probarPIN_OVERFLOW(void){

    // DESBORDAR LA COLA
    for(int i = 0; i < MAX_SIZE_COLA_EVENTOS + 1; i++){
        cola_encolar_eventos(98,1,NO_AUX_DATA);
    }
	return TRUE;
}

int probarEntrada(void){
	G_SERIE_init();
    G_SERIE_gestion_char('#');
    G_SERIE_gestion_char('N');
    G_SERIE_gestion_char('E');
    G_SERIE_gestion_char('W');
    G_SERIE_gestion_char('!');
    int comprobar = G_SERIE_comprobarComando();//tendria que ser 2
    
    if(comprobar!=2){
        return 0;
    }
		return 1;
}



