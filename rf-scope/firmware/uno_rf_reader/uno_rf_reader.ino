#include <Arduino.h>
#include "tm1637_display.h"

const int PIN_CLK = 2;
const int PIN_DIO = 3;
const int PIN_AIN = A0;

TM1637Display7Seg display(PIN_CLK, PIN_DIO);

void setup() {
  Serial.begin(115200);
  display.begin();
  display.setBrightness(7);
}

void loop() {
  int raw = analogRead(PIN_AIN);

  // Example correction: clamp and offset
  int cor = raw - 289;
  if (cor < 0) cor = 0;

  float volts = (cor / 1023.0) * 5.0;

  // Display volts * 100 (e.g. 3.58V -> "358")
  int disp = (int)(volts * 100.0f);
  display.showNumber(disp);

  // JSON line for USB/WebSocket bridge
  Serial.print("{\"raw\":");
  Serial.print(raw);
  Serial.print(",\"cor\":");
  Serial.print(cor);
  Serial.print(",\"v\":");
  Serial.print(volts, 3);
  Serial.println("}");

  delay(50);
}
