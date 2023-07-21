/*
* AUTORES:     Raul Cosmin Daramus Raica 796682
*              Ibón Cañete Bielsa 776561
* ASIGNATURA:  30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			   Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA:       Noviembre de 2022
* DESCRIPCIÓN: Definición de constantes comunes del sistema
*/

#ifndef PH_CONSTANTES_H
#define PH_CONSTANTES_H

/* For Hardware */
#define ENABLE 1
#define DISABLE 0
#define RESET 0
#define DEFAULT 0x20 // bit 5 enables vectored IRQs. 
#define PLC_CLOCK 150000 // Frecuencia del PLC Clock del sistema en Hz

/* Boolean */
#define FALSE 0
#define TRUE 1

/* NULL */
#define NO_AUX_DATA 0x00000000
#define NO_INICIALIZADO -1



#endif //PH_CONSTANTES_H
