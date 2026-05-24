//M Nharen EE25B089

#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1
#define CS_PIN 5
#define VERTICAL_PIN 32
#define HORIZONTAL_PIN 33

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
int state = 4;
int vertical_state = 0;
int horizontal_state = 0;
int frame_number = 0;
int prev_state = 4;

const byte arrows[5][8] = {
  {0b00000000, 0b00011000, 0b00111100, 0b00011000, 0b00011000, 0b00011000, 0b00011000, 0b00000000}, // Frame 0: Up
  {0b00000000, 0b00000000, 0b00001000, 0b01111100, 0b01111100, 0b00001000, 0b00000000, 0b00000000}, // Frame 1: Right
  {0b00000000, 0b00011000, 0b00011000, 0b00011000, 0b00111100, 0b00011000, 0b00000000, 0b00000000}, // Frame 2: Down
  {0b00000000, 0b00000000, 0b00010000, 0b00111110, 0b00111110, 0b00010000, 0b00000000, 0b00000000}, // Frame 3: Left
  {0b00000000, 0b00000000, 0b00011000, 0b00100100, 0b00100100, 0b00011000, 0b00000000, 0b00000000}  // Frame 4: Neutral
};


void setup() {
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 3);
  mx.clear();

  pinMode(32,INPUT_PULLUP);
  pinMode(33,INPUT_PULLUP);

  Serial.begin(9600);

  for (int i = 0; i < 8; i++) {
    mx.setRow(0, i, arrows[4][i]);
  }
}

void loop() {

  vertical_state = analogRead(VERTICAL_PIN);
  horizontal_state = analogRead(HORIZONTAL_PIN);

 if (vertical_state < 1000) {
    state = 0;
  } 
  else if (vertical_state > 3500) {
    state = 2;
  } 
  else if (horizontal_state < 1000) {
    state = 1; 
  } 
  else if (horizontal_state > 3500) {
    state = 3;
  } 
  else {
    state = 4;
  }

  if (state == prev_state)
  {
    frame_number += 1;
    frame_number = frame_number%8;
  }
  else
  {
    frame_number = 0;
  }

  if (state == 4)
  {
    mx.clear();
    for (int i = 0; i < 8; i++) {
      mx.setRow(0, i, arrows[4][i]);
    }
  }
  else
  {
    display(state, frame_number);
  }

  Serial.print(vertical_state);
  Serial.print(" ");
  Serial.println(horizontal_state);

  delay(100);

  prev_state = state;
  
}

void display(int state, int frame_number)
{
  for (int i = 0; i < 8; i++) {
    byte row = arrows[state][i];
    
    if (state == 2 || state == 3) {
      row = arrows[3][i];
      row = (row << frame_number) | (row >> (8 - frame_number));
    } 

    else if (state != 4) {
      row = arrows[1][i];
      row = (row >> frame_number) | (row << (8 - frame_number));
    }

    if (state == 0 || state == 2) {
      mx.setColumn(0, i, row);
    } else {
      mx.setRow(0, i, row); 
    }
  }
}