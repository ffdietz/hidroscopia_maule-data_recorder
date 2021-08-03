
#include <SPI.h>                                      //SPI library
#include <Wire.h>                                     //I2C library for OLED
#include <Adafruit_GFX.h>                             //graphics library for OLED
#include <Adafruit_SSD1306.h>                         //OLED driver

#define SCREEN_WIDTH    128                            // OLED display width, in pixels
#define SCREEN_HEIGHT   64                             // OLED display height, in pixels
#define OLED_RESET      -1                             // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS  0x3C                           // See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void display_init(){
    display.begin(SSD1306_SWITCHCAPVCC,SCREEN_ADDRESS);           //begin OLED @ hex addy 0x3C
    display.setTextSize(1);                             //set OLED text size to 1 (1-6)
    display.setTextColor(WHITE);                        //set text color to white
    display.clearDisplay();                             //clear display
    // analogReference(DEFAULT);                           // Use default (5v) aref voltage.
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