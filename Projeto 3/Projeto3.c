// config. dos pinos para o LCD
// pinos utilizados para comunicação com o display LCD
sbit LCD_RS at LATB4_bit; // pino 4 do PORTB interligado ao RS do display
sbit LCD_EN at LATB5_bit; // pino 5 do PORTB " " ao EN do display
sbit LCD_D4 at LATB0_bit; // pino 0 do PORTB ao D4
sbit LCD_D5 at LATB1_bit;  // " "
sbit LCD_D6 at LATB2_bit;  // " "
sbit LCD_D7 at LATB3_bit;  // " "
// direção do fluxo de dados nos pinos selecionados
sbit LCD_RS_Direction at TRISB4_bit;  // direção do fluxo de dados do pino RB4
sbit LCD_EN_Direction at TRISB5_bit;  // " "
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;

/*Programa Principal*/

void main(){
  unsigned int Valor_ADC = 0;  // var. para leitura
  unsigned char Tensao[10]; // arranjo textual para exibir no display

  //lembrando que os pinos agora devem ser configurados como analógicos
  TRISA.RA0 = 1;
  ADCON0 = 0B00000001; // AN0 -> AD ligado, leitura deslig., canal AN0
  ADCON1 = 0B00010000; // configura todos os canais como ADC e utiliza a tensão de referência externa vref+
  ADCON2 = 0B10101010; // justificativa para direita, FOSC/32 (tempo entre 2 e 25 us)

  // Configuração do módulo LCD
  Lcd_Init(); // inicializa a lib. Lcd
  Lcd_Cmd(_LCD_CLEAR); // limpa display
  Lcd_Cmd(_LCD_CURSOR_OFF); // desliga cursor
  Lcd_Out(1,1,"Temp:"); // escreve na Linha x Coluna do LCD um texto padrão

  ADC_Init_Advanced(_ADC_EXTERNAL_VREFH);  // inicializa módulo adc interno empregando uma tensão externa positiva de referência no pino VREF+

 while(1) {
    Valor_ADC = ADC_Get_Sample(0); // lê entrada no canal analógico 0

    // ajustes de escala dos valores de conversão
    Valor_ADC = Valor_ADC * (1000/1023.); // formata o valor de entrada

    // formata cada valor a ser exibido no display no formato "00.00"
    Tensao[0] = (Valor_ADC/1000) + '0';
    Tensao[1] = (Valor_ADC/100)%10 + '0';
    Tensao[2] = (Valor_ADC/10)%10 + '0';
    Tensao[3] = '.';
    Tensao[4] = (Valor_ADC/1)%10 + '0';
    Tensao[5] = ' ';
    Tensao[6] = 'C';
    Tensao[7] = 0; // terminador NULL (ultima posição da matriz)

    // Exibir os valores na config. acima no display LCD:
    Lcd_Out(1,6,Tensao); // mostra os valores no display a partir da linha 1 e coluna 6
    Delay_ms(20);   // delay para atualizar display
  }
}
