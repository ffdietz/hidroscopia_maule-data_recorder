#include <Arduino.h>
#include "DebouncedEncoder.h"

byte lastPosition = 0;
byte encoderMin = 0;
byte encoderMax = 2;

DebouncedEncoder Encoder(encoderPinA, encoderPinB, encoderMax, encoderMin, true);

void ISREnc() {
	Encoder.encoderCheck();
}

void encoder_init(){
    attachInterrupt(digitalPinToInterrupt(encoderPinA), ISREnc, CHANGE);
	attachInterrupt(digitalPinToInterrupt(encoderPinB), ISREnc, CHANGE);
}

byte encoder_position(){
	byte position = Encoder.getPosition();
	 if (lastPosition != position){
		lastPosition = position;
    	return position;
	 }
	 else return lastPosition;
}

byte encoder_direction(){
	byte direction = Encoder.getDirection();	
	return direction;
}