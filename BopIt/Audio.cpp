#include "Audio.h"
#include <Arduino.h>

void Audio::catchAudio() {

  Serial.println("[AUDIO] CATCH IT (DIAL)");

}

void Audio::attackAudio() {

  Serial.println("[AUDIO] ATTACK IT (JOYSTICK)");

}

void Audio::evolveAudio() {

  Serial.println("[AUDIO] EVOLVE IT (SHAKE)");

}

void Audio::catchSuccess() {

  Serial.println("[AUDIO] CAUGHT IT");
  delay(600); // placeholders for audio duration

}

void Audio::attackSuccess() {

  Serial.println("[AUDIO] ATTACKED IT");
  delay(600); // placeholders for audio duration

}

void Audio::evolveSuccess() {

  Serial.println("[AUDIO] EVOLVED IT");
  delay(600); // placeholders for audio duration

}

void Audio::fail() {

  Serial.println("[AUDIO] YOU FAILED");
  delay(600); // placeholders for audio duration

}