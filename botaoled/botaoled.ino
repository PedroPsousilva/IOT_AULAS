#include "WiFi.h"
#include "AdafruitIO_WiFi.h"


#define IO_USERNAME  ""
#define IO_KEY       ""

// Configurações de rede Wi-Fi
#define WIFI_SSID    ""
#define WIFI_PASS    ""



AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);


AdafruitIO_Feed *botaoLED = io.feed("botaoled");


#define LED_PIN 14  

void setup() {
    Serial.begin(115200);

  
  pinMode(LED_PIN, OUTPUT);

 
  Serial.print("Conectando ao Adafruit IO");
  io.connect();

  
  botaoLED->onMessage(handleBotaoLed);

  
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println();
  Serial.println("Conectado ao Adafruit IO!");
}

void loop() {
 
  io.run();
}

// Função chamada sempre que houver alteração no feed
void handleBotaoLed(AdafruitIO_Data *data) {
  String valor = data->toString();
  Serial.print("Recebido do feed: ");
  Serial.println(valor);

  if (valor == "true" || valor == "1") {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED LIGADO");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED DESLIGADO");
  }
}
