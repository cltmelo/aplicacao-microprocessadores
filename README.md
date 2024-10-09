# Projeto 1 - Cronômetro Digital usando Assembly e 8051

## Repositório
Este repositório contem o arquivo principal do programa desenvolvido: `cronometro.asm`. Além disso, traz-se uma breve descrição de seu modo de funcionamento.

## Funcionamento do Programa
O primeiro ato do programa constitui em escrever em registradores especiais para ativar o timer e habilitar que ele realize interrupções sempre que o timer alcançar seu valor máximo de 16 bits, divididos em dois registradores: TH0 e TL0. São essas interrupções geradas pelo timer que serão utilizadas para a contagem do tempo decorrido e que permitirão o funcionamento do cronômetro. Cada interrupção ocorrerá a cada 65535 ciclos de máquina, quando o timer atinge seu valor máximo e retorna a 0.

Sendo assim, o programa segue definindo valores iniciais para registradores auxiliares para contagem de interrupções, contagem do display do cronômetro, etc, e entra, por fim, em um loop infinito, onde seu único objetivo é gastar ciclos de máquina e causar interrupções pelo timer.

Portanto, quando um interrupção é chamada, a execução passa à função `interrompe`, a qual retorna imediatamente nas duas primeiras interrupções. Já na terceira, ela move o valor de 12158 para o timer, de forma que aguarde então mais um interrupção, totalizando 3 * 65536 + 53392 = 250000 ciclos de máquina gastos até este momento, ou seja, 0,25 segundos gastos. Portanto, tendo aguardado o tempo necessário para incrementar o cornômetro, nesta quarta interrupção é chamada a função `imprime`.

A função imprime redefine os registradores utilizados na contagem de interrupções e chama a função `checa_switch`, cujo objetivo é checar se o SW0 ou SW1 estão ativos e controlar o cronômetro de acordo. Caso SW0 esteja ativo, é chamada a função `atualiza`, a qual incrementa o valor no registrador armazenando o valor do display e atualiza o valor no display. Caso SW1 esteja ativo, é decrementado um registrador que conta 4 chamadas à função antes de permitir que a função `atualiza` seja invocada, garantido um delay de 1 segundo entre atualizações.

É importante destacar que a função `atualiza` também deve reiniciar o valor no registrador de contagem quando este atingir 10. Por sua vez, determinado o valor correto a expor, ela chama a função `display` que constitui em uma grande lista de testes, checando se o valor do display corresponde a cada um entre 0 e 9, e move o código de 8 bits correspondente ao seu formato para a porta 1, de forma a acender os leds corretos do display de 7 segmentos.

Finalizando isso, retorna-se da interrupção e continua-se no loop infinito da main, gastando ciclos até uma nova interrupção.

O esquemático abaixo mostra como os 8 bits da porta 1 se ligam ao display de 7 segmentos, justificando os códigos empregdos para sua ativação. 

![Logic Diagram](https://github.com/cltmelo/aplicacao-microprocessadores/blob/main/Logic%20Diagram.png)

## Integrantes
- Lucas Corlete ALves de Melo - 13676461  
- Guilherme Lorete Schmidt - 13676857
