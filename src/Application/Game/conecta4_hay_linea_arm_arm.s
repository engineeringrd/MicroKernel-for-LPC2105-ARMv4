 	PRESERVE8 {TRUE}
	AREA datos,  DATA, readwrite
deltas_fila DCB 0, -1, -1, 1 ;int8_t deltas_fila[4] = {0, -1, -1, 1};
deltas_columna DCB -1, 0, -1, -1  ;int8_t deltas_columna[4] = {-1, 0, -1, -1};
	AREA cod, CODE ,readonly
	EXPORT conecta4_hay_linea_arm_arm
	IMPORT conecta4_buscar_alineamiento_arm
	
conecta4_hay_linea_arm_arm

;Epilogo
	MOV IP,SP
	STMDB SP!,{R4-R10,FP,IP,LR,PC}
	SUB FP,IP,#4
	SUB SP,SP,#0x00000018
;FinEpologo

	;Cargamos los argumentos que nos pasan
	mov r4,r0 ;R4 = cuadrícula
	mov r5,r1 ;R5 = fila
	mov r6,r2 ; R6 = columna
	mov r7,r3 ; R7 = color
	
ini_funcion
	;uint8_t linea = FALSE;
	mov r9,#0x0 ;
	;unsigned int i = 0;
	mov r10,#0x0 

;for(i=0; (i < 4) && (linea == FALSE); ++i)
ini_for				
	cmp r10, #0x03 ; i < 4
	bgt fin_for 
	cmp r9, #0x00 ; linea == FALSE
	bne fin_for
	
	;BUSCAR SENTIDO
	
	;Calculamos el elemento i de cada vector
	ldr R0,=deltas_fila ;Direccion del comienzo de deltas_fila
	ldr r1,=deltas_columna ;Direccion del comienzo de deltas_columna
	ldrsb r0,[r0,r10] ; deltas_fila[i]
	ldrsb r1,[r1,r10] ; deltas_columna[i]
	
	;Le pasamos los argumentosa a la funcion
	STR R0,[sp] ; delta_fila[i]
	STR R1,[sp,#0X04] ; delta_columna[i]
	mov r0,r4 ; r0 = cuadricula
	mov r1,r5 ; r1 = fila
	mov r2,r6 ; r2 = columna
	mov r3,r7 ; r3 = color

;long_linea = conecta4_buscar_alineamiento_c(cuadricula, fila, columna, color, deltas_fila[i], deltas_columna[i]);
	BL conecta4_buscar_alineamiento_arm ; Devuelve en R0
	mov r8,r0 ; r8 = long_linea
	
	;if(linea = long_linea >= 4) continue
	cmp r8, #0x03 
	movgt r9,#0x01
	bgt continue
	
	;Calculamos el elemento i de cada vector
	ldr R0,=deltas_fila
	ldr r1,=deltas_columna
	ldrsb r0,[r0,r10] ; deltas_fila[i]
	ldrsb r1,[r1,r10] ; deltas_columna[i]
	;Lo negamos
	mov r2,#0x00000000
	sub r0,r2,r0 ; -deltas_fila[i]
	sub r1,r2,r1 ; -deltas_columna[i]
	
	;BUSCAR SENTIDO INVERSO
	
	;Le pasamos los argumentosa a la funcion
	STR R0,[sp] ; -delta_fila[i]
	STR R1,[sp,#0X04] ; -delta_columna[i]
	add r2,r6,r1 ; r2 = columna + (-deltas_columna[i])
	add r1,r5,r0 ; r1 = fila + (-deltas_fila[i])
	mov r0,r4 ; r0 = cuadricula
	mov r3, r7 ; r3 = color
	
;long_linea += conecta4_buscar_alineamiento_c(cuadricula, fila-deltas_fila[i], columna-deltas_columna[i], color, -deltas_fila[i], -deltas_columna[i]);
	BL conecta4_buscar_alineamiento_arm ;Devuelve en R0
	add r8,r0,r8 ; long_linea+=r0
	;linea = long_linea >= 4;
	cmp r8,#0x03
	movgt r9,#0x01 ; linea = TRUE
	
continue			
	add r10,r10,#0x01 ; i++
	b ini_for ; comparamos en el bucle

fin_for
	mov r0,r9 ; return linea

fin_funcion
	;Epilogo
	ADD SP,SP,#0x00000018
	LDMDB FP,{R4-R10,FP,SP,PC}
	;finEpilogo
	END