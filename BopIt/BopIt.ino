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

Catch catchCmd(&i, &a);
Attack attackCmd(&i, &a);
Evolve evolveCmd(&i, &a);

Command* commands[] = {

  &catchCmd,
  &attackCmd,
  &evolveCmd 

};

Game newgame(commands, 3, &i, &a, &g); 

void setup() {

  Serial.begin(115200);
  delay(3000);
  Serial.println("[BOOT] STARTING UP");
  
  i.begin();
  g.begin();
  a.begin();

  // Pins for BopIt Inputs, TBD
  pinMode(START, INPUT_PULLUP);

  randomSeed(analogRead(0));

}

void loop() {

  newgame.run();

}