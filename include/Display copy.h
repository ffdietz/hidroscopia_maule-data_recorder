#include <Wire.h>
#include <U8glib.h>

#define ROTATION_0      U8G2_R0
#define ROTATION_180    U8G2_R2
#define FONT            u8g_font_unifont
#define FONT_HEIGHT     10

U8GLIB_SH1106_128X64 display(U8G_I2C_OPT_NO_ACK);

void display_init()
{
    display.begin(); 
    display.setRot180();
    display.setFont(FONT);
}


void display_draw(byte to_show)
{
    
}


void display_test(){
 display.firstPage(); 
    do 
    {
        display.drawStr( 0, 12, "TEST: 098");

    } while( display.nextPage() ); 
}