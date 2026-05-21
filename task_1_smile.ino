//M Nharen EE25B089

#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1
#define CS_PIN 5

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

const byte smileFace[8] = {
  0b00111100,
  0b01000010,
  0b10100101,
  0b10000001,
  0b10100101,
  0b10011001,
  0b01000010,
  0b00111100
};

void setup() {
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 3);
  mx.clear();

  for (int i = 0; i < 8; i++) {
    mx.setRow(0, i, smileFace[i]);
  }
}

void loop() {
}
