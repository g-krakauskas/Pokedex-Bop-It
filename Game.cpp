#include "Game.h"
#include <Arduino.h>

Game::Game(Command** cmds, int size, Input* i) {

  commands = cmds;
  numCmds = size;
  input = i;

  score = 0;
  level = 1;
  timer = 5;
  
}

void Game::run() {
  
  while (!input->gameOn()) {
    delay(100);
  }

  // Message on Display for game on

  bool lastReset = false;

  while (true) {

    bool reset = input->gameStart();

    if (reset && !lastReset) {
      // Audio output to start game
      break; // Exits loop to start game
    } 

    lastReset = reset;
    delay(20);

  }
  
  // Game Start
  score = 0;
  level = 1;
  timer = 5;

  while (score < 100) {

    int idx = random(numCmds);
    bool success = commands[idx]->execute(timer);

    if (success == true) {

      score++;

      if (score % 10 == 0) {
        timer -= 0.5;
        level++;
      }

    }

    else {break};
    
  }

  // Write Code to output GAME OVER / Score Audio

}