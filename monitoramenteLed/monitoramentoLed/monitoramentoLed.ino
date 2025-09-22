#include "AdafruitIO_WiFi.h"
#include "NewPing.h"

// Configurações da sua conta Adafruit IO
// #define IO_USERNAME ""
// #define IO_KEY ""

// Configurações de rede Wi-Fi
// #define WIFI_SSID ""
// #define WIFI_PASS ""

// Cria objeto de conexão com o Adafruit IO
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Cria referência ao feed
AdafruitIO_Feed *botaoalarme = io.feed("botaoalarme");
AdafruitIO_Feed *distanciaultrassom = io.feed("distanciaultrassom");

// Define os pinos dos componentes
#define LED_PIN 13
#define BUZZER_PIN 27
#define BOTAO_FISICO 26
#define TRIG_PIN 12
#define ECHO_PIN 14

// Configuração do sensor ultrassônico
#define MAX_DISTANCE 100
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// Variáveis de controle
bool alarmeAtivo = false;
unsigned int distancia = 0;
const int LIMITE_DISTANCIA = 15;

void setup() {
  // Inicializa comunicação serial
  Serial.begin(115200);

  // Configura pinos como saída ou entrada
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BOTAO_FISICO, INPUT);

  while (!Serial)
    ;

  delay(1000);

  // Conecta ao Adafruit IO
  Serial.print("Conectando ao Adafruit IO");
  io.connect();

  // Aguarda a conexão
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("Conectado ao Adafruit IO!");

  // Vincula a função callback ao feed
  botaoalarme->onMessage(handleAlarme);

  // Solicita o estado inicial do alarme
  Serial.println("Solicitando o estado inicial do alarme...");
  botaoalarme->get();

  delay(1000);
}

void loop() {
  // Mantém a conexão ativa
  io.run();

  // Leitura do botão físico
  if (digitalRead(BOTAO_FISICO) == 1) {
    delay(300);  // debounce simples
    alarmeAtivo = !alarmeAtivo;

    botaoalarme->save(String(alarmeAtivo ? "true" : "false"));
    Serial.println(alarmeAtivo ? "Alarme ARMADO pelo botao fisico." : "Alarme DESARMADO pelo botao fisico.");
  }

  distancia = sonar.ping_cm();
  Serial.print("Distancia lida: ");
  Serial.println(distancia);
  Serial.println(" cm");
  if(distancia != 0){
    //só envia distancias válidas
    distanciaultrassom -> save(distancia);

  }
  
  // Ativação ou desativação do alarme
  if (alarmeAtivo && distancia > 0 && distancia < LIMITE_DISTANCIA) {
    ativarAlerta();
  } else {
    desligarAlerta();
  }
}

// Função chamada sempre que houver alteração no feed
void handleAlarme(AdafruitIO_Data *data) {
  String valor = data->toString();
  if (valor == "true") {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED LIGADO");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED DESLIGADO");
  }
}

// Função para ativar o alerta (ligar LED e buzzer)
void ativarAlerta() {
  digitalWrite(BUZZER_PIN, HIGH);  // Liga o buzzer
  digitalWrite(LED_PIN, HIGH);     // Liga o LED
  Serial.println("Alerta Ativado!");
}

// Função para desligar o alerta (desligar LED e buzzer)
void desligarAlerta() {
  digitalWrite(BUZZER_PIN, LOW);   // Desliga o buzzer
  digitalWrite(LED_PIN, LOW);      // Desliga o LED
  Serial.println("Alerta Desativado!");
}
