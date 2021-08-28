#include <Arduino.h>

void multiplexer_init()
{
  pinMode(muxPinA, OUTPUT);
  pinMode(muxPinB, OUTPUT);
  pinMode(muxPinC, OUTPUT);
}


void multiplexer_selector(byte n)
{
    digitalWrite(muxPinA, n   & 1);
    digitalWrite(muxPinB, n/2 & 1);
    digitalWrite(muxPinC, n/4 & 1);
}