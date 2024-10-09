; muda origem para 0000h
org 0000h
; jump para main
jmp main
; mudar origem para a posicao do interruptor de clock 
org 000Bh
; jump paar funcao de interrupção
jmp interrompe

org 0032h

;função main
main:
	; seta timer 0 para o modo 1 e inicia ele
	MOV TMOD, #00000001b
	MOV TCON, #00010000b
	; habilita interrupções do timer
	MOV IE, #10000010b

	;seta registradores
	MOV R0, #0
	MOV R1, #4
	MOV R2, #3	
	MOV R6, #0

;loop para aguardar interrupções
wait:
	LJMP wait

; função para atualizar o valor de r0 e colocá-lo no display
atualiza:
	; incrementar r0 
	INC R0

	; se for 10 deve voltar a 0
	CJNE R0, #0Ah, prossegue
	MOV R0, #0

	prossegue:

	; saída para o display
	ACALL display
	
	; retorna à posição anterior da stack
	RET

; roda a cada interrupção, devendo rodar 4 vezes antes de incrementar o display
; totaliza 3 * 65535 + 53392 = 250000 ciclos antes de incrementar
interrompe:
	; diminui r2 e encerra se diferente de 0 (não passou 3 interrupções)
	DJNZ R2, retorna

	PUSH ACC ;salvar ACC na stack
	MOV A, R6 ;mover R6 para ACC
	
	; se ACC não for zero, passa à impressão do display
	JNZ imprime

	; se acc for diferente de 0, coloca 53392 no timer para aguardar nova interrupção
	MOV TH0, #02Fh
	MOV TL0, #07Eh
	MOV R6, #1 ; não é mais zero, permite impressão na próxima interrupção
	MOV R2, #1

	POP ACC

	RETI

; chama a impressão do contador no display
imprime:
	; reinicia registradores
	MOV R6, #0
	MOV R2, #3

	; checa os switchs e atualiza o display
	ACALL checa_switch

	; recuperar ACC da pilha
	POP ACC

	; retorna da interrupcao para o loop de espera
	retorna:
	RETI

; funcao para realizar o display do relogio
checa_switch:
	; incrementa o contador e realiza display toda vez se switch 0 setado
	JNB P2.0, atualiza

	; garante que a atualização ocorra a cada 4 ciclos se switch 1 setado
	DJNZ R1, finaliza
	MOV R1, #4
	; atualiza contador se switch 1 setado
	JNB P2.1, atualiza
	
	; finaliza se não houver switch setado ou switch 1 setado e r1 diferente de 0
	finaliza:
	RET

; passa numero no registrador r0 ao display
; os bits que devem ser setados no display para construir o numero são movidos a P1
display:
	CJNE R0, #0, display1
	MOV P1, #11000000b
	RET
display1:
	CJNE R0, #1, display2
	MOV P1, #11111001b
	RET
display2:
	CJNE R0, #2, display3
	MOV P1, #10100100b
	RET
display3:
	CJNE R0, #3, display4
	MOV P1, #10110000b
	RET
display4:
	CJNE R0, #4, display5
	MOV P1, #10011001b
	RET
display5:
	CJNE R0, #5, display6
	MOV P1, #10010010b
	RET
display6:
	CJNE R0, #6, display7
	MOV P1, #10000010b
	RET
display7:
	CJNE R0, #7, display8
	MOV P1, #11111000b
	RET
display8:
	CJNE R0, #8, display9
	MOV P1, #10000000b
	RET
display9:
	CJNE R0, #9, display_nada
	MOV P1, #10010000b
	RET
display_nada:
	MOV P1, #11111111b
	RET