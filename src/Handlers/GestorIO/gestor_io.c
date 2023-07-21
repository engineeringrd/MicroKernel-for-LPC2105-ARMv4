/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Noviembre de 2022
* DESCRIPCIÓN: Definición de las funciones del gestor de IO
*/

#include "gpio.h"
#include "constantes.h"
#include "gestor_io.h"
#include "cola_mensajes.h"
#include "msg.h"
#include "temporizador.h"
#include "configuraciones.h"
#include "gestor_alarmas.h"
#include "gestor_serie.h"
#include "conecta4_2022.h"
#include "gestor_juego.h"
#include "RTC.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_TABLERO 16

char fila6[TAM_TABLERO]; 
char fila5[TAM_TABLERO];
char fila4[TAM_TABLERO];
char fila3[TAM_TABLERO];
char fila2[TAM_TABLERO];
char fila1[TAM_TABLERO];

char tablero[2048];

/******** INTERFACE GPIO *************** */
enum {
    PIN_JUGADOR_1 = 1, // GPIO 1
    PIN_JUGADOR_2 = 2,  // GPIO 1

//
    PIN_CANCELAR = 14,  // GPIO 14
    PIN_REINICIAR_PARTIDA = 15,  // GPIO 15
    PIN_JUGADA_REALIZADA = 16,  // GPIO 16
    PIN_JUGADA_NO_VALIDA = 17,  // GPIO 17
    PIN_FINAL_PARTIDA = 18,  // GPIO 18
    PIN_ERROR_BUFFER = 19,  // GPIO 19
    PIN_OVERFLOW = 30,  // GPIO 30
    PIN_LATIDO = 31  // GPIO 31
};
/***********************************/
#define MARCADO 1


static volatile int LED_latido = DISABLE;

void G_IO_inicializar (void){
	
    // Inicializa la GPIO
    GPIO_iniciar();
    GPIO_marcar_salida(PIN_JUGADOR_1,2);
    GPIO_marcar_entrada(PIN_CANCELAR,2);
    GPIO_marcar_salida(PIN_JUGADA_REALIZADA,4);
    GPIO_marcar_salida(PIN_OVERFLOW,2);

    //Se programa una alarma periódica para que 10 veces por segundo se
    //actualice la visualización de si la columna marcada está llena.
    //cola_encolar_mensajes(SET_ALARMA,CONFIG_COLUMNA, temporizador_leer());

}
void G_IO_clearAll(void){

	GPIO_clear_salida(1,30);
}

void G_IO_mostrarTurno(int jugador){

    // Jugador 1
    if (jugador == 1){
        GPIO_clear_salida(PIN_JUGADOR_2,1);
        GPIO_escribir(PIN_JUGADOR_1,1,MARCADO);
    }
    
    // Jugador 2
    else {
        GPIO_clear_salida(PIN_JUGADOR_1,1);
        GPIO_escribir(PIN_JUGADOR_2,1,MARCADO);
    }

}


void G_IO_mostrarJugadaRealizada(void){
	
    GPIO_escribir(PIN_JUGADA_REALIZADA,1,MARCADO);

}

void G_IO_clearJugadaRealizada(void){
	
		GPIO_clear_salida(PIN_JUGADA_REALIZADA,1);
}

void G_IO_mostrarJugadaNoValida(void){
    // Si la columna no es válida se ignorará
    char mensaje[] = "\nColumna no valida\n\0";
    G_SERIE_enviar_array(mensaje);
    //se encenderá el led GPIO17
    GPIO_escribir(PIN_JUGADA_NO_VALIDA,1,MARCADO);
}

void G_IO_clearJugadaNoValida(void){

    GPIO_clear_salida(PIN_JUGADA_NO_VALIDA,1);
}

void enviarTiempoMedio(void){
    int msMedios = cola_devolver_tiempoMedio_mensajes();
    char strMedios[20];
		strMedios[0] = '0';
		strMedios[1] = ',';
		strMedios[2] = '0';
		strMedios[3] = '0';
    int i = 4;
    while (msMedios > 0) {
        strMedios[i] = (char)((msMedios % 10) + 48);  // 48 is the ASCII value for '0'
        msMedios /= 10;
        i++;
    }
    strMedios[i] = '\0';  // Add the null terminator

    // Reverse the string
    int j = 4;
    i--;
    while (j < i) {
        char temp = strMedios[j];
        strMedios[j] = strMedios[i];
        strMedios[i] = temp;
        j++;
        i--;
    }
    strcat(tablero,"Calidad de servicio: ");
    strcat(tablero,strMedios);
    strcat(tablero," ms medios de tiempo en la gestion de mensajes\n");
}




void enviarMinutosSegundos(void){
    
    uint8_t minutos = 0, segundos = 0;
    uint8_t *ptrMinutos = &minutos;
    uint8_t *ptrSegundos = &segundos;
    


    //Tiempo total de juego de esta partida (usando la llamada de sistema del RTC al comenzar y al acabar la partida)
    RTC_leer(ptrMinutos, ptrSegundos);
    char strMinutos[20];
    int i = 0;
    while (minutos > 0) {
        strMinutos[i] = (char)((minutos % 10) + 48);  // 48 is the ASCII value for '0'
        minutos /= 10;
        i++;
    }
    strMinutos[i] = '\0';  // Add the null terminator

    // Reverse the string
    int j = 0;
    i--;
    while (j < i) {
        char temp = strMinutos[j];
        strMinutos[j] = strMinutos[i];
        strMinutos[i] = temp;
        j++;
        i--;
    }
    char strSegundos[20];
    i = 0;
    while (segundos > 0) {
        strSegundos[i] = (char)((segundos % 10) + 48);  // 48 is the ASCII value for '0'
        segundos /= 10;
        i++;
    }
    strSegundos[i] = '\0';  // Add the null terminator

    // Reverse the string
    j = 0;
    i--;
    while (j < i) {
        char temp = strSegundos[j];
        strSegundos[j] = strSegundos[i];
        strSegundos[i] = temp;
        j++;
        i--;
    }
    strcat(tablero,"La partida ha tenido una duracion de ");
    strcat(tablero,strMinutos);
    strcat(tablero," minutos y de ");
    strcat(tablero,strSegundos);
    strcat(tablero," segundos\n");
    
}
void G_IO_mostrarFinalPartida(int causa, int jugador){
    for(int i = 0; i< 2048;i++){
		tablero[i] = NULL;
	}

    //char mensaje[2048];
	//strcat(mensaje,"\n");
    // LED DE LA GPIO
    GPIO_escribir(PIN_FINAL_PARTIDA,1,MARCADO);

    //Causa por la que se termina (botón de reiniciar, victoria de uno de los jugadores, empate)
    if(causa == CAUSA_REINICIAR){
        strcat(tablero,"\nEl juego se va a reiniciar...\n");
    }
    else if(causa == CAUSA_VICTORIA){
        if (jugador == 1)
        {
            strcat(tablero,"\nEl juego ha terminado y han ganado las BLANCAS!\n");
        }else if(jugador==2){
            strcat(tablero,"\nEl juego ha terminado y han ganado las NEGRAS!\n");
        }
    }
    else if(causa == CAUSA_EMPATE){
        strcat(tablero,"\nEl juego ha terminado y ha habido un empate!\n\0");
    }
    else if(causa == CAUSA_END){
        strcat(tablero,"\nEl juego ha terminado,parece que ya no quereis jugar :(\n");
    }

    enviarMinutosSegundos();
    enviarTiempoMedio();

    //char mensaje[2048];
    char newPartida[] = "\nPara empezar una partida escribe: #NEW!\n";
    char columna[] = "Para elegir la columna donde colocar la ficha escribe: #C!\n    Donde C es un numero entre 1 y 7\n"; 
	char end[] = "Si quiere forzar el fin de la partida escribe: #END!\n\0";
    strcat(tablero,newPartida);
    strcat(tablero,columna);
    strcat(tablero,end);
    
  //Calidad de servicio en la gestión de mensajes: ¿cuánto tarda el planificador en procesar los mensajes desde que los envían? Podéis calcular el tiempo medio en microsegundos, 
  //o realizar algo más elaborado, como un histogram
  //TODO
  
  G_SERIE_enviar_array(tablero);
}

void G_IO_mostrarPIN_OVERFLOW(void){

    GPIO_escribir(PIN_OVERFLOW,1,1);
}

void G_IO_encenderLED_ERROR_BUFFER(void){
    for(int i = 0; i< 2048;i++){
		tablero[i] = NULL;
	}
	strcat(tablero,"\nEl comando no se ha escrito bien :(\nPrueba Otra Vez!\n\0");
    G_SERIE_enviar_array(tablero);
    GPIO_escribir(PIN_ERROR_BUFFER,1,1);
}

void G_IO_apagarLED_ERROR_BUFFER(void){

    GPIO_clear_salida(PIN_ERROR_BUFFER,1);
}

void G_IO_mostrarLatido(void){
	

    // Si el LED esta encendido
    if(LED_latido == ENABLE){
        // Lo apagamos
        LED_latido = DISABLE;
        GPIO_clear_salida(PIN_LATIDO,1);
    }else{
        LED_latido = ENABLE;
        GPIO_escribir(PIN_LATIDO,1,1);
    }
}



// Devuelve la columna seleccionada por el jugador actual
int G_IO_columnaSeleccionada(void){

    return FALSE;

 }



// El programa mostrará por línea serie información sobre el
// juego y cómo jugar mientras se espera la pulsación de cualquier botón o llega
// un nuevo comando de nueva partida 
void G_IO_mostrar_leyenda(void){
    for(int i = 0; i< 2048;i++){
		tablero[i] = NULL;
	}
    //char mensaje[2048];
    char newPartida[] = "\nPara empezar una partida escribe: #NEW!\n";
    char columna[] = "Para elegir la columna donde colocar la ficha escribe: #C!\n    Donde C es un numero entre 1 y 7\n"; 
	char end[] = "Si quiere forzar el fin de la partida escribe: #END!\n\0";
    strcat(tablero,newPartida);
    strcat(tablero,columna);
    strcat(tablero,end);
    G_SERIE_enviar_array(tablero);

}


/* Muestra el tablero con el siguiente formato:
6| | | | | | | |
5| | | | | | | |
4| | | | | | | |
3| | | | | | | |
2| | |R| | | | |
1| | |N| | | | |
----------------
-|1|2|3|4|5|6|7|

*/
void G_IO_enviar_tablero(int jugador){

    for(int i = 0; i< 2048;i++){
		tablero[i] = NULL;
	}
	
    char *newTablero= get_tablero();
    strcat(tablero,"\n");
	strcat(tablero,newTablero);

	strcat(tablero,"\n");
    if (jugador == 1){ //BLANCAS
        strcat(tablero,"Es el turno de las BLANCAS\n");
    }else if(jugador == 2 ){ //NEGRAS
        strcat(tablero,"Es el turno de las NEGRAS\n");
    }else if(jugador == 0){
        strcat(tablero,"Pulsa boton 1(GPIO14) para cancelar\n");
    }else if(jugador==3){
        strcat(tablero,"Movimiento cancelado\n");
    }
	G_SERIE_enviar_array(tablero);
}

void G_IO_nueva_partida(void){
    for(int i = 0; i< 2048;i++){
		tablero[i] = NULL;
	}
    char new[] = "\nComienza la partida!\n";
    char columna[] = "Para elegir la columna donde colocar la ficha escribe: #C!\n    Donde C es un numero entre 1 y 7\n"; 
	char end[] = "Si quiere forzar el fin de la partida escribe: #END!\n\0";
    strcat(tablero,new);
    strcat(tablero,columna);
    strcat(tablero,end);
    G_SERIE_enviar_array(tablero);
    //G_IO_enviar_tablero(1);
}

void G_IO_mensajeEmpezar(void){
    for(int i = 0; i< 2048;i++){
		tablero[i] = NULL;
	}
    char new[] = "\nPara poder jugar, primero escribe el comando : #NEW!\n";

    strcat(tablero,new);
    G_SERIE_enviar_array(tablero);
}


void G_IO_mostrar_paraCancelar(void){

    for(int i = 0; i< 2048;i++){
			tablero[i] = NULL;
		}
    char newMensaje[] = "\nPulsa boton 1(GPIO14) para cancelar\n";

    strcat(tablero,newMensaje);
    G_SERIE_enviar_array(tablero);

}




void G_IO_mostrar_cancelada(void){

    // Mostrar mensaje que se ha cancelado la jugada
    for(int i = 0; i< 2048;i++){
			tablero[i] = NULL;
		}
    char newMensaje[] = "\nMovimiento cancelado\n";

    strcat(tablero,newMensaje);
    G_SERIE_enviar_array(tablero);
}

void G_IO_mostrarEsperarAEscribir(void){
    // Mostrar mensaje que no se puede poner la columna porque no se ha terminado de imprimir
    for(int i = 0; i< 2048;i++){
			tablero[i] = NULL;
		}
    char newMensaje[] = "\nPor favor, espere a que termine de imprimirse los mensajes\n";

    strcat(tablero,newMensaje);
    G_SERIE_enviar_array(tablero);
}

