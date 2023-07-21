/*
 * AUTORES:     Raul Cosmin Daramus Raica 796682
 *              Ibón Cañete Bielsa 776561
 * ASIGNATURA:  30220 Proyecto Hardware del Grado de Ingeniería en Informática
 *			   Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
 * FECHA:       Noviembre de 2022
 * DESCRIPCIÓN: Funcion main del microKernel
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
#include "test.h"
#include "gestor_juego.h"
#include "gestor_serie.h"
#include "RTC.h"
#include "WT.h"

/* Constantes del Scheduler */
const int periodo_encolacion = 50; // Tiempo en ms

int main(){
    // Prueba que todos los modulos funcionan de forma correcta
    int OK = test();
    // Inicializar colas
    cola_inicializar_eventos();
    cola_inicializar_mensajes();

    // Se inicia el temporizador que mide tiempos
    temporizador_iniciar();
    temporizador_empezar();

    // Se inicia el temporizador periodico
    temporizador_reloj(periodo_encolacion);

    // Inicializa G_Alarm
    G_ALARMA_inicializar();

    // Inicializar G_IO
    G_IO_inicializar();

    // Inicializar G_Boton
    G_BOTON_inicializar();
    
    // Inicializar G_serie
    G_SERIE_init();

    //Inicializar Juego
    G_JUEGO_iniciarJuego();
    
    RTC_init();

    WD_init(1);
    
    // Llama al scheduler del sistema
    scheduler();
    
}
