#include <Arduino.h>
#include "DebouncedEncoder.h"

byte lastPosition;
byte encoderPinA = 2;
byte encoderPinB = 3;
byte encoderMin = 0;
byte encoderMax = 5;

DebouncedEncoder Encoder(encoderPinA, encoderPinB, encoderMax, encoderMin, true);

void ISREnc() {
	Encoder.encoderCheck();
}

void encoder_init(){
    attachInterrupt(digitalPinToInterrupt(encoderPinA), ISREnc, CHANGE);
	attachInterrupt(digitalPinToInterrupt(encoderPinB), ISREnc, CHANGE);
}

byte encoder_check(){
	byte position = Encoder.getPosition();
	if (lastPosition != position) lastPosition = position;

    return position;
}