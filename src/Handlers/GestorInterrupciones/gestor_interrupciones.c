/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Diciembre de 2022
* DESCRIPCIÓN: Definición de las funciones para acticar y desactivar interrupciones
*/
#include "gestor_interrupciones.h"
#include "constantes.h"
#include "systemCalls.h"


/* MODOS DEL SISTEMA */
extern int mode(void);
#define USER 0x10
#define FIQ	0x11
#define IRQ 0x12
			

void G_INTERRUPCIONES_disable(void){

    // En función del modo
    int modo = mode();
    switch(modo){
        case USER:
            //Debemos desactivar I y F que por defecto estarán activos.
            disable_irq_fiq();
            break;
        
        case IRQ:
            // Debemos desactivar F que por defecto estará activa.
            disable_fiq();

            break;
        case FIQ:
             /* No hacer nada ya que en FIQ se activan y desactivan automaticamente */
            break;
    }
}

void G_INTERRUPCIONES_enable(void){

     // En función del modo
    int modo = mode();
    switch(modo){
        
        case USER:
            //Debemos desactivar I y F que por defecto estaban activos.
            enable_irq_fiq();
            break;
        
        case IRQ:
            // Debemos activa F que por defecto estaba activa.
            enable_fiq();

            break;
        case FIQ:
             /* No hacer nada ya que en FIQ se activan y desactivan automaticamente */
            break;
    }

}


