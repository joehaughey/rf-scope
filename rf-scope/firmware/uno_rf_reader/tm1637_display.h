#pragma once
#include <Arduino.h>
#include <TM1637Display.h>

class TM1637Display7Seg {
public:
  TM1637Display7Seg(uint8_t pinClk, uint8_t pinDio)
    : display(pinClk, pinDio) {}

  void begin() {
    display.setBrightness(7);
    display.clear();
  }

  void setBrightness(uint8_t b) {
    display.setBrightness(b);
  }

  void showNumber(int value) {
    // 4-digit, leading zeros off
    display.showNumberDec(value, false);
  }

private:
  TM1637Display display;
};
