#include <Arduino.h>

#include "Display.h"
#include "Encoder.h"
#include "FFT.h"
#include "Multiplexer.h"
#include "SDModule.h"


void setup() {
  display_init();
  encoder_init();
  multiplexer_init();
  // SD_init();
}

void loop() 
{
//ENCODER
  byte position = encoder_check();
  multiplexer_selector(position);
//FFT
  fft_update();
  // SD_update();
//DISPLAY
  display_show();
}