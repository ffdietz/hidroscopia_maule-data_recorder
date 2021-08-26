#include <Arduino.h>


byte muxSelectorPin[] = {A1, A2, A3};


void multiplexer_init()
{
  for(byte i = 0; i < 3; i++) pinMode(muxSelectorPin[i], OUTPUT);
}


void multiplexer_selector(byte n)
{
  for (byte i = 0; i < 3; i++) {
    digitalWrite(muxSelectorPin[i], n & 1);
    n /= 2;
  }
}