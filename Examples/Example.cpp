// Designed for a Teensy 3.2
// Reads data from the Virtual Boy Controller and outputs it as keystrokes to a computer using the Keyboard library

#include <Arduino.h>
#include "VirtualBoyController.h"

#define LATCH_PIN 0
#define CLOCK_PIN 1
#define DATA_PIN 2

#define checkButton(button, key) if (vboy.down(button)) { Keyboard.press(key); } else if (vboy.up(button)) { Keyboard.release(key); }

VirtualBoyController vboy;

void setup() {
  vboy.init(LATCH_PIN, CLOCK_PIN, DATA_PIN);
}

void loop() {
  vboy.update();

  checkButton(VBOY_LUP, KEY_W);
  checkButton(VBOY_LLEFT, KEY_A);
  checkButton(VBOY_LDOWN, KEY_S);
  checkButton(VBOY_LRIGHT, KEY_D);

  checkButton(VBOY_RUP, KEY_I);
  checkButton(VBOY_RLEFT, KEY_J);
  checkButton(VBOY_RDOWN, KEY_K);
  checkButton(VBOY_RRIGHT, KEY_L);

  checkButton(VBOY_A, KEY_M);
  checkButton(VBOY_B, KEY_N);
  checkButton(VBOY_START, KEY_ENTER);
  checkButton(VBOY_SELECT, KEY_RIGHT_SHIFT);
  checkButton(VBOY_L, KEY_Q);
  checkButton(VBOY_R, KEY_O) ; 
}

function checkButton(uint8_t button, uint16_t key)
{
  
  if (vboy.down(button))
  {
    Keyboard.press(key);
  }

  else if (vboy.up(button))
  {
    Keyboard.release(key);
  }
}