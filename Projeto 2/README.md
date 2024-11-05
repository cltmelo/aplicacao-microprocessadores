# Projeto 2 - Cronômetro Digital com Timer e Interrupções

## Repositório
Este repositório contém tanto o arquivo de simulação `circuito.simu` do circuito construído no SimulIDE quanto os arquivos `Projeto2.c` e `Projeto2.hex` do programa desenvolvido e compilado no MikroC.

## Funcionamento do Programa

O programa desenvolvido faz uso de diversas funcionalidades do microcontrolador PIC18F4550, destacando-se o uso de timers internos e interrupções externas.

### Configuração dos Pinos

Realizemos uma análise minuciosa do programa desenvolvido. Iniciando na função `main`, seu primeiro chamado trata-se da função `ConfigMCU`, responsável por configurar as portas do microcontrolador. Inicialmente, as portas são definidas como digitais através do registrodor `ADCON1`, e os resistores de pull-up internos são ativados por meio do registrador `INTCON2`. A seguir, a porta D é definida como saída por meio do registrador `TRISD` e assume o valor inicial de 0, tratando-se do local onde será conectado o display de 7 segmentos. Por fim, os pinos RB0 e RB1 são definidos como entradas e o valor da porta A é definido de forma a ligar o display no kit EasyPIC.

### Configuração de Interrupts

Seguindo-se à configuração das portas, é chamada a função `ConfigInterrupts`, ativando e configurando as interrupções relevantes ao programa. Sendo assim, a flag `GIEH` do registrador `INTCON` é acessada de forma a habilitar o uso de interrupções, continuando ao habilitar os níveis de prioridade através da flag `IPEN` do registrador `RCON`. Prosseguindo, as flags `INT0IE` e `INT1IE` dos registradores `INTCON` e `INTCON3`, respectivamente, têm seu valor definido de forma a habilitar as interrupções INT0 e INT1, relacionadas às portas RB0 e RB1. De forma similar, as flags de interrupação `INT0IF` e `INT1IF` desses mesmos registradores são inicialmente definidas como 0 (desativadas). Quanto ao momento de ativação, as flags `INTEDG0` e `INTEDG1` do registrador `INTCON2` são definidas de forma que as respectivas interrupções sejam ativadas na borda de subida, ou seja, ao soltar o botão na configuração pull-up utilizada. Finalizando a configuração de interrupções externas, a prioridade da interrupção INT1 é definida como alta através da flag `INT1IP` do registrador `INTCON3` (note que a interrupção INT0 é de prioridade alta por padrão). Por fim, habilita-se a interrupção relativa ao timer TMR0 através da flag `TMR0IE` do registrador `INTCON`.

### Configuração do Timer

Continuando com as preparações, agora configurando-se o timer TMR0 do microcontrolador. Primeiramente, o registrador `T0CON` é definido com as configurações gerais do timer, ativando seu prescaler, colocando-o no modo 16 bits, empregando clock interno, incrementando na borda de subida do clock e inicialmente desligado (o valor de prescaler não é relevante no momento). Note que a flag de overflow também é inicialmente definida como 0. A seguir, o valor inicial do timer é definido como 0x0BDC, ou 3036, o que nos dá 65536 - 3036 = 62500 incrementos antes de overflow no timer. Sendo assim, ao considerar um intervalo de 0.5 microssegundos para um ciclo de clock, vemos que um prescaler de 32 nos dá 0.5 * 32 * 62500 = 1 000 000 microssegundos (1 segundo) até overflow, enquanto um prescaler de 8 promove 0.5 * 8 * 62500 = 250 000 microssegundos (0.25 segundo) até o overflow, sendo estes os dois períodos de tempo desejados para o incremento do valor no display de 7 segmentos.

### Lidando com interrupções

Portanto, como último comando da `main`, temos um loop infinito, de forma que o programa permanecerá nele até uma interrupção. Prosseguindo então para o modo como o programa lida com interrupções, iniciemos pela interrupção do TMR0: quando a interrupção for chamada, a flag é novamente desativada e o valor inicial do timer é redefinido para 0x0BDC, finalizando com o chamado da função `Incrementa`, a qual incrementa o contador interno do programa (reiniciando ao chegar em 9) e configura a porta D de forma que o display de 7 segmentos mostre o número no contador (cada pino corresponde a um segmento do display, bastando configurá-lo como ligado ao desligado conforme o número a ser mostrado). A seguir, temos a interrupção INT0, que além de redefinir sua flag também configura o prescaler do TMR0 para 32, tornando a contagem total do timer 1 segundo, e ativa o timer. Por fim, a interrupção INT1 redefine sua própria flag e configura o prescaler do TMR0 para 8, tornando a contagem total 0.25 segundo, como já discutido, também ativando o timer.

## Integração com o circuito

A figura abaixo demonstra o circuito geral construído. Note que os pinos da porta D são conectados ordenadamente ao display de 7 segmentos, de forma que o microcontrolador possa mostrar seu contador interno conforme as especificações desejadas. Observe também que os botões conectados aos pinos RB0 e RB1 são responsáveis pelas interrupções INT0 e INT1, respectivamente, e que empregam os resistores de pull-up internos ao microcontrolador.

![Circuito](https://github.com/cltmelo/aplicacao-microprocessadores/blob/main/Projeto%202/figura.png)

## Comparações entre implementações

Vantagens:
- A linguagem C, por ser de alto nível, possui uma sintaxe muito mais intuitiva e fácil de aprender, que resulta numa facilidade maior na leitura, escrita e manutenção do código. A adaptabilidade também é uma vantegm a ser considerada, já que permite que o código seja adaptado para outro microcontroladores com menos esforço. A vasta gama de bibliotecas, quando usadas, acelera significativamente o processo de desenvolvimento.
  
Desvantagens:
- A linguagem C peca em questão de eficiencia em termos de tamanho e velocidade de execução quando comparado ao assembly. Também há uma complexidade muito maior do compilador, podendo exigir mais recursos do microcontrolador. Além disso, sendo de alto nível, C não permite um controle tão preciso sobre o hardware quanto o assembly.

## Integrantes
- Lucas Corlete ALves de Melo - 13676461  
- Guilherme Lorete Schmidt - 13676857
- João Victor Breches Alves - 13677142
