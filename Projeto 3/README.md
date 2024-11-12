# Projeto 3 - Termômetro Digital com LM35 e Conversor A/D

## Repositório
Este repositório contém tanto o arquivo de simulação `circuito.simu` do circuito construído no SimulIDE quanto os arquivos `Projeto3.c` e `Projeto3.hex` do programa desenvolvido e compilado no MikroC.

## Funcionamento do Programa

O programa desenvolvido faz uso de diversas funcionalidades do microcontrolador PIC18F4550, destacando-se o uso de seu ADC interno. Além disso, destaca-se o uso de bibliotecas para o controle do ADC interno e do diplay LCD externo.

### Configuração Inicial dos Pinos

Inicialmente, modifica-se o registrador `ADCON0` de forma a configurar todos os pinos como analógicos. A seguir, é atuallizado o registrador `ADCON1` para que o pino AN3 seja utilizado como tensão de referênciaexterna positiva, enquanto o AN2 é utilizado como tensão de referência externa negativa. Por fim, o registrador `TRISA` é definido de forma que o pino AN0 seja uma entrada.

### Configuração do ADC

Além das tensões de referência externas já definidas, outros aspectos do conversor devem ser também configurados. Começamos por definir o registrador `ADCON2` para que as medidas do ADC sejam justificadas à direita, para que o clock de conversão seja FOSC / 32, e para que o tempo de conversão seja 12 TAD. A seguir, o ADC é inicializado através da função `ADC_Init_Advanced()` com o argumento `_ADC_EXTERNAL_REF`, de forma que ele empregue tensões de referência externas.

### Configuração do LCD

No início do código, diversos pinos da Porta B são configurados para comunicarem-se com o display LCD, correlacionando os pinos utilizados pela biblioteca de controle do display com os pinos físicos doo microcontrolador. Mais tarde, é chamada a função `Lcd_Init()`, a qual inicializa o módulo LCD, seguindo então com a chamada de `Lcd_Cmd()` com os parâmetros `_LCD_CLEAR`, para limpar o display, e `_LCD_CURSOR_OFF`, para desativar o cursor.

### Leitura de ADC e Escrita no LCD

O loop principal do código consiste em empregar a função `ADC_Get_Sample(0)` para obter o valor resultante da conversão da entrada AN0 do ADC, convertê-lo em uma string em formato decimal por meio de uma série de divisões, e printar a string por meio da função `Lcd_Out()`, iniciando na posição previamente definida. Destaca-se que uma parte da saída visualizada no LCD ("Temp:") é permanente, resultante de uma única chamada de `Lcd_Out()` e nunca sobrescrita.

Note especialmente que o valor medido pelo ADC é retornado em uma base de 10 bits. Concomitantemente, como o termômetro LM35 utilizado na análise apresenta variações de 10 mV / °C, sendo 1 V equivalente a 100 °C e 0 V a 0 °C. Sendo assim, para torná-lo representativo do valor real, devemos multiplicá-lo por 100 (na realidade, multiplicaremos por 1000 para aumentar a precisão) e dividí-lo por 1023. Somente a partir desse momento o valor obtido pode ser empregado na conversão para string.

## Integração com o circuito

A figura abaixo demonstra o circuito geral construído. Note que os pinos da porta B são conectados ao display LCD externo na ordem definida em código. Além disso, observe que o termômetro LM35 é representado por um potenciômetro, que varia de 0 V a 1 V, conectado ao pino AN0. Além disso, temos as tensões externas conectadas aos pinos AN2 e AN3. 

![Circuito](https://github.com/cltmelo/aplicacao-microprocessadores/blob/main/Projeto%203/circuito.png)

## Integrantes
- Lucas Corlete ALves de Melo - 13676461  
- Guilherme Lorete Schmidt - 13676857
- João Victor Breches Alves - 13677142
