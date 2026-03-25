#include "Game.h"
#include <Arduino.h>

Game::Game(Command** cmds, int size, Input* i, gameDisplay* g, spriteDisplay* s) {

  commands = cmds;
  numCmds = size;
  input = i;
  gDisplay = g;
  sDisplay = s;

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

  Serial.println("[DISPLAY] show 'Press Start'screen");

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

  while (score < 100) {

    Serial.print("[GAME] SCORE: ");
    Serial.print(score);
    Serial.print("  LEVEL: ");
    Serial.print(level);
    Serial.print("  TIMER: ");
    Serial.println(timer);

    gDisplay->displayScore(score, level);
    //sDisplay->displaySprite(spriteArray[index]);

    int idx = random(numCmds);

    Serial.print("[GAME] COMMAND SELECTED: ");
    
    if (idx == 0) Serial.println("CATCH (DIAL)");
    else if (idx == 1) Serial.println("ATTACK (JOYSTICK)");
    else Serial.println("EVOLVE (SHAKE)");

    bool success = commands[idx]->execute(timer);

    if (success == true) {

      score++;
      Serial.println("[GAME] SUCCESS!");

      if (score % 10 == 0) {
        timer = max(1.0f, timer-0.5f);
        level++;
        Serial.print("[GAME] LEVEL UP! LEVEL = ");
        Serial.print(level);
        Serial.print(" TIMER = ");
        Serial.println(timer);
        Serial.println("[AUDIO] level up sound");
      }

    }

    else {
      Serial.println("[GAME] GAME OVER");
      Serial.println("[AUDIO] fail sound");
      break;
    }
    
  }

  if (score >= 100) {
    Serial.println("[GAME] YOU WIN");
    Serial.println("[AUDIO] play win sound");
  }

  Serial.print("[GAME] FINAL SCORE: ");
  Serial.println(score);
  gDisplay->displayScore(score, level);
  Serial.println("[DISPLAY] show game over screen");

}