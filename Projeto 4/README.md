# Projeto 4 - Controle PWM e Comunicação 

## Repositório
Este repositório contém duas pastas, cada uma referente a um programa proposto no projeto 4 da disciplina de apliação em microprocessadores. Dentro de cada pasta há o arquivo `.ino` com o código fonte juntos das imagens dos resultados (que também serão apresentadas neste documento).

## Funcionamento dos Programas
Para o primeiro programa, o arquivo `.ino` possui um código em C para o microcontrolador ESP32, configurado para, através da interação dos usuários com os botões e potenciômetro, seja controlado um servo motor com dois modos: manual e automático. Um display OLED nos dá o retorno visual sobre os acontecimentos no sistema.

Já para o segundo programa, um LED RGB é controlado usando PWM, ou modulação por largura de pulso. A intensidade de cada uma das três cores do RGB é definida por um duty cycle, que varia continuamente no intervalo.

## Programa 1
Como já explicado, o programa controla um servo moto usando três botões: manual, automático e stop. Cada botão define o modo que o servo irá funcionar e o display nos retorna visualmente o estado visual de todo o sistema.

### Modo manual
Nesse modo, o servo motor é controlado utilizando o potenciômetro. O valor lido do potenciômetro altera a posição do servo, podendo ser definido de 0 a 180 graus. O display nos mostra a posição (de 0 a 180 graus), o modo manual ativo e a origem do controle.
### Modo automático
No modo automático o servo se move sozinho de 0 a 180 graus e depois faz o caminho inverso. O display nos retorna o modo automático como ativo, a posição do ângulo do servo e a direção.
### Modo stop
O botão stop para todo o funcionamento do sistema, definindo o ângulo como 0° e pausando qualquer ação.

### Implementação no código
Temos três botões que são chamados de `BUTTON_LOOP` (define modo automático), `BUTTON_MANUAL` (define modo manual) e `BUTTON_STOP` (desativa o sistema). Para o servo motor, foi importada a biblioteca `ESP32Servo` para garantir controle do dispositivo.

Para as funções, temos `setup()`, que inicializa os principais dispositivos do circuito, como display, servo, botões, etc.
A função `loop()` acompanha as interações com botões e alterna entre os três modos possíveis do sistema. A `automaticMode()` faz o controle do servo no modo automático e a `manualMode()`faz o mesmo para o modo manual. `updateDisplayAndSerial()` faz a atualização do display e do serial para mostrar o modo atual em tempo real.

### Circuito 1 
![circuito 1](<Programa 1/circuito 1.png>)

### Serial no modo automático
![serial](<Programa 1/Automático.png>)

### Serial no modo Manual
![serial](<Programa 1/Manual.png>)


## Programa 2
Nesse programa, um LED RGB é controlado usando PWM e a intensidade de suas cores é definida por um duty cycle que varia continuamente.

Através da biblioteca analogWrite são controlados os pinos de PWM do ESP32. O brilho dos LEDs é definido por um incremente variante (de 0 a 255). 

Todos os valores são expostos no display.

### Implementação no código
O controle do LED RGB é feito por PWM,  utilizando os pinos 5, 16 e 17. A configuração do PWM é feita com um frequência de 5kHz e 8 bits de resolução.

As prinipais funções utilizadas são: `loop()`, que cria a animação de transição das cores usando os ciclos de trabalho dos LEDs; e `setup()` que incializa as principais configurações, como pinos do PWM e comunicação serial.

No código `.ino` é utilizada a função já citada anteriormente `analogWrite()`, que ajusta o valor de duty cycle para cada cor do LED.

Para o código `ESP-IDF`, temos: `ledc_timer_config()`, que configura o temporizador PWM, `ledc_channel_config()`, que configura os canais PWM de cada cor e `ledc_set_duty()` que ajusta o ciclo de trabalho para cada cor.

### Circuito 2
![Circuito 2](<Programa 2/circuito 2.png>)

### Serial no modo automático
![serial](<Programa 2/serial.png>)


## Integrantes 
- Guilherme Lorete Schmidt - 13676857
- João Victor Breches Alves - 13677142
- Lucas Corlete ALves de Melo - 13676461
- Daniel Dias Silva Filho - 13677114
