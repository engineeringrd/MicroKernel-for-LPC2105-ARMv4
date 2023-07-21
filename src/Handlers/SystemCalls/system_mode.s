; Lee del registro CPRS y devuelve el modo (FIQ,IRQ,USER)

		AREA    system_mode, CODE, READONLY
		EXPORT 	mode
mode
		STMFD   SP!, {LR}          ; Store LR

		MRS		R0, CPSR
		AND		R0, R0, #0x1F      ; Devolvemos en r0 en valor del modo

		LDMFD   SP!, {PC}         ; Restore LR

		END