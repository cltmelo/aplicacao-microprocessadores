#include <Wire.h>               // Biblioteca para comunicação I2C
#include <Adafruit_GFX.h>        // Biblioteca para gráficos no display OLED
#include <Adafruit_SSD1306.h>    // Biblioteca específica para o display OLED SSD1306
#include <ESP32Servo.h>          // Biblioteca para controlar o servo motor com ESP32

// Configuração do display OLED
#define SCREEN_WIDTH 128         // Largura do display OLED
#define SCREEN_HEIGHT 64         // Altura do display OLED
#define OLED_RESET -1            // Não estamos utilizando pino de reset
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  // Inicializa o display OLED

// Configuração do Servo
Servo servoMotor;              // Cria um objeto servoMotor para controlar o servo
#define SERVO_PIN 26            // Define o pino 26 para o controle do servo motor

// Configuração dos botões
#define BUTTON_LOOP 12          // Define o pino 12 para o botão de controle do modo automático
#define BUTTON_MANUAL 14        // Define o pino 14 para o botão de controle do modo manual
#define BUTTON_STOP 23          // Define o pino 23 para o botão de desligar o sistema
bool loopActive = false;       // Variável para verificar se o modo automático está ativado
bool manualActive = false;     // Variável para verificar se o modo manual está ativado
bool systemActive = true;      // Variável para verificar se o sistema está ativo

#define POT_PIN 34              // Define o pino 34 para o potenciômetro (controle manual do servo)

void setup() {
  Serial.begin(115200);         // Inicializa a comunicação serial com a taxa de 115200 bps

  // Inicializa o display OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Verifica se o display foi inicializado com sucesso
    Serial.println(F("Falha ao inicializar o display OLED"));  // Exibe erro caso falhe
    for (;;);  // Entra em loop infinito se falhar
  }

  // Inicializa o servo motor
  servoMotor.attach(SERVO_PIN);  // Associa o servo motor ao pino definido

  // Configuração dos botões
  pinMode(BUTTON_LOOP, INPUT_PULLUP);   // Define o pino do botão LOOP com resistência de pull-up
  pinMode(BUTTON_MANUAL, INPUT_PULLUP); // Define o pino do botão MANUAL com resistência de pull-up
  pinMode(BUTTON_STOP, INPUT_PULLUP);   // Define o pino do botão STOP com resistência de pull-up

  display.display();              // Atualiza o display com o que foi configurado
  delay(2000);                    // Aguarda 2 segundos antes de limpar o display
  display.clearDisplay();         // Limpa o display
  display.setTextSize(1);         // Define o tamanho do texto
  display.setTextColor(SSD1306_WHITE);  // Define a cor do texto para branco
  display.setCursor(0, 0);        // Define a posição inicial do texto
  display.println(F("Hello World!"));  // Exibe "Hello World!" no display
  display.display();              // Atualiza o display com o texto
}

void loop() {
  // Verifica se o botão STOP foi pressionado
  if (digitalRead(BUTTON_STOP) == LOW) {  // Se o botão STOP for pressionado (LOW)
    systemActive = false;  // Desliga o sistema
    loopActive = false;    // Desativa o modo automático
    manualActive = false;  // Desativa o modo manual
    servoMotor.write(0);   // Reseta o servo para a posição 0 graus
    updateDisplayAndSerial("Sistema desligado", 0, "OFF");  // Atualiza o display e envia informação via serial
    delay(300);  // Aguarda 300 milissegundos
  }

  if (!systemActive) return;  // Se o sistema estiver desligado, sai da função loop

  // Modo automático
  if (digitalRead(BUTTON_LOOP) == LOW) {  // Se o botão LOOP for pressionado (LOW)
    loopActive = true;    // Ativa o modo automático
    manualActive = false; // Desativa o modo manual
    delay(300);           // Aguarda 300 milissegundos
  }

  // Modo manual
  if (digitalRead(BUTTON_MANUAL) == LOW) {  // Se o botão MANUAL for pressionado (LOW)
    manualActive = true;   // Ativa o modo manual
    loopActive = false;    // Desativa o modo automático
    delay(300);            // Aguarda 300 milissegundos
  }

  // Chama as funções de controle conforme o modo ativado
  if (loopActive) automaticMode();  // Chama o modo automático se loopActive for verdadeiro
  if (manualActive) manualMode();  // Chama o modo manual se manualActive for verdadeiro
}

// Função para o movimento automático do servo
void automaticMode() {
  // Move o servo de 0 a 180 graus
  for (int angle = 0; angle <= 180; angle += 1) {
    if (!loopActive) return;  // Se o modo automático for desativado, interrompe o movimento
    servoMotor.write(angle);  // Move o servo para o ângulo atual
    updateDisplayAndSerial("Automatico", angle, "->");  // Atualiza o display e envia via serial
    delay(100);  // Aguarda 100 milissegundos
  }

  delay(1000);  // Aguarda 1 segundo antes de inverter o movimento

  // Move o servo de 180 a 0 graus
  for (int angle = 180; angle >= 0; angle -= 1) {
    if (!loopActive) return;  // Se o modo automático for desativado, interrompe o movimento
    servoMotor.write(angle);  // Move o servo para o ângulo atual
    updateDisplayAndSerial("Automatico", angle, "<-");  // Atualiza o display e envia via serial
    delay(200);  // Aguarda 200 milissegundos
  }
}

// Função para o controle manual do servo com potenciômetro
void manualMode() {
  int potValue = analogRead(POT_PIN);  // Lê o valor do potenciômetro (0 a 4095)
  int angle = map(potValue, 0, 4095, 0, 180);  // Mapeia o valor para o intervalo de 0 a 180 graus
  servoMotor.write(angle);  // Define o ângulo do servo conforme o valor do potenciômetro
  updateDisplayAndSerial("Manual", angle, "Pot");  // Atualiza o display e envia via serial
  delay(100);  // Aguarda 100 milissegundos
}

// Função para atualizar o display OLED e a comunicação serial
void updateDisplayAndSerial(const char *mode, int angle, const char *direction) {
  Serial.print("Modo: ");
  Serial.println(mode);  // Exibe o modo atual no terminal serial
  Serial.print("Angulo: ");
  Serial.println(angle);  // Exibe o ângulo do servo no terminal serial
  Serial.print("Sentido: ");
  Serial.println(direction);  // Exibe o sentido do movimento no terminal serial

  display.clearDisplay();  // Limpa o display OLED
  display.setCursor(0, 0);  // Define a posição inicial do texto no display
  display.println(F("Modo: "));  // Exibe o texto "Modo: "
  display.println(mode);  // Exibe o modo atual no display
  display.println(F("Angulo: "));  // Exibe o texto "Angulo: "
  display.println(angle);  // Exibe o ângulo no display
  display.println(F("Sentido: "));  // Exibe o texto "Sentido: "
  display.println(direction);  // Exibe o sentido no display
  display.display();  // Atualiza o display com as novas informações
}
