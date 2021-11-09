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
uint8_t   channel_select = 0;
boolean   rec_state = true;

void setup(void) {
  display_init();
  encoder_init();
  multiplexer_init();
  // sd_init();

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
    // display_filename(filename);

    // display_channel((channel_select + 1) * 50);
    display_channel(channel_select + 1);

    // display_graphic_draw();
    display_graphic_circular();
    // display_variable(0,   20, message);

    if(rec_state) display_recording();
    else          display_recording_pause();

  } while( display.nextPage() ); 
}



unsigned long prev_millis = 0;
unsigned long interval_on = 10;

void loop(void) {

  unsigned long current_millis = millis();
  // channel_select  = encoder_position();
  // channel_select  = map(analog_input,0, 1023, 0, 7);

  analog_input    = analogRead(analogPin);  
  interval_on = analog_input;

  if(current_millis - prev_millis >= interval_on) {
    // interval_on = analog_input;
    // channel_select  = byte(random(7));
    channel_select++;
    if(channel_select > 6) channel_select = 0;

    prev_millis = current_millis;
  }

    // interval_on = analog_input;


  // pushButton.poll();
  // if(pushButton.pushed()) rec_state = !rec_state;

  // if(rec_state) sd_write(analog_input);
  // else          sd_stop();


  multiplexer_selector(channel_select);

  display_graphic_circular_update(analog_input);
  display_buffer();

  // sd_test();
  // display_graphic_update(analog_input);
}
