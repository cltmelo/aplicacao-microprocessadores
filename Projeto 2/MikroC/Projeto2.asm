
_INTERRUPCAO:

;Projeto2.c,3 :: 		void INTERRUPCAO() iv 0x0008 ics ICS_AUTO {
;Projeto2.c,4 :: 		if(INTCON.INT0IF == 1) { // verifica se a INT0 ocorreu
	BTFSS       INTCON+0, 1 
	GOTO        L_INTERRUPCAO0
;Projeto2.c,5 :: 		T0CON = 0B10000101;; // liga o timer e configura prescaler
	MOVLW       133
	MOVWF       T0CON+0 
;Projeto2.c,6 :: 		INTCON.INT0IF = 0; //  zera flag
	BCF         INTCON+0, 1 
;Projeto2.c,7 :: 		Delay_ms(40);
	MOVLW       104
	MOVWF       R12, 0
	MOVLW       228
	MOVWF       R13, 0
L_INTERRUPCAO1:
	DECFSZ      R13, 1, 1
	BRA         L_INTERRUPCAO1
	DECFSZ      R12, 1, 1
	BRA         L_INTERRUPCAO1
	NOP
;Projeto2.c,8 :: 		}
L_INTERRUPCAO0:
;Projeto2.c,10 :: 		if(INTCON3.INT1IF == 1) { // verifica se a INT1 ocorreu
	BTFSS       INTCON3+0, 0 
	GOTO        L_INTERRUPCAO2
;Projeto2.c,11 :: 		T0CON = 0B10000011;; // liga o timer e configura prescaler
	MOVLW       131
	MOVWF       T0CON+0 
;Projeto2.c,12 :: 		INTCON3.INT1IF = 0; //  zera flag
	BCF         INTCON3+0, 0 
;Projeto2.c,13 :: 		Delay_ms(40);
	MOVLW       104
	MOVWF       R12, 0
	MOVLW       228
	MOVWF       R13, 0
L_INTERRUPCAO3:
	DECFSZ      R13, 1, 1
	BRA         L_INTERRUPCAO3
	DECFSZ      R12, 1, 1
	BRA         L_INTERRUPCAO3
	NOP
;Projeto2.c,14 :: 		}
L_INTERRUPCAO2:
;Projeto2.c,15 :: 		}
L_end_INTERRUPCAO:
L__INTERRUPCAO21:
	RETFIE      1
; end of _INTERRUPCAO

_Incrementa:

;Projeto2.c,17 :: 		void Incrementa() { // função para incrementar contador
;Projeto2.c,18 :: 		ucContador++;
	INFSNZ      _ucContador+0, 1 
	INCF        _ucContador+1, 1 
;Projeto2.c,19 :: 		switch (ucContador) {  	// acionamento do display de 7 segmentos do kit EasyPIC (PORTD)
	GOTO        L_Incrementa4
;Projeto2.c,20 :: 		case 0:{ latd = 0b00111111; break;}
L_Incrementa6:
	MOVLW       63
	MOVWF       LATD+0 
	GOTO        L_Incrementa5
;Projeto2.c,21 :: 		case 1:{ latd = 0b00000110; break;}
L_Incrementa7:
	MOVLW       6
	MOVWF       LATD+0 
	GOTO        L_Incrementa5
;Projeto2.c,22 :: 		case 2:{ latd = 0b01011011; break;}
L_Incrementa8:
	MOVLW       91
	MOVWF       LATD+0 
	GOTO        L_Incrementa5
;Projeto2.c,23 :: 		case 3:{ latd = 0b01001111; break;}
L_Incrementa9:
	MOVLW       79
	MOVWF       LATD+0 
	GOTO        L_Incrementa5
;Projeto2.c,24 :: 		case 4:{ latd = 0b01100110; break;}
L_Incrementa10:
	MOVLW       102
	MOVWF       LATD+0 
	GOTO        L_Incrementa5
;Projeto2.c,25 :: 		case 5:{ latd = 0b01101101; break;}
L_Incrementa11:
	MOVLW       109
	MOVWF       LATD+0 
	GOTO        L_Incrementa5
;Projeto2.c,26 :: 		case 6:{ latd = 0b01111101; break;}
L_Incrementa12:
	MOVLW       125
	MOVWF       LATD+0 
	GOTO        L_Incrementa5
;Projeto2.c,27 :: 		case 7:{ latd = 0b00000111; break;}
L_Incrementa13:
	MOVLW       7
	MOVWF       LATD+0 
	GOTO        L_Incrementa5
;Projeto2.c,28 :: 		case 8:{ latd = 0b01111111; break;}
L_Incrementa14:
	MOVLW       127
	MOVWF       LATD+0 
	GOTO        L_Incrementa5
;Projeto2.c,29 :: 		case 9:{ latd = 0b01101111; break;}
L_Incrementa15:
	MOVLW       111
	MOVWF       LATD+0 
	GOTO        L_Incrementa5
;Projeto2.c,30 :: 		default:{ PORTD =0; ucContador = -1; break;} // zera todo o PORTD
L_Incrementa16:
	CLRF        PORTD+0 
	MOVLW       255
	MOVWF       _ucContador+0 
	MOVLW       255
	MOVWF       _ucContador+1 
	GOTO        L_Incrementa5
;Projeto2.c,31 :: 		}
L_Incrementa4:
	MOVLW       0
	XORWF       _ucContador+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__Incrementa23
	MOVLW       0
	XORWF       _ucContador+0, 0 
L__Incrementa23:
	BTFSC       STATUS+0, 2 
	GOTO        L_Incrementa6
	MOVLW       0
	XORWF       _ucContador+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__Incrementa24
	MOVLW       1
	XORWF       _ucContador+0, 0 
L__Incrementa24:
	BTFSC       STATUS+0, 2 
	GOTO        L_Incrementa7
	MOVLW       0
	XORWF       _ucContador+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__Incrementa25
	MOVLW       2
	XORWF       _ucContador+0, 0 
L__Incrementa25:
	BTFSC       STATUS+0, 2 
	GOTO        L_Incrementa8
	MOVLW       0
	XORWF       _ucContador+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__Incrementa26
	MOVLW       3
	XORWF       _ucContador+0, 0 
L__Incrementa26:
	BTFSC       STATUS+0, 2 
	GOTO        L_Incrementa9
	MOVLW       0
	XORWF       _ucContador+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__Incrementa27
	MOVLW       4
	XORWF       _ucContador+0, 0 
L__Incrementa27:
	BTFSC       STATUS+0, 2 
	GOTO        L_Incrementa10
	MOVLW       0
	XORWF       _ucContador+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__Incrementa28
	MOVLW       5
	XORWF       _ucContador+0, 0 
L__Incrementa28:
	BTFSC       STATUS+0, 2 
	GOTO        L_Incrementa11
	MOVLW       0
	XORWF       _ucContador+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__Incrementa29
	MOVLW       6
	XORWF       _ucContador+0, 0 
L__Incrementa29:
	BTFSC       STATUS+0, 2 
	GOTO        L_Incrementa12
	MOVLW       0
	XORWF       _ucContador+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__Incrementa30
	MOVLW       7
	XORWF       _ucContador+0, 0 
L__Incrementa30:
	BTFSC       STATUS+0, 2 
	GOTO        L_Incrementa13
	MOVLW       0
	XORWF       _ucContador+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__Incrementa31
	MOVLW       8
	XORWF       _ucContador+0, 0 
L__Incrementa31:
	BTFSC       STATUS+0, 2 
	GOTO        L_Incrementa14
	MOVLW       0
	XORWF       _ucContador+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__Incrementa32
	MOVLW       9
	XORWF       _ucContador+0, 0 
L__Incrementa32:
	BTFSC       STATUS+0, 2 
	GOTO        L_Incrementa15
	GOTO        L_Incrementa16
L_Incrementa5:
;Projeto2.c,32 :: 		}
L_end_Incrementa:
	RETURN      0
; end of _Incrementa

_ConfigMCU:

;Projeto2.c,35 :: 		void ConfigMCU() {
;Projeto2.c,37 :: 		ADCON1 |= 0X0F;
	MOVLW       15
	IORWF       ADCON1+0, 1 
;Projeto2.c,40 :: 		INTCON2.RBPU = 0; //RBPU é barrado, portanto acionado em 0
	BCF         INTCON2+0, 7 
;Projeto2.c,42 :: 		TRISD = 0;  // definir porta D como saida
	CLRF        TRISD+0 
;Projeto2.c,43 :: 		PORTD = 0;  // LEDs inicialmente apagados
	CLRF        PORTD+0 
;Projeto2.c,44 :: 		TRISB.RB0 = 1; // Pino RB0/INT0 como entrada
	BSF         TRISB+0, 0 
;Projeto2.c,45 :: 		TRISB.RB1 = 1; // Pino RB1/INT1 como entrada
	BSF         TRISB+0, 1 
;Projeto2.c,47 :: 		PORTA = 0b00001111; // liga o display de 7 seg. do kit
	MOVLW       15
	MOVWF       PORTA+0 
;Projeto2.c,49 :: 		}
L_end_ConfigMCU:
	RETURN      0
; end of _ConfigMCU

_main:

;Projeto2.c,51 :: 		void main() {
;Projeto2.c,52 :: 		ConfigMCU();
	CALL        _ConfigMCU+0, 0
;Projeto2.c,55 :: 		INTCON.GIEH = 1; // Habilita interrupções
	BSF         INTCON+0, 7 
;Projeto2.c,57 :: 		RCON.IPEN = 1;  // habilita niveis de prioridade
	BSF         RCON+0, 7 
;Projeto2.c,59 :: 		INTCON.INT0IF = 0;    //Flag responsável em gerar/acionar a interrupção
	BCF         INTCON+0, 1 
;Projeto2.c,60 :: 		INTCON.INT0IE = 1;  //Habilita a interrupção específica INT0
	BSF         INTCON+0, 4 
;Projeto2.c,62 :: 		INTCON3.INT1IF = 0;    //Flag responsável em gerar/acionar a interrupção
	BCF         INTCON3+0, 0 
;Projeto2.c,63 :: 		INTCON3.INT1IP = 1; // coloca INT1 como alta prioridade
	BSF         INTCON3+0, 6 
;Projeto2.c,64 :: 		INTCON3.INT1IE = 1;  //Habilita a interrupção específica INT1
	BSF         INTCON3+0, 3 
;Projeto2.c,67 :: 		INTCON2.INTEDG0 = 1;
	BSF         INTCON2+0, 6 
;Projeto2.c,68 :: 		INTCON2.INTEDG1 = 1;
	BSF         INTCON2+0, 5 
;Projeto2.c,71 :: 		T0CON = 0B00000100;
	MOVLW       4
	MOVWF       T0CON+0 
;Projeto2.c,74 :: 		TMR0L = 0xF4;
	MOVLW       244
	MOVWF       TMR0L+0 
;Projeto2.c,75 :: 		TMR0H = 0x24;
	MOVLW       36
	MOVWF       TMR0H+0 
;Projeto2.c,77 :: 		INTCON.TMR0IF = 0 ; // flag de overflow do timer inicialmente zerada
	BCF         INTCON+0, 2 
;Projeto2.c,79 :: 		while(1) {
L_main17:
;Projeto2.c,80 :: 		if (INTCON.TMR0IF == 1) { // verifica se timer finalizou contagem
	BTFSS       INTCON+0, 2 
	GOTO        L_main19
;Projeto2.c,82 :: 		INTCON.TMR0IF = 0; // zera o flag de overflow da contagem
	BCF         INTCON+0, 2 
;Projeto2.c,83 :: 		TMR0L = 0xF4;
	MOVLW       244
	MOVWF       TMR0L+0 
;Projeto2.c,84 :: 		TMR0H = 0x24;
	MOVLW       36
	MOVWF       TMR0H+0 
;Projeto2.c,85 :: 		Incrementa();
	CALL        _Incrementa+0, 0
;Projeto2.c,86 :: 		}
L_main19:
;Projeto2.c,87 :: 		}
	GOTO        L_main17
;Projeto2.c,88 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
