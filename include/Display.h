#include <Wire.h>
#include <U8g2lib.h>

#define ROTATION_0      U8G2_R0
#define ROTATION_180    U8G2_R2
#define FONT            u8g2_font_6x10_mr
#define FONT_HEIGHT     10

U8G2_SH1106_128X64_NONAME_1_HW_I2C display(ROTATION_180, /* reset=*/ U8X8_PIN_NONE);

void display_init()
{
    display.begin(); 
    display.setFont(FONT);
}


void display_show(byte to_show)
{
    display.setCursor(0, 10);  
        display.print("HIDROSCOPIA MAULE");
    display.setCursor(0, 24);  
        display.print("CHANNEL: ");    display.print(to_show + 1);
    display.setCursor(0, 34);  
        display.print("FREQUENCY: ");  display.print((to_show + 1) * 50); display.print("Hz");
}


void display_test(){
 display.firstPage(); 
    do {
        display.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
        display.drawStr(0,10,"Hello World!");	// write something to the internal memory
        display.drawLine(
              0, 0, 
              10, 10 ); // skip displaying the 0-500hz band completely.
        display.sendBuffer();					// transfer internal memory to the display
    } while( display.nextPage() ); 
}