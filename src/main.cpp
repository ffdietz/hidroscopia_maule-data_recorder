#include <Arduino.h>
#include "fix_fft.h"                                  //library to perfom the Fast Fourier Transform
#include <SPI.h>                                      //SPI library
#include <Wire.h>                                     //I2C library for OLED
#include <Adafruit_GFX.h>                             //graphics library for OLED
#include <Adafruit_SSD1306.h>                         //OLED driver

#define SCREEN_WIDTH    128                            // OLED display width, in pixels
#define SCREEN_HEIGHT   64                             // OLED display height, in pixels
#define OLED_RESET      -1                             // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS  0x3C                           // See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

char im[128], data[128];                              //variables for the FFT
char x = 0, ylim = 60;                                //variables for drawing the graphics
int i = 0, val;                                       //counters

void setup(){
  //Serial.begin(9600);                                 //serial comms for debuging
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);           //begin OLED @ hex addy 0x3C
  display.setTextSize(1);                             //set OLED text size to 1 (1-6)
  display.setTextColor(WHITE);                        //set text color to white
  display.clearDisplay();                             //clear display
  analogReference(DEFAULT);                           // Use default (5v) aref voltage.
}

void loop(){
  int min = 800, max = 0;                                //set minumum & maximum ADC values
  for (i = 0; i < 128; i++) {                         //take 128 samples
    val = analogRead(A0);                             //get audio from Analog 0
    data[i] = val / 4 - 128;                          //each element of array is val/4-128
    im[i] = 0;                                        //
    if(val > max) max = val;                              //capture maximum level
    if(val < min) min = val;                              //capture minimum level
  };
    
  fix_fft(data, im, 7, 0);                            //perform the FFT on data
  
  display.clearDisplay();                             //clear display
  for (i = 1; i < 64; i++) {                          // In the current design, 60Hz and noise
    int dat = sqrt(data[i] * data[i] + im[i] * im[i]);            //filter out noise and hum
    display.drawLine(
      i*2 + x, ylim, 
      i*2 + x, ylim - dat, 
      WHITE);  // draw bar graphics for freqs above 500Hz to buffer
  }

  display.setCursor(0,0);                             //set cursor to top of screen
  display.print("SPECTRUM ANALIZER");                 //print title to buffer
  display.setCursor(0,8);                            //set cursor to top of screen
  display.print(analogRead(A0));   
  display.display();                                  //show the buffer
}

/*
 * Arduino Spectrum Analizer
 * 
 * learnelectronics
 * 27 April 2017
 * black magic stolen from CBM80Amiga
 * 
 * www.youtube.com/c/learnelectronics
 * arduino1069@gmail.com
 * 
 * Fix_FFT library available @ https://github.com/kosme/arduinoFFT
 */