
#include <SPI.h>                                      //SPI library
#include <Wire.h>                                     //I2C library for OLED
#include <U8g2lib.h>

#define SCREEN_WIDTH    128                            // OLED display width, in pixels
#define SCREEN_HEIGHT   64                             // OLED display height, in pixels
#define OLED_RESET      -1                             // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS  0x3C                           // See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void display_init(){   
  display.begin();
}

void display_static()
{
    
    // display.setCursor(0,0);                             //set cursor to top of screen
    // display.print("SPECTRUM ANALIZER");

    // display.display();                                  //show the buffer

    // display.setCursor(0,8);                            //set cursor to top of screen
    // display.print("INPUT READ:");

    // display.setCursor(0,16);  
    // display.print("MUX SELECT:");

    // display.setCursor(116,16); 
    // display.print("Hz");
    
    // display.display();                                  //show the buffer
}

void display_show(int to_display){
    // display.clearDisplay();                             //clear display

    // for(i = 0 ; i < sizeof(to_display) ; i++){
    //     display.setCursor(to_display[0][i],to_display[1][i]);
    //     display.print(to_display[i]);
    // }
    // // for (i = 1; i < 64; i++) 
    // // {                                                                 // In the current design, 60Hz and noise
    // //     int dat = sqrt(data[i] * data[i] + im[i] * im[i]);            //filter out noise and hum
    // //     display.drawLine(
    // //         i*4 + x, ylim, 
    // //         i*4 + x, ylim - dat, 
    // //         WHITE);  // draw bar graphics for freqs above 500Hz to buffer
    // // }

    // // display.setCursor(0,0);                             //set cursor to top of screen
    // // display.print();                 //print title to buffer
    
    // // display.setCursor(0,8);                            //set cursor to top of screen
    // // display.print("INPUT READ:");   
    // // display.print(analogRead(A0));   
    
    // // display.setCursor(0,16);  
    // // display.print("MUX SELECT:");
    // // display.print(position + 1);
    // // // display.print(currentValue);

    // // display.setCursor(98,16); 
    // // display.print((50 * (position + 1)));
    // // display.setCursor(116,16); 
    // // display.print("Hz");
    
    // display.display();                                  //show the buffer
}

void display_test_u8g2(){
    display.firstPage();
    do {
        display.setFont(u8g2_font_roentgen_nbp_t_all);  // Set the font
        display.drawStr(20,35,"test");   // Write 'Hello World!'
        // display.drawRFrame(0,0,127,63,7);       // Draw a rectangle around it
    } while ( display.nextPage() );
}