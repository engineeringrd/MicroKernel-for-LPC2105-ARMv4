/*
 * AUTORES:     Raul Cosmin Daramus Raica 796682
 *              Ib�n Ca�ete Bielsa 776561
 * ASIGNATURA:  30220 Proyecto Hardware del Grado de Ingenier�a en Inform�tica
 *			   Escuela de Ingenier�a y Arquitectura - Universidad de Zaragoza
 * FECHA:       Noviembre de 2022
 * DESCRIPCI�N: Funciones relativas a la gestion del juego
 */
 
 #include "gestor_juego.h"

/* Gestores */
#include "gestor_boton.h"
#include "gestor_io.h"

/* Conecta4 */ 
#include "conecta4_2022.h"
#include "celda.h"
#include "tableros.h"

#include "gestor_alarmas.h"
#include "msg.h"
#include "configuraciones.h"

#define CARACTER_ESPECIAL 3
#define LIMPIAR 0

static int volatile cancelado = FALSE;
static int volatile row_anterior;
static int volatile columna_anterior;
static int volatile jugador = 1;
static int volatile jugando = FALSE;
static int volatile disponible = TRUE;


void G_JUEGO_iniciarJuego(void){

    // Incializar Turno
    G_JUEGO_inicializarTurno();
    
    // El programa mostrará por línea serie información sobre el
    // juego y cómo jugar mientras se espera la pulsación de cualquier botón o llega
    // un nuevo comando de nueva partida 
    G_IO_mostrar_leyenda();

    //A continuación, aparecerá el tablero por línea serie en la consola
    //G_IO_enviar_tablero();

}


void G_JUEGO_inicializarTurno(void){
    // jugador 1 (blancas) o 0 (negras) (GPIO leer Bit 1 y 2)
		jugador = 1;
    G_IO_mostrarTurno(jugador);	
}

void G_JUEGO_reiniciarPartida(void){
    jugando = TRUE;
    disponible = TRUE;
    G_IO_clearAll();
    G_JUEGO_inicializarTurno();
    
    // Reiniciamos el juego
		conecta4_reiniciarTablero();
    G_JUEGO_finalizarPartida(CAUSA_REINICIAR,0);
}

void G_JUEGO_realizarJugada(int columna){    
  if (jugando==FALSE)
    {
      G_IO_mensajeEmpezar();
    }
    else{
      if(disponible){
        // jugador 1 (blancas) o 2 (negras) (GPIO leer Bit 1 y 2)
        G_IO_clearJugadaRealizada();

        // Llamar a la funcion del juego que realiza la jugada
        // int columna = G_IO_columnaSeleccionada();
        int row = conecta4_comprobar_columna(columna); //devolvera 0 si no es valida , en caso contrario la fila en la que se coloca
          
        // Si y solo si esta llena o has seleccionado la columna invalida 
        if (row != 0){
            
            // Guardarnos el tablero anterior por si se nos cancelan
            row_anterior = row;
            columna_anterior = columna;

            //Si se realiza el movimiento, se enviará de nuevo el tablero por la línea serie 
            conecta4_actualizar_tablero(row, columna, CARACTER_ESPECIAL); // actualizamos el tablero el 3 significa caracter Especial
            
            /* Mostrar la jugada con caracterEspecial */
            G_IO_enviar_tablero(0);

            /* Mostrar mensaje para cancelar*/
            //G_IO_mostrar_paraCancelar();

            // Activar alarma
            //cola_encolar_mensajes(SET_ALARMA,CONFIG_ALARMA_CONFIRMAR_JUGADA,temporizador_leer());
            crearAlarmaConfirmar();
            disponible = FALSE;
        }
        else{
          // Mostrar columna invalida
          G_IO_mostrarJugadaNoValida();
        }
      }else{
        G_IO_mostrarEsperarAEscribir();
      }
    }
}

void G_JUEGO_comprobarColumna(void){
    
    // Obtemos la columna actual que el jugador a seleccionado
    int columna = G_IO_columnaSeleccionada();
		if(columna > 0){
			int row = conecta4_comprobar_columna(columna); 
			
      if (row==0){// Si y solo si esta llena o has seleccionado la columna invalida 
				 G_IO_mostrarJugadaNoValida();
					G_IO_clearJugadaRealizada();
			}
      else{
				G_IO_clearJugadaNoValida();
			}
		}
}

 void G_JUEGO_confirmarJugada(void){
  
  // Si y solo si no se ha cancelado
  if(cancelado == FALSE){

      //Si se realiza el movimiento, se enviará de nuevo el tablero por la línea serie 
      conecta4_actualizar_tablero(row_anterior,columna_anterior,jugador); // actualizamos el tablero el 3 significa caracter Especial
      
      // Si y solo si ha acabado la partida
      if(conecta4_finPartida(row_anterior,columna_anterior,jugador)){
          //Mostramos quien es el ganador
          G_IO_mostrarTurno(jugador);
          G_JUEGO_finalizarPartida(CAUSA_VICTORIA,jugador);
      }
      // Seguimos la partida
      else{
				// Indicar la jugada realizada
          G_IO_mostrarJugadaRealizada();
          //G_IO_enviar_tablero(jugador);
          // Cambiamos el jugador
          jugador = conecta4_cambiarJugador(jugador);
          //G_IO_mostrarTurno(jugador); // mostramos el otro jugador
          G_IO_enviar_tablero(jugador);
      }
      disponible = TRUE;
  }else{
    cancelado = FALSE;
  }
 }



 void G_JUEGO_cancelarJugada(void){
  if(!disponible){
      // Para ignorar la alarma
      cancelado = TRUE;

      // Restaurar tablero
      conecta4_actualizar_tablero(row_anterior, columna_anterior, LIMPIAR); // actualizamos el tablero el 0 significa limpiar

      //Mostrar que se ha cancelado la jugada
      G_IO_mostrar_cancelada();

      // Enviamos el tablero
      G_IO_enviar_tablero(3);
      disponible = TRUE;
  }
 }


void G_JUEGO_finalizarPartida(int causa, int jugador){
    jugando = FALSE;
  // Se muestran informacion
  G_IO_mostrarFinalPartida(causa,jugador);

  //Además, se mostrará la leyenda de volver a jugar. Si el usuario decide volver a jugar se empezará una nueva partida
  //G_IO_mostrar_leyenda();
}

void G_JUEGO_partidaNueva(void){
    jugando = TRUE;
    G_IO_clearAll();
    G_JUEGO_inicializarTurno();
    G_IO_nueva_partida();
		conecta4_reiniciarTablero();
}
