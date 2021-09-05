#include <Wire.h>
#include <U8glib.h>

//#define FONT            u8g_font_unifont
#define FONT            u8g_font_6x10r
//#define FONT            u8g_font_7x13
#define FONT_HEIGHT     10

#define DISPLAY_WIDTH   128
#define DISPLAY_HEIGHT  64
#define LENGTH          DISPLAY_WIDTH

byte x = 0, i;
int y[LENGTH];

String message = "";

U8GLIB_SH1106_128X64 display(U8G_I2C_OPT_NO_ACK);


void clearY(){
  for(int i=0; i < LENGTH; i++) y[i] = -1;
}

float linear(float i, float imin, float imax, float omin, float omax){
  if (i < imin) i = imin;
  if (i > imax) i = imax;
  float o = (( omax - omin ) * (( i - imin ) / ( imax-imin )) + omin );
  return o;
}

void display_init(){
    display.begin(); 
    display.setRot180();
    display.setFont(FONT);

    clearY();
}

void display_variable(byte xpos, byte ypos, byte text_to_show){
    char buffer[255];
    sprintf (buffer, "%d", text_to_show);
    display.drawStr(xpos, ypos, buffer);
}

void display_header(){
    display.drawStr(0, 7, "HIDROSCOPIA MAULE");
    // display.drawStr(0, 17,  "CHANNEL ");
}

unsigned long previousMillis = 0;
boolean state = true;

void display_recording(){
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 500) {
        previousMillis = currentMillis;
        state = !state;
    }
    if (state)  display.drawDisc(124, 3, 3, U8G_DRAW_ALL);
}

void display_recording_pause(){
    // display.drawBox(121, 0, 7, 7);
    display.drawFrame(121, 0, 7, 7);
}

void display_graphic_update(int input_value){

    y[x] = linear(input_value, 0, 1024, DISPLAY_HEIGHT-30, 0);
    x++;
    if(x >= DISPLAY_WIDTH){
        x = 0;
        clearY();
    }
}

void display_graphic_draw(){
  display.drawPixel(0, y[0]);
  for(i = 1; i < LENGTH; i++){
    if(y[i] != -1)    display.drawPixel(i, y[i] + 25); 
    // if(y[i] != -1)    display.drawLine(i-1, y[i-1], i, y[i]);
    else  break;
  }
}

void display_test(){
    display.firstPage(); 
    do{
        display.drawStr( 0, 12, "TEST: 098");
    } while( display.nextPage() ); 
}

