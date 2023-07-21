#include <LPC210x.H> 
#include "RTC.h"                      /* LPC210x definitions */
//CTCR
//The Clock Tick Counter is read only. It can be reset to zero through the Clock Control 
// Register (CCR). The CTC consists of the bits of the clock divider counter.
// Prior to the Seconds counter, the CTC counts 32,768 clocks per second. Due to the RTC Prescaler, these 32,768 time increments may not all be of the same duration. 
//CCR: Clock Control Register.  5-bit register that controls the operation of the clock divide circuit
// CLKEN(bit 0) Clock Enable. When this bit is a one the time counters are enabled. When it is a zero, they are disabled so that they may be initialized.
// CTCRST(bit 1) CTC Reset. When one, the elements in the Clock Tick Counter are  reset. The elements remain reset until CCR[1] is changed to zero.
// CTTEST Test Enable. These bits should always be zero during normal operation
// The Consolidated Time Registers are read only. To write new values to the Time Counters, the Time Counter addresses should be used.
// Consolidated Time register 0 (CTIME0) The Consolidated Time Register 0 contains the low order time values: Seconds, Minutes, Hours, and Day of Week
// (CTIME1)The Consolidate Time register 1 contains the Day of Month, Month, and Year values.
// (CTIME2)The Consolidate Time register 2 contains just the Day of Year value.
// Time counter group: 8 contadores de lectura/escritura para segundos, minutos, horas, d�a del mes, de la semana, del a�o, mes y a�o

void RTC_init(void){
	//CCR=0x10;
	//CCR=0x00;
	// prepara el RTC para que cuente los segundo a 15 MHz
	PREINT = 0x1C9;
	PREFRAC = 0x1C0;

	// enable of the RTC
	CCR=0x01;
	
}
void RTC_leer(uint8_t* minutos, uint8_t* segundos){
	//seconds 5:0 bits

	*segundos = CTIME0 & 0x0000003F; // Modificamos el valor de var2

	//minutes 13:8 bits
	int mascara = (1 << 6) - 1;

    //Desplazamos la mascara hasta la posicion correspondiente
    mascara = (mascara << 8); 

    // Leemos
    int valor = CTIME0 & mascara; 
	
	*minutos = (valor >> 8); // Modificamos el valor de var1
}
