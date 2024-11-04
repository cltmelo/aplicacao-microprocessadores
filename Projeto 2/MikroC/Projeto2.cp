#line 1 "C:/Users/13676857/Downloads/Projeto 2/MikroC/Projeto2.c"
int ucContador = -1;

void INTERRUPCAO() iv 0x0008 ics ICS_AUTO {
 if(INTCON.INT0IF == 1) {
 T0CON = 0B10000101;;
 INTCON.INT0IF = 0;
 Delay_ms(40);
 }

 if(INTCON3.INT1IF == 1) {
 T0CON = 0B10000011;;
 INTCON3.INT1IF = 0;
 Delay_ms(40);
 }
}

void Incrementa() {
 ucContador++;
 switch (ucContador) {
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
 default:{ PORTD =0; ucContador = -1; break;}
 }
}


void ConfigMCU() {

 ADCON1 |= 0X0F;


 INTCON2.RBPU = 0;

 TRISD = 0;
 PORTD = 0;
 TRISB.RB0 = 1;
 TRISB.RB1 = 1;

 PORTA = 0b00001111;

}

void main() {
 ConfigMCU();


 INTCON.GIEH = 1;

 RCON.IPEN = 1;

 INTCON.INT0IF = 0;
 INTCON.INT0IE = 1;

 INTCON3.INT1IF = 0;
 INTCON3.INT1IP = 1;
 INTCON3.INT1IE = 1;


 INTCON2.INTEDG0 = 1;
 INTCON2.INTEDG1 = 1;


 T0CON = 0B00000100;


 TMR0L = 0xF4;
 TMR0H = 0x24;

 INTCON.TMR0IF = 0 ;

 while(1) {
 if (INTCON.TMR0IF == 1) {

 INTCON.TMR0IF = 0;
 TMR0L = 0xF4;
 TMR0H = 0x24;
 Incrementa();
 }
 }
}
