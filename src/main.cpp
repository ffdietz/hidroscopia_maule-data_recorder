#include <Arduino.h>
#include "Libraries.h"
#include "Encoder.h"
#include "Display.h"
#include "Multiplexer.h"
#include "FFT.h"

void setup(){
  display_init();
  display_static();
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

  display.clearDisplay();                             //clear display

    // for (i = 1; i < 64; i++) 
    // {                                                                 // In the current design, 60Hz and noise
    //     int dat = sqrt(data[i] * data[i] + im[i] * im[i]);            //filter out noise and hum
    //     display.drawLine(
    //         i*4 + x, ylim, 
    //         i*4 + x, ylim - dat, 
    //         WHITE);  // draw bar graphics for freqs above 500Hz to buffer
    // }


    // display.print();                 //print title to buffer
    
        
    display.setCursor(0,0);                             //set cursor to top of screen
    display.print("SPECTRUM ANALIZER");

    display.setCursor(0,8);                            //set cursor to top of screen
    display.print("INPUT READ:");

    display.setCursor(0,16);  
    display.print("MUX SELECT:");
    display.print(position );

    display.setCursor(116,16); 
    display.print("Hz");
    

    display.setCursor(88,8);                            //set cursor to top of screen
    display.print(analogRead(A0)); 
    
    display.setCursor(0,16);  
    // display.print(currentValue);

    display.setCursor(98,16); 
    display.print((50 * (position + 1)));

    
    display.display();                                  //show the buffer
}
//CREAR STRUCTUR PARA DISPLAY
// int display_data[2][1] = {
//   {{0,0}, {"SPECTRUM ANALIZER"}},
// }
// display_show(display_data);


//DISPLAY LIBRARY u8g2
//https://github.com/olikraus/u8g2

//MICROSD MODULE
