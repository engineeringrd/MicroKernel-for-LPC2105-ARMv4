	PRESERVE8 {TRUE}
	AREA datos,  DATA, readwrite
NUM_COLUMNAS EQU 7
NUM_FILAS EQU 6	
	AREA cod, CODE ,readonly
	EXPORT conecta4_buscar_alineamiento_arm
	
conecta4_buscar_alineamiento_arm

;Epilogo
	MOV IP,SP
	STMDB SP!,{R4-R10,FP,IP,LR,PC}
	SUB FP,IP,#4
	SUB SP,SP,#0x00000008
;finEpilogo
	
	; Cargamos los argumentos que nos pasan
	MOV r4,r0 ;R4 = cuadrícula
	MOV r5,r1 ;R5 = fila
	MOV r6,r2 ; R6 = columna
	MOV r7,r3 ; R7 = color
	LDR r8,[FP,#0x04] ; R8 = delta_fila
	LDR r9,[FP,#0x08] ; R9 = delta_columna
	
ini_funcion

;if (!C4_fila_valida(fila) || ! C4_columna_valida(columna)) return 0
	;!C4_fila_valida(fila) 
	CMP R5,#0x01
	BLT retu0
	CMP R5,#NUM_FILAS 
	BGT retu0
	;!C4_columna_valida(columna)
	CMP R6,#0x01
	BLT retu0
	CMP R6,#NUM_COLUMNAS 
	BGT retu0

;if(celda_vacia(cuadricula[fila][columna]) || (celda_color(cuadricula[fila][columna]) != color)) return 0;
	;celda_vacia(cuadricula[fila][columna])
	ADD R1,R4,R5,LSL #3 ; R1 = @CUADRICULA + FILA * 8
	LDRB R0,[R1,R6] ; R0 = CELDA = R1+COLUMNA
	MOV R2,#0x01
	BIC R0,R2,R0,LSR #2 ; CELDA == VACIA
	CMP R0,#0x0
	BNE retu0
;(celda_color(cuadricula[fila][columna]) != color
	LDRB R0,[R1,R6]
	AND R1,R0,#0x03
	CMP R1, R7 ; CELDA_COLOR(CELDA) != COLOR
	BNE retu0
	
	;Pasamos los argumentos de la funcion
	MOV R0,R4 ; R0 = CUADRICULA
	;uint8_t nueva_fila = fila + delta_fila;
	ADD R1,R5,R8 ; nueva_fila = fila + delta_fila
	;uint8_t nueva_columna = columna + delta_columna;
	ADD R2,R6,R9 ; nueva_columna = columna + delta_columna
	MOV R3,R7 ; R3 = COLOR
	STR R8,[SP]
	STR R9,[SP,#0x04]

;return 1 + conecta4_buscar_alineamiento_c(cuadricula, nueva_fila, nueva_columna, color, delta_fila, delta_columna);
	BL conecta4_buscar_alineamiento_arm
	ADD R0,R0,#0x01
	B fin_funcion
	
retu0
	MOV R0,#0x0 ; return 0
	
fin_funcion
	;Prologo
	ADD SP,SP,#0x00000008
	LDMIA SP,{R4-R10,FP,SP,PC}
	END