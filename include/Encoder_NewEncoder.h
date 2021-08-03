#include <Arduino.h>
#include "NewEncoder.h"

void ESP_ISR callBack(NewEncoder *encPtr, const volatile NewEncoder::EncoderState *state, void *uPtr);

NewEncoder encoder(2, 3, 0, 6, 0, FULL_PULSE);

int16_t prevEncoderValue;
volatile NewEncoder::EncoderState newState;
volatile bool newValue = false;

void encoder_init()
{
  NewEncoder::EncoderState state;

  Serial.begin(115200);
  Serial.println("Starting");

    encoder.getState(state);
    Serial.print("Encoder Successfully Started at value = ");
    prevEncoderValue = state.currentValue;
    Serial.println(prevEncoderValue);

  encoder.attachCallback(callBack);

}

int16_t encoder_check()
{
  int16_t currentValue;
  NewEncoder::EncoderClick currentClick;

  if (newValue) {
    noInterrupts();
    currentValue = newState.currentValue;
    currentClick = newState.currentClick;
    newValue = false;
    interrupts();
    Serial.print("Encoder: ");
    if (currentValue != prevEncoderValue) {
      Serial.println(currentValue);
      prevEncoderValue = currentValue;
	return currentValue;
    }

  }
//    display.setCursor(0,0);
//    display.print(currentValue);
//    display.display();
}

void ESP_ISR callBack(NewEncoder *encPtr, const volatile NewEncoder::EncoderState *state, void *uPtr) {
  (void) encPtr;
  (void) uPtr;
  memcpy((void *)&newState, (void *)state, sizeof(NewEncoder::EncoderState));
  newValue = true;
}