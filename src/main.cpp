#include <Arduino.h>

#define encoderPinA 2
#define encoderPinB 3

#define muxPinA A1
#define muxPinB A2
#define muxPinC A3

#define SDCSPin 10

#define analogPin A0

#include "Display.h"
#include "Encoder.h"
#include "FFT.h"
#include "Multiplexer.h"
#include "SDModule.h"

void setup() {
  display_init();         //
  encoder_init();         //
  multiplexer_init();     //
  //FFT_init();
  SD_init();
}

void loop() 
{
//ENCODER
  byte position = encoder_check();
  multiplexer_selector(position);
//FFT
  //fft_update();
  //SD_update();
//DISPLAY
  display_show(position);
}