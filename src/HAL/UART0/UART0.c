/*
* AUTORES:  Raul Cosmin Daramus Raica 796682
*           Ibón Cañete Bielsa 776561
* ASIGNATURA: 30220 Proyecto Hardware del Grado de Ingeniería en Informática
*			Escuela de Ingeniería y Arquitectura - Universidad de Zaragoza
* FECHA: Diciembre de 2022
* DESCRIPCIÓN: Definición de las funciones para la gestión serie
*/
#include "UART0.h"
#include "constantes.h"
#include "gestor_interrupciones.h"
#include "cola_async.h"
#include "eventos.h"
#include "gestor_alarmas.h"
#include <LPC210x.H>                     /* LPC21xx definitions */

#define END_LINE   0x0D                     // Final de linea

/* Tipos de interrupciones */
#define RDA        0x4                      // Receive Data Available (RDA)
#define THRE       0x2                      // Transmit Holding Register Empty (THRE)



// A la línea serie accederemos por interrupciones y
// al llegar un comando completo se generará un nuevo evento
// Cuando la RSI detecte un carácter generará el evento correspondiente. 
void rsi_UART0(void) __irq;

void UART0_init(void){
              
    PINSEL0 |= 0x5;       // Enable RxD1 and TxD1              
    U0LCR = 0x83;         // 8 bits, no Parity, 1 Stop bit     
    U0DLL = 96;           // 9600 Baud Rate @ 15MHz VPB Clock  
    U0LCR = 0x03;         // DLAB = 1                          
    U0IER = 0x03;            // Activar RDA y THRE

    // Activar interrupcion
    VICVectAddr4 = (unsigned long)rsi_UART0;    // Rutina de interrupcion
    VICVectCntl4 = DEFAULT | 6;                 // Numero 6 es la UART                
    VICIntEnable = VICIntEnable | 0x00000040;   // Activar UART0 Interrup   
}

char UART0_getChar(void){
  return (char)(U0RBR);    
}

void UART0_sendChar(char c)  {
    //Comprobar final de linea
    if (c == '\0'){
        // Escribir final de linea
        U0THR = END_LINE;
    }
    else{
        // Escribir por pantalla
        U0THR = c;
    }
}
int UART0_getInterrupt(void)  {
  return U0IIR & 0xE;
}

void rsi_UART0(void) __irq{
   G_ALARMA_reiniciarTIMEOUT();
   // Extraer información sobre la interrupción
    unsigned int tipo = UART0_getInterrupt();
    char c = UART0_getChar();
    
    // Si es interrupcion de tipo RDA (Entrada)
    if (tipo == RDA){
        cola_encolar_eventos(EV_ENTRADA_P_SERIE,0,c);     // Se ha escrito un caracter
    }

    // Si es interrupcion de tipo THRE (Salida)
    else if (tipo == THRE){ 
	    cola_encolar_eventos(EV_SALIDA_P_SERIE,0,0) ;     // Se quiere enviar un caracter
    }

    VICVectAddr = RESET; // Acknowledge
}
