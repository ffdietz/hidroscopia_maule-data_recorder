#include <Arduino.h>
#include "Libraries.h"
#include "Encoder.h"
#include "Display.h"
#include "Multiplexer.h"
#include "FFT.h"

void setup(){
  display_init();
  encoder_init();
  multiplexer_init();
}

void loop()
{
  //ENCODER
  byte position = encoder_check();
  multiplexer_selector(position);

//FFT
  fft_update();

//_DISPLAY_////////////////////////////

//__________CREAR STRUCTUR___________
// int display_data[2][1] = {
//   {{0,0}, {"SPECTRUM ANALIZER"}},
// }
  display_show(display_data);
}
