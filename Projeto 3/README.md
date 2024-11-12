# Projeto 3 - Termômetro Digital com LM35 e Conversor A/D

## Repositório
Este repositório contém tanto o arquivo de simulação `circuito.simu` do circuito construído no SimulIDE quanto os arquivos `Projeto3.c` e `Projeto3.hex` do programa desenvolvido e compilado no MikroC.

## Funcionamento do Programa

O programa desenvolvido faz uso de diversas funcionalidades do microcontrolador PIC18F4550, destacando-se o uso de seu ADC interno. Além disso, destaca-se o uso de bibliotecas para o controle do ADC interno e do diplay LCD externo.

### Configuração dos Pinos

Inicialmente, modifica-se o registrador `ADCON0` de forma a configurar todos os pinos como analógicos. A seguir, é atuallizado o registrador `ADCON1` para que o pino AN3 seja utilizado como tensão de referência para o ADC do microcontrolador.

## Integração com o circuito

A figura abaixo demonstra o circuito geral construído. Note que os pinos da porta D são conectados ordenadamente ao display de 7 segmentos, de forma que o microcontrolador possa mostrar seu contador interno conforme as especificações desejadas. Observe também que os botões conectados aos pinos RB0 e RB1 são responsáveis pelas interrupções INT0 e INT1, respectivamente, e que empregam os resistores de pull-up internos ao microcontrolador.

![Circuito](https://github.com/cltmelo/aplicacao-microprocessadores/blob/main/Projeto%203/circuito.png)

## Integrantes
- Lucas Corlete ALves de Melo - 13676461  
- Guilherme Lorete Schmidt - 13676857
- João Victor Breches Alves - 13677142
