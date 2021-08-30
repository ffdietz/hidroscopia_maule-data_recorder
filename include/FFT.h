#include "fix_fft.h"                                  //library to perfom the Fast Fourier Transform

// void fft_update(uint16_t analogInput)
//  {
//     for (i = 0; i < 64; i++) {      //take 64 samples
//         val = analogInput;          //get audio from Analog 0
//         data[i] = val / 4 - 128;    //each element of array is val/4-128
//         im[i] = 0;                                        //
//         if(val > max) max = val;    //capture maximum level
//         if(val < min) min = val;    //capture minimum level
//     };

//     fix_fft(data, im, 7, 0);                            //perform the FFT on data

// }

// //    for (int i = 0; i < 64; i++) 
// //     {                                                                 // In the current design, 60Hz and noise
// //         int dat = sqrt(data[i] * data[i] + im[i] * im[i]);            //filter out noise and hum
// //         u8g2.drawLine(
// //             i*4 + x, ylim, 
// //             i*4 + x, ylim - dat 
// //             );  // draw bar graphics for freqs above 500Hz to buffer
// //     }

// for (i = 1; i < 64; i++) 
// {                                                                 // In the current design, 60Hz and noise
//     int dat = sqrt(data[i] * data[i] + im[i] * im[i]);            //filter out noise and hum
//     display.drawLine(
//         i*4 + x, ylim, 
//         i*4 + x, ylim - dat, 
//         WHITE);  // draw bar graphics for freqs above 500Hz to buffer
// }        