.syntax unified
.thumb
.text

@ Simbolos exportados
.global asm_svc
.global asm_sum
.global asm_zeros
.global asm_productoEscalar32
.global asm_productoEscalar16
.global asm_productoEscalar12
.global asm_productoEscalar12_sinUSAT
.global asm_invertir
.global asm_max
.global asm_filtroVentana10
.global asm_pack32to16
.global asm_downsampleM

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void asm_svc (void)
@
.thumb_func
    asm_svc:
        svc 0
        bx lr


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   uint32_t asmSum (uint32_t firstOperand, uint32_t secondOperand)
@
@ Parametros recibidos:
@   r0: firstOperand
@   r1: secondOperand
@
@ Valor de retorno:
@   r0: resultado de la suma de firstOperand y secondOperand
@
.thumb_func
    asm_sum:
        add r0, r1  @ r0 = r0 + r1
        bx lr       @ vuelve adonde fue llamada (especificamente, si "pc"
                    @ es la direccion, en el codigo del programa, de la
                    @ instruccion "bl asm_sum" usada para saltar a
                    @ esta funcion, entonces "lr" contiene ese "pc" + 4).
                    @ el valor de retorno debe quedar en el registro r0.
                    @ En este caso, r0 es el resultado de r0 + r1.

        @ Otras alternativas para el retorno
        @ mov pc,lr
        @ bx lr
        @ push {lr} ... pop {pc}


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void asm_zeros (uint32_t *vector, uint32_t longitud);
@
@ Parametros recibidos:
@   r0: *vector
@   r1: longitud
@
.thumb_func
    asm_zeros:
        @ Registros usados
        @   r2: valor cero
        mov r2, 0           @ constante cero
    .asm_zeros_loop:
        str r2, [r0], 4     @ sizeof(uint32_t) == 4, *vector++ = r2
        subs r1, 1          @ --longitud
        bne	.asm_zeros_loop
        bx lr


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@ void productoEscalar32(uint32_t * vectorIn, uint32_t * vectorOut, uint32_t longitud, uint32_t escalar);
@
@ Parametros recibidos:
@   r0: * vectorIn
@   r1: * vectorOut
@	r2: longitud
@	r3: escalar
@
@ Valor de retorno:
@   Ninguno
@
.thumb_func
    asm_productoEscalar32:
    	push {r5}
    	push {r6}
    .loop1:
    	ldr	r5, [r0], 4
    	mul r6, r5, r3
		str r6, [r1], 4
    	subs r2, 1          @ --longitud
        bne	.loop1
        pop {r6}
    	pop {r5}
        bx lr


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@ void asm_productoEscalar16(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar);
@
@ Parametros recibidos:
@   r0: * vectorIn
@   r1: * vectorOut
@	r2: longitud
@	r3: escalar
@
@ Valor de retorno:
@   Ninguno
@
.thumb_func
    asm_productoEscalar16:
    	push {r5}
    	push {r6}
    .loop2:
    	ldrh r5, [r0], 2
    	mul r6, r5, r3
		strh r6, [r1], 2
    	subs r2, 1          @ --longitud
        bne	.loop2
        pop {r6}
    	pop {r5}
        bx lr


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@ void asm_productoEscalar12_sinUSAT(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar);
@
@ Parametros recibidos:
@   r0: * vectorIn
@   r1: * vectorOut
@	r2: longitud
@	r3: escalar
@
@ Valor de retorno:
@   Ninguno
@
.thumb_func
    asm_productoEscalar12_sinUSAT:
    	push {r5}
    	push {r6}
    .loop3:
    	ldrh r5, [r0], 2
    	mul r6, r5, r3
    	mov r5, 4095
    	cmp r6, r5
    	bls .pe12_skip1
    	mov r6, 4095
    .pe12_skip1:
		strh r6, [r1], 2
    	subs r2, 1          @ --longitud
        bne	.loop3
        pop {r6}
    	pop {r5}
        bx lr


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@ void asm_productoEscalar12(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar);
@
@ Parametros recibidos:
@   r0: * vectorIn
@   r1: * vectorOut
@	r2: longitud
@	r3: escalar
@
@ Valor de retorno:
@   Ninguno
@
.thumb_func
    asm_productoEscalar12:
    	push {r5}
    	push {r6}
    .pe12_loop3:
    	ldrh r5, [r0], 2
    	mul r6, r5, r3
    	usat r6, #12, r6
		strh r6, [r1], 2
    	subs r2, 1          @ --longitud
        bne	.pe12_loop3
        pop {r6}
    	pop {r5}
        bx lr


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@ int32_t asm_max (int32_t * vectorIn, uint32_t longitud);
@
@ Parametros recibidos:
@   r0: * vector
@   r1: longitud
@
@ Valor de retorno:
@   r0: posicion en el vector del maximo valor
@
.thumb_func
    asm_max:
    	push {r4}
    	push {r5}
    	ldr r2, [r0], 4
    	mov r3, 1
    	mov r4, 1
		subs r1, 1
        beq .skip3
	.loop5:
		add r4, 1
		ldr r5, [r0], 4
		cmp r2, r5
		bgt .skip2
		mov r2, r5
		mov r3, r4
	.skip2:
    	subs r1, 1
        bne	.loop5
    .skip3:
        mov r0, r3
        pop {r5}
        pop {r4}
    	bx lr


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@ void asm_invertir (uint16_t * vector, uint32_t longitud);
@
@ Parametros recibidos:
@   r0: * vector
@   r1: longitud
@
@ Valor de retorno:
@   Ninguno
@
.thumb_func
    asm_invertir:
        push {r4}

        subs r1, 1
        beq .skip1
    	mov r3, 2
    	mul r4, r1, r3
    	add r4, r0
    	add r1, 1
    	udiv r1, r1, r3
    .loop4:
    	ldrh r2, [r0]
    	ldrh r3, [r4]
		strh r3, [r0], 2
		strh r2, [r4], -2
    	subs r1, 1
        bne	.loop4

	.skip1:
        pop {r4}
        bx lr


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@ void filtroVentana10(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitudVectorIn)
@
@ Parametros recibidos:
@   r0: * vector
@   r1: * vector
@	r2: longitud
@
@ Valor de retorno:
@   Ninguno
@
.thumb_func
	asm_filtroVentana10:
        push {r4}
        push {r5}
        push {r6}
        push {r7}
        push {r8}

		mov r3, 0			// index

.fv_loop2:
		mov r4, 0			// avg
		mov r5, 0			// i

.fv_loop1:
		add r6, r3, r5
		cmp r6, r2
		blt .fv_skip2
		udiv r7, r6, r2
		mul r7, r7, r2
		sub r6, r6, r7

.fv_skip2:
		mov r8, 2
		mul r6, r6, r8
		add r6, r0, r6
		ldrh r8, [r6]
		add r4, r4, r8
		add r5, 1
		cmp r5, 10
		blt .fv_loop1

		mov r8, 10
		udiv r8, r4, r8
		strh r8, [r1], 2
		add r3, 1
		cmp r3, r2
		blt .fv_loop2

		pop {r8}
        pop {r7}
		pop {r6}
        pop {r5}
        pop {r4}
		bx lr


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@ void pack32to16 (int32_t * vectorIn, int16_t *vectorOut, uint32_t longitud);
@
@ Parametros recibidos:
@   r0: * vector
@   r1: * vector
@	r2: longitud
@
@ Valor de retorno:
@   Ninguno
@
.thumb_func
	asm_pack32to16:
		add r0, 2
	.pack_loop1:
		ldrh r3, [r0], 4
		strh r3, [r1], 2
    	subs r2, 1          @ --longitud
        bne	.pack_loop1
		bx lr


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@ void downsampleM (int32_t * vectorIn, int32_t * vectorOut, uint32_t longitud, uint32_t N);
@
@ Parametros recibidos:
@   r0: * vector
@   r1: * vector
@	r2: longitud
@	r3: N
@
@ Valor de retorno:
@   Ninguno
@
.thumb_func
	asm_downsampleM:
		push {r4}
		push {r5}

		mov r4, 1			// index
	.ds_loop1:
		ldr r5, [r0], 4
		cmp r4, r3
		beq .ds_skip1
		str r5, [r1], 4
		bal .ds_skip2
	.ds_skip1:
		mov r4, 0
	.ds_skip2:
		add r4, 1
		subs r2, 1
		bne .ds_loop1

		pop {r5}
		pop {r4}
		bx lr
