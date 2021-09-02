#include <Arduino.h>

#define encoderPinA 2
#define encoderPinB 3

#define muxPinA A1
#define muxPinB A2
#define muxPinC A3

#define SD_CSPin 10

#define analogPin A0

#include "Display.h"
#include "Encoder.h"
#include "FFT.h"
#include "Multiplexer.h"
#include "microSD.h"

#define FASTADC 0
// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


uint16_t  input_read ;
uint8_t   menu_select;

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
    
    if(menu_select == 0){
      display_recording_pause();
    }

    if(menu_select == 1){
      display_recording();
    }

  } while( display.nextPage() ); 
}

void loop(void) {

  menu_select = encoder_position();
  input_read  = analogRead(analogPin);

  multiplexer_selector(menu_select);
  display_graphic_update(input_read);

  if(menu_select == 0) sd_stop();
  if(menu_select == 1) sd_write(input_read);

  display_buffer();

}
