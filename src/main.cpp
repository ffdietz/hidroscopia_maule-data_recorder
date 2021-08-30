#include <Arduino.h>

#define encoderPinA 2
#define encoderPinB 3

#define muxPinA A1
#define muxPinB A2
#define muxPinC A3

#define SD_CSPin 10

#define analogPin A0

#include "Display copy.h"
#include "Encoder.h"
#include "FFT.h"
#include "Multiplexer.h"
#include "microSD.h"

#define FASTADC 1
// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


char im[128], data[128];
byte x = 0, ylim = 62;
byte i = 0, val;
byte dat, var;
int min=0, max=0;

uint16_t  inputRead ;
uint8_t   menu_select;


void display_buffer(){
  if(menu_select == 0){
    display.drawStr(0, 10, "spectrum analyzer");

    for ( i = 0 ; i < 32; i++){
        dat = sqrt(data[i] * data[i] + im[i] * im[i]);
        var = ylim - dat;
        if (var < 0) var = 0;
        // display.drawHLine( i + x, var - 5, 2);
        // display.drawLine(i + x, ylim, i + x, var );
        display.drawVLine(i * 4, var, ylim );
        // display.drawPixel(i, var );
        // display.drawBox( i + x, var , 3,  ylim );
      }
  }

  if(menu_select == 1){
     display.drawStr(0, 20, "sd recording");
     display.drawEllipse(0, 20, 10, 10);
     
  }

  if(menu_select == 2){
     display.drawStr(0, 20, "sd recording");
     display.drawStr(0, 30, "stopped");
  }
}


void setup(void) {
  display_init();         //
  encoder_init();         //
  SD_init();

  // multiplexer_init();     //

  #if FASTADC
  // set prescale to 16
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;
  #endif

}

void loop(void) {
//INPUT UPDATE
  menu_select   =   encoder_position();
  inputRead     =   analogRead(analogPin);

  if(menu_select == 0){      //graphic()
      //get analog reading
    for ( i = 0; i < 32; i++){
        // data[i] = x;
        data[i] = inputRead >> 2;
      }
    fix_fft(data, im, 7, 0);
  }

  if (menu_select == 1){
    SD_write(inputRead);
  }

  if (menu_select == 2){
    SD_stop();
  }
  
  //  display_test();

  display.firstPage(); 
    do{
      display_buffer();
    } while( display.nextPage() ); 

      
}


  //multiplexer_selector(0);
  //multiplexer_selector(position);

  // char buffer[3];
  // sprintf (buffer, "%d", position);
  // display.drawStr(100, 10, buffer);


/*
encoder >> scan mode // record mode

 scan_mode
  shows fft graphic

record mode
  shows fft graphic
  record icon

 */