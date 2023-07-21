/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Noviembre de 2022
* DESCRIPCIÓN: Implementación de las funciones del gestor de energia
*              Se desarrollará un gestor de estados de energía (G_Energia) que se encarga de
*              gestionar los estados del procesador y decidir si pasar a powerdown tras un
*              tiempo sin actividad del usuario.
*/
#include "gestor_energia.h"
#include <LPC210x.H> /* LPC210x definitions */

// Funcion en esnamblador de que reinicia la PLL
extern void restartPLL(void);

void G_ENERGIA_power_down_mode (void){
    EXTWAKE = 6; // Mediante las interrupciones EXTINT1 y EXTINT2 se despertará al procesador  (Ver tabla 1 del LPC2105 user manual)
    PCON |= 0x02; // Se indica que se quiere poner en modo PM (Ver tabla 26 del LPC2105 user manual)
    restartPLL(); // Función en ensamblador
}
void G_ENERGIA_idle_mode (void){
    PCON |= 0x01; // // Se indica que se quiere poner en modo IDLE (Ver tabla 26 del LPC2105 user manual)
}
