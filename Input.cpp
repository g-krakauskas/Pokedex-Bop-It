#include "Input.h"

int Input::readInput() {

  if (digitalRead(1)) return 1; //map to DIAL pin
  if (digitalRead(2)) return 2; //map to JOYSTICK pin
  if (digitalRead(3)) return 3; //map to ACCELEROMETER/SHAKE pin

  return 0;

}

bool Input::waitForCompletion(int userInput, int timer) {

  unsigned long startTime = millis();

  while (millis() - startTime < timer * 1000) {
    if (readInput() == userInput) {
      return true;
    }
  }

  return false;

}

bool Input::gameOn() {

  if (digitalRead(4) == HIGH) { //map pin to on/off switch
    return true;
  }

  return false;

}

bool Input::gameStart() {

  if (digitalRead(5) == HIGH) { //map pin to game start/reset button
    return true;
  }

  return false;

}