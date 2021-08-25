#include "FIX_FFT.h"                                  //library to perfom the Fast Fourier Transform

char  im[128], data[128];                              //variables for the FFT
char  x = 0, ylim = 60;                                //variables for drawing the graphics
int   i = 0, val;                                       //counters

int min = 600, max = 0;                                //set minumum & maximum ADC values

void fft_update()
{
    for (i = 0; i < 128; i++) {                         //take 128 samples
        val = analogRead(A0);                             //get audio from Analog 0
        data[i] = val / 4 - 128;                          //each element of array is val/4-128
        im[i] = 0;                                        //
        if(val > max) max = val;                              //capture maximum level
        if(val < min) min = val;                              //capture minimum level
    };

    fix_fft(data, im, 7, 0);                            //perform the FFT on data

}

