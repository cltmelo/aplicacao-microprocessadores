ORG 0000H               ; Início na posição 0000H
MOV P1, #0FFH           ; Desliga o display de 7 segmentos
MOV DPTR, #CODES_TABLE  ; Aponta O DPTR para a tabela de códigos de segmentos
MOV R1, #0              ; Inicializa o contador em 0
MOV DELAY, #0           ; Inicializa o tempo de delay como zero

; Verificação dos botões
main:
    ACALL CHECK_BUTTONS       ; Verifica continuamente os botões (se está pressionado ou não), ficando nessa rotina caso nenhum esteja pressionado

    ; Detectado que está pressionado, exibe o numero atual no display e realiza a contagem
    MOV A, DELAY              ; Move o valor de DELAY para o acumulador
    CJNE A, #0, CONTINUE      ; Se o DELAY for diferente de 0, continua
    MOV P1, #0FFH             ; Mantém o display desligado se nenhum botão estiver pressionado
    SJMP main                 ; Volta ao loop principal para continuar verificando

CONTINUE:
    ACALL DISPLAY_NUMBER      ; Exibe o número no display
    ACALL APPLY_DELAY         ; Executa o delay
    ACALL INCREASE_CONT       ; Incrementa o contador de números
    SJMP main                 ; Repete o loop





; Sub-rotina para verificar e configurar o delay baseado nos botões pressionados
CHECK_BUTTONS:
    JNB P2.0, SW0_ATIVO
    JNB P2.1, SW1_ATIVO
    SJMP CHECK_BUTTONS         



; Subrotinas para as configurações do delay
SW0_ATIVO:
    MOV DELAY, #5             ; Define delay de 0,25 segundos (5 ciclos de 50ms)
    RET                       ; Retorna ao loop principal para iniciar a contagem

SW1_ATIVO:
    MOV DELAY, #20            ; Define delay de 1 segundo (20 ciclos de 50ms)
    RET




; Sub-rotina para exibir o número no display
DISPLAY_NUMBER:
    MOV A, R1                 ; Carrega o número atual no acumulador
    MOVC A, @A+DPTR           ; Busca o código de exibição na tabela
    MOV P1, A                 ; Mostra o número no display
    RET


; Sub-rotina para aplicar o delay usando Timer 0
APPLY_DELAY:
    MOV R2, DELAY             ; Carrega o tempo de delay (multiplicador)
DELAY_LOOP:
    MOV TMOD, #01H            ; Configura Timer 0 no modo 1 (16-bit timer)
    MOV TH0, #3CH             ; Parte alta do Timer (ajustado para cerca de 50 ms)
    MOV TL0, #0B0H            ; Parte baixa do Timer (ajustado para cerca de 50 ms)
    SETB TR0                  ; Inicia o Timer 0
WAIT_DELAY:
    JNB TF0, WAIT_DELAY       ; Espera até que o Timer 0 transborde
    CLR TR0                   ; Para o Timer 0
    CLR TF0                   ; Limpa a flag TF0 (flag de transbordo)
    DJNZ R2, DELAY_LOOP       ; Decrementa o contador R2 e repete até completar o número de ciclos
    RET


; Sub-rotina para incrementar a contagem dos números
INCREASE_CONT:
    INC R1                     ; Incrementa o contador
    CJNE R1, #10, RETURN       ; Se ainda não chegou a 10, continua
    MOV R1, #0                 ; Se chegou a 9, reinicia a contagem em 0
RETURN:
    RET

; Tabela de códigos do display de 7 segmentos para números de 0 a 9
CODES_TABLE:
DB 0C0h
DB 0F9h
DB 0A4h
DB 0B0h
DB 99h
DB 92h
DB 82h
DB 0F8h
DB 80h
DB 90h

; Área de dados
DELAY: DB 00H                  ; Armazena o número de ciclos de delay
; Inicialmente, sem delay configurado

END                            ;acabou, mano!