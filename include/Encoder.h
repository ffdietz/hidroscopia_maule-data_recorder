#include <Arduino.h>
#include "DebouncedEncoder.h"

byte lastPosition = 0;
byte encoderPinA = 2;
byte encoderPinB = 3;
byte encoderMin = 0;
byte encoderMax = 6;

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
	 if (lastPosition != position){
		lastPosition = position;
    	return position;
	 }
	 else return lastPosition;
}