#include "conecta4_2022.h"
#include "tableros.h"
#include <stdio.h>
#include <string.h>

extern uint8_t conecta4_buscar_alineamiento_arm(CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t
	fila, uint8_t columna, uint8_t color, int8_t delta_fila, int8_t
	delta_columna);
extern uint8_t conecta4_hay_linea_arm_c(CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t
	fila, uint8_t columna, uint8_t color);
extern uint8_t conecta4_hay_linea_arm_arm(CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t
	fila, uint8_t columna, uint8_t color);



// Devuelve ERROR en caso de no encontrar fila
uint8_t C4_calcular_fila(CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t columna){
	uint8_t fila = 1; // row 0 is used to enumerate the columns

	if ((columna < 1 ) || (columna >  NUM_COLUMNAS)) {
		return ERROR;
	} // Out of the board. Columna must go form 1 to 7

	while((fila <= NUM_FILAS)
		&& (celda_vacia(cuadricula[fila][columna]) == FALSE)){
	    fila++;
	}
	return fila <= NUM_FILAS ? fila : ERROR;
};



// Devuelve la longitud de la línea más larga
uint8_t conecta4_buscar_alineamiento_c(CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t
	fila, uint8_t columna, uint8_t color, int8_t delta_fila, int8_t
	delta_columna)
{
    // avanzar hasta que cela esté vacía, sea distinto color o lleguemos al borde
    if (!C4_fila_valida(fila) || ! C4_columna_valida(columna)) {
			return 0;
    }

    // posicion valida y mismo color
    if(celda_vacia(cuadricula[fila][columna]) || (celda_color(cuadricula[fila][columna]) != color)) { 
				return 0;
    }

    // avanzar índices
    uint8_t nueva_fila = fila + delta_fila;
    uint8_t nueva_columna = columna + delta_columna;

    // incrementar longitud y visitar celda vecina
    return 1 + conecta4_buscar_alineamiento_c(cuadricula, nueva_fila, nueva_columna, color, delta_fila, delta_columna);
}



// Devuelve true(int = 1) si y solo si encuentra una línea de longitud mayor o igual a 4 invocado a la funcion buscar_alineamiento en C
uint8_t conecta4_hay_linea_c_c(CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t fila, uint8_t columna, uint8_t color)
{
   int8_t deltas_fila[4] = {0, -1, -1, 1};
   int8_t deltas_columna[4] = {-1, 0, -1, -1};
   unsigned int i = 0;
   uint8_t linea = FALSE;
   uint8_t long_linea = 0;

   // buscar linea en fila, columna y 2 diagonales
   for(i=0; (i < 4) && (linea == FALSE); ++i) {
       // buscar sentido
       long_linea = conecta4_buscar_alineamiento_c(cuadricula, fila, columna, color, deltas_fila[i], deltas_columna[i]);
       linea = long_linea >= 4;
       if (linea) {
         continue;
       }
       // buscar sentido inverso
       long_linea += conecta4_buscar_alineamiento_c(cuadricula, fila-deltas_fila[i],
	       columna-deltas_columna[i], color, -deltas_fila[i], -deltas_columna[i]);
       linea = long_linea >= 4;
   }
   return linea;
}



// Devuelve true(int = 1) si y solo si encuentra una línea de longitud mayor o igual a 4 invocado a la funcion buscar_alineamiento en ARM
uint8_t conecta4_hay_linea_c_arm(CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t fila, uint8_t columna, uint8_t color)
{
   int8_t deltas_fila[4] = {0, -1, -1, 1};
   int8_t deltas_columna[4] = {-1, 0, -1, -1};
   unsigned int i = 0;
   uint8_t linea = FALSE;
   uint8_t volatile long_linea = 0;

   // buscar linea en fila, columna y 2 diagonales
   for(i=0; (i < 4) && (linea == FALSE); ++i) {
       // buscar sentido
       long_linea = conecta4_buscar_alineamiento_arm(cuadricula, fila, columna, color, deltas_fila[i], deltas_columna[i]);
       linea = long_linea >= 4;
       if (linea) {
         continue;
       }
       // buscar sentido inverso
       long_linea += conecta4_buscar_alineamiento_arm(cuadricula, fila-deltas_fila[i],
	       columna-deltas_columna[i], color, -deltas_fila[i], -deltas_columna[i]);
       linea = long_linea >= 4;
   }
   return linea;
}



// Actualiza el tablero con el valor de las fichas correspondientes
void C4_conecta4_actualizar_tablero(CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t fila,
	uint8_t columna, uint8_t val)
{
    celda_poner_valor(&cuadricula[(fila)][(columna)], val);
}



//Devuelve TRUE (int =1) si y solo si esta jugada llena todo el tablero y hay empate
int C4_comprobar_empate(CELDA cuadricula[TAM_FILS][TAM_COLS]){
	for(int j=0;j< NUM_COLUMNAS;j++) {
		if(celda_vacia(cuadricula[NUM_FILAS][j])==TRUE){
			return 0;
		}
	}
	return 1;
}



	// Verifica que todas las optimizaciones dan el mismo resultado
int C4_verificar_4_en_linea(CELDA cuadricula[TAM_FILS][TAM_COLS], uint8_t fila, uint8_t columna, uint8_t color){
	uint8_t resultado_c_c = conecta4_hay_linea_c_c(cuadricula, fila, columna, color);
	return resultado_c_c;
}

void conecta4_reiniciarTablero(void){
	
	for(int i = 1;i<= NUM_FILAS;i++){
		for(int j = 1;j< NUM_COLUMNAS;j++){
			reiniciar_celda(&cuadricula_normal[i][j]);
		}
	}
	
}

int conecta4_comprobar_columna(int columna){
		int row = C4_calcular_fila(cuadricula_normal, columna); // returns 0 if is not in range
		if(C4_fila_valida(row) && C4_columna_valida(columna)) return row;
		return FALSE;
}

void conecta4_actualizar_tablero(int row, int column, int colour){
	C4_conecta4_actualizar_tablero(cuadricula_normal,row,column,colour);
}

int conecta4_finPartida(int row, int column, int colour){
	return C4_verificar_4_en_linea(cuadricula_normal, row, column, colour) || C4_comprobar_empate(cuadricula_normal);
}

int conecta4_cambiarJugador(int jugador){
	return C4_alternar_color(jugador);
}
/*
6| | | | | | | |
5| | | | | | | |
4| | | | | | | |
3| | | |N| | | |
2| | |R|R| | | |
1| | |N|R| | | |
----------------
-|1|2|3|4|5|6|7|

*/

char *get_tablero(void){
	char totalArray[2048];

	strncat(totalArray,"\n",1);
	for(int i = NUM_FILAS;i >= 1;i--){
		char numF= (char)i+48;
		strncat(totalArray,&numF,1); // ASCII Numero = num+ 48(0)
		strncat(totalArray,"|",1); // ASCII | = 124
		for(int j = NUM_COLUMNAS;j >= 1;j--){
			if(celda_vacia(cuadricula_normal[i][j])){
				strncat(totalArray," ",1); // ASCII ESPACIO = 32
			}else if(celda_negra(cuadricula_normal[i][j])){
				strncat(totalArray,"N",1); // ASCII N = 78
			}
			else if(celda_blanca(cuadricula_normal[i][j])){
				strncat(totalArray,"B",1); // ASCII B = 66
			}else if(celda_especial(cuadricula_normal[i][j])){
				strncat(totalArray,"*",1);
			}
			
			strncat(totalArray,"|",1); // ASCII | = 124
		}
		strncat(totalArray,"\n",1); // ASCII  \n = 10
	}
	char separador[]=   "----------------\n";
	char indicadorColumna[] = "-|1|2|3|4|5|6|7|\n";
	strcat(totalArray,separador);
	strcat(totalArray,indicadorColumna);

	return totalArray;
} 

//Funcion principal para jugar
void conecta4_jugar(void){
	
}
