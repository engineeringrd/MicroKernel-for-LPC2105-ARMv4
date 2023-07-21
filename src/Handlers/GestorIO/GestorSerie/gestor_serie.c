/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Octubre de 2022
* DESCRIPCIÓN: Definición de las funciones para la gestión serie
*/
#include "gestor_serie.h"
#include "constantes.h"
#include "UART0.h"
#include "msg.h"
#include "gestor_io.h"
#include "cola_mensajes.h"
#include "systemCalls.h"
#include <string.h>

// DELIMITADORES
#define INICIO '#'
#define FIN '!'

// BUFFER PARA LA ENTRADA
#define TAM_BUFFER_READ 6 // 5 + \0
static int indice_lectura;
static char buffer_read[TAM_BUFFER_READ];

// BUFFER PARA LA SALIDA
#define TAM_BUFFER_WRITE 2048
static char buffer_send[TAM_BUFFER_WRITE];
static int indice_escritura ;
int escribiendo; //Variable para ver si esta escribiendo un mensaje

void G_SERIE_init(void){
    UART0_init();
    indice_lectura = 0;
    indice_escritura = -1;
    escribiendo = FALSE;
}

// ******** ENTRADA **************

void G_SERIE_gestion_char(int c){
  
  char CHAR = (char)c;
	char vacio = ' ';
  char array[4];
  array[0] = CHAR;
	array[1] = vacio;
	array[2] = vacio;
	array[3] = vacio;
	
  G_SERIE_enviar_array(array);
  
	//Sí recibe el carácter # 
  if ((CHAR == INICIO)){
    G_IO_apagarLED_ERROR_BUFFER();    //Apagará el led  y empezará a tratar el nuevo comando.
    indice_lectura = RESET;
    buffer_read[indice_lectura] = CHAR; // empezará a almacenar los caracteres en un buffer de tamaño 3.
    indice_lectura++;
  }
  
  // Caso base
  else{
      
      //Si recibe el carácter !
      if(CHAR == FIN){
          // Añadir caracter al buffer
          buffer_read[indice_lectura] = CHAR;
          indice_lectura++;

          // Comprobamos el comando
          int comando = G_SERIE_comprobarComando();

          //Si se ha recibido un comando correcto 
          if(comando != FALSE){
							buffer_read[0] = ' ';
							buffer_read[1] = ' ';
							buffer_read[2] = ' ';
							buffer_read[3] = ' ';
             cola_encolar_mensajes(MSG_COMANDO_CORRECTO, comando, clock_getus());//generará el mensaje pertinente
          }

          // Si el comando no es correcto
          else{
              G_IO_encenderLED_ERROR_BUFFER(); // encenderá el led (GPIO19) e ignorará todo lo que reciba hasta que llegue un nuevo #.
          }

      }

      // Si se recibe más de 4 caracteres  
      else if(indice_lectura + 1 >= TAM_BUFFER_READ){
        G_IO_encenderLED_ERROR_BUFFER(); // encenderá el led (GPIO19) e ignorará todo lo que reciba hasta que llegue un nuevo #.
      }
      
      // Sino se guarda
      else{
        // Añadir caracter al buffer
        buffer_read[indice_lectura] = c;
        indice_lectura++; // Mover indice si y solo si es menor(para no no salirse del vector)
      
      }
  }

}

int G_SERIE_comprobarComando(void){

    // Si es el comando END 
		if (buffer_read[0] == INICIO && buffer_read[1] == 'E' && buffer_read[2] == 'N' && buffer_read[3] == 'D' && buffer_read[4] == FIN) 			
		{
				return END;
		}

    // Si es el comando NEW
		else if (buffer_read[0] == INICIO && buffer_read[1] == 'N' && buffer_read[2] == 'E' && buffer_read[3] == 'W' && buffer_read[4] == FIN)	
		{
      return NEW;
		}

    // Si es la columna 1
		else if(buffer_read[0] == INICIO && buffer_read[1] == '1' && buffer_read[2] == FIN){
      return C_1;
    }
    // Si es la columna 2
		else if(buffer_read[0] == INICIO && buffer_read[1] == '2' && buffer_read[2] == FIN){
      return C_2;
    }
   // Si es la columna 3
		else if(buffer_read[0] == INICIO && buffer_read[1] == '3' && buffer_read[2] == FIN){
      return C_3;
    }
    // Si es la columna 4
		else if(buffer_read[0] == INICIO && buffer_read[1] == '4' && buffer_read[2] == FIN){
      return C_4;
    }
    // Si es la columna 5
		else if(buffer_read[0] == INICIO && buffer_read[1] == '5' && buffer_read[2] == FIN){
      return C_5;
    }
    // Si es la columna 6
		else if(buffer_read[0] == INICIO && buffer_read[1] == '6' && buffer_read[2] == FIN){
      return C_6;
    }
    else if(buffer_read[0] == INICIO && buffer_read[1] == '7' && buffer_read[2] == FIN){
      return C_7;
    }
    // Si el comando no es correcto
    else{
      return FALSE;
    }																											
}



// ******** SALIDA **************

// Inicializará las estructuras necesarias y enviará el primer carácter.
void G_SERIE_enviar_array(char string[]){
    for(int i = 0; i< TAM_BUFFER_WRITE;i++){
      buffer_send[i] = NULL;
    }
    // Incializamos las estructuras necesarias
    strcpy(buffer_send,string);
    indice_escritura = 0;

    // Indicamos que estamos escribiendo
    escribiendo = TRUE;

    //Enviamos el primer caracter
    UART0_sendChar(buffer_send[indice_escritura]);
    indice_escritura++;

}

// Enviará el siguiente carácter hasta llegar al final del array
void G_SERIE_continuar_envio(void){
    
    if(buffer_send[indice_escritura] != '\0'){
        UART0_sendChar(buffer_send[indice_escritura]);
        indice_escritura++;
    }
    else{
      escribiendo = FALSE;
      UART0_sendChar('\n');
     
    }
}

void G_SERIE_gestion_envio(void){
  if(escribiendo){
    G_SERIE_continuar_envio();
  }
}
