#include <Arduino.h>

#define encoderPinA 2
#define encoderPinB 3
#define muxPinA A1
#define muxPinB A2
#define muxPinC A3
#define SD_CSPin 10
#define analogPin A0
#define recButton 4

#include "Display.h"
#include "Encoder.h"
#include "FFT.h"
#include "Multiplexer.h"
#include "microSD.h"

#define FASTADC 0
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

uint16_t  analog_input ;
uint8_t   channel_select;
boolean   rec_state = false;

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
    display_graphic_draw();
    display_variable(0,   20, channel_select);    
    // display_variable(0,   20, message);

    if(rec_state == true)   display_recording();
    if(rec_state == false)  display_recording_pause();

  } while( display.nextPage() ); 
}

void loop(void) {

  channel_select = encoder_position();
  analog_input = analogRead(analogPin);
  if(recording_button.debounce())  rec_state = !rec_state;

  multiplexer_selector(channel_select);
  display_graphic_update(analog_input);

  if(rec_state == true)   sd_write(analog_input);
  if(rec_state == false)  sd_stop();

  display_buffer();
  //display_test();

}
