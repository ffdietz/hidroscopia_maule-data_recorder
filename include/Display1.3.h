
#include <SPI.h>                                      //SPI library
#include <Wire.h>                                     //I2C library for OLED
#include <U8g2lib.h>

#define DIRECTION U8G2_R0   // No rotation
// #define DIRECTION U8G2_R2   // 180 degrees
#define FONT u8g2_font_6x12_mf

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(DIRECTION, /* reset=*/ U8X8_PIN_NONE);

void display_init(){   
    u8g2.begin(); 
    u8g2.setFont(FONT);	// set the font for the terminal window     
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

void display_show(){

    // display.clearDisplay();                             //clear display

    // for(i = 0 ; i < sizeof(to_display) ; i++){
    //     display.setCursor(to_display[0][i],to_display[1][i]);
    //     display.print(to_display[i]);
    // }
    // for (i = 1; i < 64; i++) 
    // {                                                                 // In the current design, 60Hz and noise
    //     int dat = sqrt(data[i] * data[i] + im[i] * im[i]);            //filter out noise and hum
    //     display.drawLine(
    //         i*4 + x, ylim, 
    //         i*4 + x, ylim - dat, 
    //         WHITE);  // draw bar graphics for freqs above 500Hz to buffer
    // }

    u8g2.firstPage();
    do {
        u8g2.drawStr(0, 10, "SPECTRUM ANALIZER");
        u8g2.drawStr(0, 20, "INPUT READ: ");
        u8g2.drawStr(0, 30, "CHANNEL: ");
    } while ( u8g2.nextPage() );

    // display.print(analogRead(A0));

    // display.print(position + 1);

    // display.setCursor(98,16); 
    // display.print((50 * (position + 1)));
    // display.setCursor(116,16); 
    // display.print("Hz");

}


void display_test_u8g2(){
    u8g2.firstPage();
    do {
        u8g2.drawStr(0, 15, "TEST:123");
    } while ( u8g2.nextPage() );
}