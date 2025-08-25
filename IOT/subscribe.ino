void handleTemperatura(AdafruitIO_Data *data) {
  float temp = data->toFloat();

  Serial.print(F("Temperatura do feed: "));
  Serial.println(temp, 2);
  Serial.println("°C");

  // Lógica para acender ou não o LED
  if (temp < 0) {
    digitalWrite(pinLed, HIGH);
  } else {
    digitalWrite(pinLed, LOW);
  }
}
