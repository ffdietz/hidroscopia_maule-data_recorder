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
  if(i < imin) i = imin;
  if(i > imax) i = imax;
  float o = (( omax - omin ) * (( i - imin ) / ( imax-imin )) + omin );
  return o;
}

void display_init(){
    display.begin(); 
    display.setRot180();
    display.setFont(FONT);

    clearY();
}

void display_variable(byte xpos, byte ypos, int text_to_show){
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

void display_channel(uint16_t channel){
    display.drawStr(0,17, "CANAL");
    display_variable(32, 17, channel);
    // display_variable(45, 17, channel * 50);
}

void display_filename(char *file){
    display.drawStr(72, 17, file);
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

int _circularBuffer[DISPLAY_WIDTH]; //fast way to store values 
int _curWriteIndex = 0; // tracks where we are in the circular buffer

void drawLine(int xPos, int analogVal){
  int lineHeight = linear(analogVal, 0, 1023, 0, DISPLAY_HEIGHT * 0.4);
  int yPos = DISPLAY_HEIGHT / 2 + lineHeight;
//   display.drawVLine(xPos, yPos, lineHeight);
  display.drawPixel(xPos, yPos);
}

void display_graphic_circular_update(int input_value){
    _circularBuffer[_curWriteIndex++] = input_value;
    if(_curWriteIndex >= DISPLAY_WIDTH) _curWriteIndex = 0;
}

void display_graphic_circular(){
    int xPos = 0; 
    for(int i = _curWriteIndex; i < DISPLAY_WIDTH; i++){
        int input_value = _circularBuffer[i];
        drawLine(xPos, input_value);
        xPos++;
    }

    for(int i = 0; i < _curWriteIndex; i++){
        int analogVal = _circularBuffer[i];
        drawLine(xPos, analogVal);
        xPos++;;
    }
}

void display_test(){
    display.firstPage(); 
    do{
        display.drawStr( 0, 12, "TEST: 098");
    } while( display.nextPage() ); 
}


// https://github.com/makeabilitylab/arduino/blob/master/OLED/AnalogGraphScrolling/AnalogGraphScrolling.ino