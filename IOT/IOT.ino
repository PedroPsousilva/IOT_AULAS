#include <math.h>
#include "AdafruitIO_WiFi.h"
#include "NewPing.h"

// #define WIFI_SSID "Adriano"  // Config da rede wifi
// #define WIFI_PASS "..."  // Config da rede wifi

// // Autenticação Adafruit IO
// #define IO_USERNAME  "Pedro0807"
// #define IO_KEY       "..."
// AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

#define pinNTC 34
#define pinLed 14
#define BUZZER_PIN 27
#define LED_ALARME 13
#define BOTAO_FISICO 26
#define TRIG_PIN 12
#define ECHO_PIN 14

//Configuração do ultrassonico
#define MAX_DISTANCE 100
NewPing sonar(TRIG_PIN, ECHO_PIN,MAX_DISTANCE);


//Controle de envio de dados
float temp_atual = 0;
float temp_anterior = -1;

// Variavel / ponteiro para referenciar o fees temperatura
// AdafruitIO_Feed* temperatura = io.feed("temperatura");

const float Rfixo = 10000.0;  // resistor do projeto
const float Beta = 3950.0;
const float R0 = 10000.0;        //nominal do ntc
const float T0_kelvin = 298.15;  // 25°C em Kelvin
const float Vcc = 3.3;

void setup() {
  pinMode(pinNTC, INPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_ALARME, OUTPUT); 
  pinMode(BOTAO_FISICO, INPUT); 


  while (!Serial);

  Serial.begin(115200);

  // while (!Serial)
  //   ;

  // Serial.print("Conectando ao Adafruit IO");
  // io.connect();

  // while (io.status() < AIO_CONNECTED) {
  //   Serial.print(".");
  //   delay(500);
  // }

  // Serial.println();
  // Serial.println(io.statusText());

  // // configurção do callback, quando o feed receber (atualizar) um valor
  // //temperatura -> onMessage(handleTemperatura);
  // // Registra a função de callback
  // // ela será chamada sempre que o feed receber um novo dado

  // delay(3000);
}

void loop() {

  // Serial.print(F("Distancia Lida: "));
  // Serial.println(sonar.ping_cm());
  // delay(500);


//   // Manter a conexão com o Adafruit IO ativa
//   io.run();

//   // publicacao();  // chamada da função publish

//   delay(3000);
 }
