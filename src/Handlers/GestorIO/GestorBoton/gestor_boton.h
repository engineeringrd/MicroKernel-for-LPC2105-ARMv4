/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Noviembre de 2022
* DESCRIPCIÓN: Definición de las funciones del gestor de boton
*/
#ifndef __GESTOR_BOTON_H__
#define __GESTOR_BOTON_H__



// Inicializa el gestor de los botones
void G_BOTON_inicializar(void);

// Comprueba si la tecla EINT1 sigue pulsada, si es asi no se hará nada.
// En caso contrario se volverá a habilitar la interrupción de ese botón.
void G_BOTON_actualizar_boton1(void);

// Comprueba si la tecla EINT2 sigue pulsada, si es asi no se hará nada.
// En caso contrario se volverá a habilitar la interrupción de ese botón.
void G_BOTON_actualizar_boton2(void);

// Pulsa el boton 1
void G_BOTON_pulsar_boton1(void);

// Pulsa el boton 2
void G_BOTON_pulsar_boton2(void);

// Despulsa el boton 1
void G_BOTON_despulsar_boton1(void);

// Despulsa el boton 2
void G_BOTON_despulsar_boton2(void);

int G_BOTON_getVecesPulsadoBoton1(void);

int G_BOTON_getVecesPulsadoBoton2(void);


#endif //__GESTOR_BOTON_H__
