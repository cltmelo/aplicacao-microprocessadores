int ucContador = -1; // variável global para contador do display

void Incrementa() { // função para incrementar contador e atualizar display
	ucContador++; // incrementa contador
	if(ucContador > 9) // retorna contador a 0 caso este ultrapasse 9
		ucContador = 0;

	switch (ucContador) { // acionamento do display de 7 segmentos do kit EasyPIC (PORTD)
		case 0:{ latd = 0b00111111; break;}
		case 1:{ latd = 0b00000110; break;}
		case 2:{ latd = 0b01011011; break;}
		case 3:{ latd = 0b01001111; break;}
		case 4:{ latd = 0b01100110; break;}
		case 5:{ latd = 0b01101101; break;}
		case 6:{ latd = 0b01111101; break;}
		case 7:{ latd = 0b00000111; break;}
		case 8:{ latd = 0b01111111; break;}
		case 9:{ latd = 0b01101111; break;}
		default:{ PORTD =0; ucContador = -1; break;} // zera todo o PORTD em caso de entrada inválida
	}
}

void INTERRUPCAO() iv 0x0008 ics ICS_AUTO {
	if(INTCON.TMR0IF == 1) { // verifica se timer finalizou contagem
		INTCON.TMR0IF = 0; // zera o flag de overflow da contagem

		// valores iniciais carregados no timer para contagem até 1s na razão 32 e modo 16 bits
		TMR0L = 0xDC;
		TMR0H = 0x0B;

		// incrementa valor no display de 7 segmentos
		Incrementa();
	}
	if(INTCON.INT0IF == 1) { // verifica se a interrupção INT0 ocorreu
		T0CON = 0B10000100; // liga o timer e configura prescaler para 32, contando 1s
		INTCON.INT0IF = 0; // zera flag de interrupção
	}

	if(INTCON3.INT1IF == 1) { // verifica se a interrupção INT1 ocorreu
		T0CON = 0B10000010;; // liga o timer e configura prescaler para 8, contando 0.25s
		INTCON3.INT1IF = 0; // zera flag de interrupção
	}
}

void ConfigMCU() {
	// configura pinos do microcontrolador como digitais
	ADCON1 |= 0X0F;

	// habilita resistores de pull-up internos do PORTB
	INTCON2.RBPU = 0; // RBPU é barrado, portanto acionado em 0

	TRISD = 0;  // definir porta D como saida
	PORTD = 0;  // LEDs inicialmente apagados
	TRISB.RB0 = 1; // Pino RB0/INT0 como entrada
	TRISB.RB1 = 1; // Pino RB1/INT1 como entrada

        TRISA = 0; // definir porta A como saída
	PORTA = 0b00001111; // liga o display de 7 segmentos do kit
}

void ConfigInterrupt() {
	// configuração global das interrupções GIE
	INTCON.GIEH = 1; // habilita interrupções

	RCON.IPEN = 1; // habilita niveis de prioridade

	INTCON.INT0IF = 0; // flag responsável por gerar/acionar a interrupção INT0
	INTCON.INT0IE = 1; // habilita a interrupção específica INT0

	INTCON3.INT1IF = 0; // flag responsável por gerar/acionar a interrupção INT1
	INTCON3.INT1IP = 1; // coloca INT1 como alta prioridade
	INTCON3.INT1IE = 1; // habilita a interrupção específica INT1

	// ativa interrupções ao soltar o botão (rising edge)
	INTCON2.INTEDG0 = 1;
	INTCON2.INTEDG1 = 1;

	// ativa interrupção do timer 0
	INTCON.TMR0IE = 1;
}

void main() {
	ConfigMCU();
	ConfigInterrupt();

	// configura timer, inicialmente desligado
	T0CON = 0B00000100;

	// valores iniciais carregados no timer para contagem até 1s na razão 32 e modo 16 bits
	TMR0L = 0xDC;
	TMR0H = 0x0B;

	// flag de overflow do timer inicialmente zerada
	INTCON.TMR0IF = 0 ;

	// prende execução neste loop
	while(1);
}