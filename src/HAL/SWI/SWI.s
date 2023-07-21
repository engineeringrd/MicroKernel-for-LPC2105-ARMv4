;/*****************************************************************************/
;/* SWI.S: SWI Handler                                                        */
;/*****************************************************************************/
;/* This file is part of the uVision/ARM development tools.                   */
;/* Copyright (c) 2005-2006 Keil Software. All rights reserved.               */
;/* This software may only be used under the terms of a valid, current,       */
;/* end user licence from KEIL for a compatible version of KEIL software      */
;/* development tools. Nothing else gives you the right to use this software. */
;/*****************************************************************************/

T_Bit           EQU     0x20
F_Bit		EQU	0x40
I_Bit		EQU	0x80



                PRESERVE8                      ; 8-Byte aligned Stack
                AREA    SWI_Area, CODE, READONLY
                ARM

                EXPORT  SWI_Handler
SWI_Handler   

                STMFD   SP!, {R12, LR}         ; Store R12, LR
                MRS     R12, SPSR              ; Get SPSR
                STMFD   SP!, {R8, R12}         ; Store R8, SPSR
                TST     R12, #T_Bit            ; Check Thumb Bit
                LDRNEH  R12, [LR,#-2]          ; Thumb: Load Halfword
                BICNE   R12, R12, #0xFF00      ; Extract SWI Number
                LDREQ   R12, [LR,#-4]          ; ARM:   Load Word
                BICEQ   R12, R12, #0xFF000000  ; Extract SWI Number

; add code to enable/disable the global IRQ flag
                CMP     R12,#0xFF              
                BEQ     enable_fiq

                CMP     R12,#0xFE              
                BEQ     disable_fiq

                CMP     R12,#0xFD              
                BEQ     enable_irq_fiq

                CMP     R12,#0xFC              
                BEQ     disable_irq_fiq

                CMP     R12,#0xFB              
                BEQ     read_IRQ_bit

                CMP     R12,#0xFA            
                BEQ     read_FIQ_bit

                LDR     R8, SWI_Count
                CMP     R12, R8
                BHS     SWI_Dead               ; Overflow
                ADR     R8, SWI_Table
                LDR     R12, [R8,R12,LSL #2]   ; Load SWI Function Address
                MOV     LR, PC                 ; Return Address
                BX      R12                    ; Call SWI Function 

                LDMFD   SP!, {R8, R12}         ; Load R8, SPSR
                MSR     SPSR_cxsf, R12         ; Set SPSR
                LDMFD   SP!, {R12, PC}^        ; Restore R12 and Return

SWI_Dead        B       SWI_Dead               ; None Existing SWI

SWI_Cnt         EQU    (SWI_End-SWI_Table)/4
SWI_Count       DCD     SWI_Cnt

                IMPORT  __SWI_0
                IMPORT  __SWI_1

SWI_Table
                DCD     __SWI_0                ; SWI 0 Function Entry
                DCD     __SWI_1                ; SWI 1 Function Entry

SWI_End

; Dentro del código para activar/desactivar las interrupciones IRQ y FIQ, que
;deberá estar dentro del fichero SWI.s, hay que cargar el registro SPSR, modificar
;el bit de IRQ, actualizar SPSR, y finalmente volver a modo usuario. Para cargar el
;registro SPSR, deberéis de revisar la documentación de la instrucción SWI y la
;copia en memoria del registro CPSR al cambiar de modo.

enable_fiq
		MRS	R0, SPSR
		MOV	R1, #0xFFFFFFFF
		EOR	R2, R1, #F_Bit	        ; Negar
				
		AND 	R0, R0, R2 		; Enable FIQ interrupts
		MSR 	SPSR_c, R0
				
                LDMFD   SP!, {R8, R12}          
                LDMFD   SP!, {R12, PC}^         ; Return

disable_fiq
		MRS	R0, SPSR
		ORR 	R0, R0, #F_Bit 		; Disable FIQ interrupts
		MSR 	SPSR_c, R0
				
                LDMFD   SP!, {R8, R12}      
                LDMFD   SP!, {R12, PC}^         ; Return

enable_irq_fiq
        	MRS	R0, SPSR
		MOV	R1, #0xFFFFFFFF
		EOR	R2, R1, #I_Bit:OR:F_Bit	; Negar
				
		AND 	R0, R0, R2 		; Enable IRQ and FIQ interrupts
		MSR 	SPSR_c, R0
				
                LDMFD   SP!, {R8, R12}        
                LDMFD   SP!, {R12, PC}^         ; Return

disable_irq_fiq
		MRS	R0, SPSR
		ORR 	R0, R0, #I_Bit:OR:F_Bit ; Disable IRQ and FIQ interrupts
		MSR 	SPSR_c, R0
				
                LDMFD   SP!, {R8, R12}          
                LDMFD   SP!, {R12, PC}^         ; Return	
               
read_IRQ_bit
                MRS	R1, SPSR
                AND     R1, R1,#I_Bit
                MOVEQ   R0, #0
                MOVNE   R0, #1
                LDMFD   SP!, {R8, R12}          
                LDMFD   SP!, {R12, PC}^         ; Return

read_FIQ_bit
                MRS	R1, SPSR
                AND     R1, R1,#F_Bit
                MOVEQ   R0, #0
                MOVNE   R0, #1
                LDMFD   SP!, {R8, R12}          
                LDMFD   SP!, {R12, PC}^         ; Return

                END

