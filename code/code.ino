#include <Bounce.h>

const int buttonPin = 8;
const int ledPin = 13;
Bounce pushbutton = Bounce(buttonPin, 5);  // 10 ms debounce

void setup() {
  Keyboard.begin();
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, HIGH); // Light up on board LED to show connected status
}

byte previousState = LOW;         // what state was the button last time
unsigned int count = 0;            // how many times has it changed to low
unsigned long countAt = 0;         // when count changed
unsigned int countPrinted = 0;     // last count printed

void loop() {
  if (pushbutton.update()) {
    if (pushbutton.fallingEdge()) {
      previousState=HIGH;
      count = count + 1;
      countAt = millis();
    } if (pushbutton.risingEdge()) {
      previousState=LOW;
    }
  } else {
    if (count != countPrinted) {
      unsigned long nowMillis = millis();
      if (nowMillis - countAt > 100) {
        countPrinted = count;
      }
    }
  }

  if (previousState==HIGH){
    Keyboard.press(32);
  } else{
    Keyboard.release(32);
  }
}
