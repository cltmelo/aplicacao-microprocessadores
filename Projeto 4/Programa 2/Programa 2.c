// Definições dos pinos GPIO para as cores do LED RGB (cátodo comum)
#define LED_PIN_R 5  // Pino do Red (Vermelho)
#define LED_PIN_G 16  // Pino do Green (Verde)
#define LED_PIN_B 17  // Pino do Blue (Azul)

void setup() {
  // Inicialização da comunicação serial com a taxa de 115200 bps
  Serial.begin(115200);
  
  // Configuração dos pinos de saída para o controle das cores do LED
  pinMode(LED_PIN_R, OUTPUT);  // Define o pino do Red como saída
  pinMode(LED_PIN_G, OUTPUT);  // Define o pino do Green como saída
  pinMode(LED_PIN_B, OUTPUT);  // Define o pino do Blue como saída
}

void loop() {
  // Variável estática para controlar o incremento do brilho das cores do LED
  static uint8_t incremento = 0;

  // Calcular o duty cycle (valor de PWM) para cada cor do LED com base no incremento
  uint32_t duty_r = incremento * 2; // Duty cycle para a cor Red
  uint32_t duty_g = incremento;     // Duty cycle para a cor Green
  uint32_t duty_b = incremento * 3; // Duty cycle para a cor Blue

  // Atualizar os valores de PWM para controlar o brilho das cores do LED
  analogWrite(LED_PIN_R, duty_r);  // Aplica o valor de PWM para a cor Red
  analogWrite(LED_PIN_G, duty_g);  // Aplica o valor de PWM para a cor Green
  analogWrite(LED_PIN_B, duty_b);  // Aplica o valor de PWM para a cor Blue

  // Exibir no Monitor Serial os valores atuais do incremento e dos duty cycles de cada cor
  Serial.print("Incremento: ");
  Serial.println(incremento);  // Exibe o valor do incremento no Monitor Serial
  Serial.print("Duty cycle - R: ");
  Serial.print(duty_r * 100 / 255);  // Exibe o valor do duty cycle da cor Red em percentual
  Serial.print("%, G: ");
  Serial.print(duty_g * 100 / 255);  // Exibe o valor do duty cycle da cor Green em percentual
  Serial.print("%, B: ");
  Serial.print(duty_b * 100 / 255);  // Exibe o valor do duty cycle da cor Blue em percentual
  Serial.println("%");

  // Incrementar o valor de incremento para alterar o brilho das cores do LED
  incremento += 5;  // Aumenta o valor do incremento em 5 a cada loop
  if (incremento > 255) {  // Se o valor do incremento ultrapassar 255
    incremento = 0;  // Reseta o valor do incremento para 0
  }

  delay(100); // Aguarda 100 milissegundos antes de repetir o loop
}
