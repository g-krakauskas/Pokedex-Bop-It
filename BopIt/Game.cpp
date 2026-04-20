#include "Game.h"
#include <Arduino.h>

#define ROUND_INTERVAL 500

Game::Game(Command** cmds, int size, Input* i, gameDisplay* g) {

  commands = cmds;
  numCmds = size;
  input = i;
  gDisplay = g;

  score = 0;
  level = 1;
  timer = 5.0f;
  
}

void Game::run() {
  
  Serial.println("[GAME] WAITING FOR POWER SWITCH");
  while (!input->gameOn()) {
    delay(100);
  }

  Serial.println("[GAME] POWER ON");

  gDisplay->pressStart();

  Serial.println("[GAME] WAITING FOR START BUTTON");

  bool lastReset = false;

  while (true) {

    bool reset = input->gameStart();

    if (reset && !lastReset) {
      Serial.println("[GAME] START BUTTON PRESSED");
      // Audio output to start game
      break; // Exits loop to start game
    } 

    lastReset = reset;
    delay(20);

  }
  
  // Game Start
  score = 0;
  level = 1;
  timer = 5.0f;
  Serial.println("[GAME] GAME STARTED");
  gDisplay->displayScore(score, level);

  while (score < 100) {

    Serial.print("[GAME] SCORE: ");
    Serial.print(score);
    Serial.print("  LEVEL: ");
    Serial.print(level);
    Serial.print("  TIMER: ");
    Serial.println(timer);

    int idx = random(numCmds);

    Serial.print("[GAME] COMMAND SELECTED: ");
    
    if (idx == 0) Serial.println("CATCH (DIAL)");
    else if (idx == 1) Serial.println("ATTACK (JOYSTICK)");
    else Serial.println("EVOLVE (SHAKE)");

    bool success = commands[idx]->execute(timer);

    if (success) {

      score++;
      Serial.println("[GAME] SUCCESS!");

      if (score % 10 == 0 && level <= 9) {
        timer = max(1.0f, timer-0.25f);
        level++;
        Serial.print("[GAME] LEVEL UP! LEVEL = ");
        Serial.print(level);
        Serial.print(" TIMER = ");
        Serial.println(timer);
        Serial.println("[AUDIO] level up sound");
      }

      gDisplay->displayScore(score, level);

      delay(ROUND_INTERVAL);

    }

    else {
      Serial.println("[GAME] GAME OVER");
      break;
    }
    
  }

  if (score >= 100) {
    Serial.println("[GAME] YOU WIN");
    Serial.println("[AUDIO] play win sound");
    gDisplay->gameWin(score);
  }
  else {
    gDisplay->gameOver(score);
  }

}