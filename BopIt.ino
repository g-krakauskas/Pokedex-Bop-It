#include "Input.h"
#include "Audio.h"
#include "Catch.h"
#include "Attack.h"
#include "Evolve.h"
#include "Game.h"

Input i;
Audio a;

#define DIAL 1
#define JOYSTICK 2
#define SHAKE 3

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

Game newgame(commands, 3);

void setup() {

    // Pins for BopIt Inputs, TBD
    pinMode(DIAL, INPUT);
    pinMode(JOYSTICK, INPUT);
    pinMode(SHAKE, INPUT);

    pinMode(onPin, INPUT);
    pinMode(startPin, INPUT);

    randomSeed(analogRead(0));

}

void loop() {

    game.run();

}
