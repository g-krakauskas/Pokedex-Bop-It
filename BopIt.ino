#include "Input.h"
#include "Audio.h"
#include "Catch.h"
#include "Attack.h"
#include "Evolve.h"
#include "Game.h"
#include "Display.h"

Input i;
Audio a;
gameDisplay g;
spriteDisplay s;

#define DIAL_PIN 1
#define JOYSTICK_PIN 2

#define onPin 4
#define startPin 5

Catch catchCmd(&i, &a);
Attack attackCmd(&i, &a);
Evolve evolveCmd(&i, &a);

Command* commands[] = {

  &catchCmd,
  &attackCmd,
  &evolveCmd

};

Game newgame(commands, 3, &i, &g, &s);

void setup() {

  Serial.begin(115200);
  delay(1000);

  i.begin();
  g.begin();
  s.begin();

  // Pins for BopIt Inputs, TBD
  pinMode(DIAL_PIN, INPUT_PULLUP);
  pinMode(JOYSTICK_PIN, INPUT_PULLUP);
  pinMode(onPin, INPUT_PULLUP);
  pinMode(startPin, INPUT_PULLUP);

  randomSeed(analogRead(0));

}

void loop() {

  newgame.run();

}
