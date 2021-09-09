#include <Arduino.h>
#include "Display.h"
#include "Encoder.h"
#include "FFT.h"
#include "Multiplexer.h"
#include "microSD.h"

#define analogPin A0

#define FASTADC 1
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

uint16_t  analog_input ;
uint8_t   channel_select;
boolean   rec_state = true;

void setup(void) {
  display_init();
  encoder_init();
  multiplexer_init();
  sd_init();

  #if FASTADC
    sbi(ADCSRA,ADPS2) ;   // set prescale to 16
    cbi(ADCSRA,ADPS1) ;
    cbi(ADCSRA,ADPS0) ;
  #endif
}

void display_buffer(){
  display.firstPage(); 
  do{
    display_header();
    display_filename(filename);
    display_channel((channel_select + 1) * 50);

    // display_graphic_draw();
    display_graphic_circular();
    // display_variable(0,   20, message);

    if(rec_state) display_recording();
    else          display_recording_pause();

  } while( display.nextPage() ); 
}

void loop(void) {

  channel_select  = encoder_position();
  analog_input    = analogRead(analogPin);
  
  pushButton.poll();
  if(pushButton.pushed()) rec_state = !rec_state;

  if(rec_state) sd_write(analog_input);
  else          sd_stop();

  multiplexer_selector(channel_select);

  display_graphic_circular_update(analog_input);
  // sd_test();
  display_buffer();
  // display_graphic_update(analog_input);
}
