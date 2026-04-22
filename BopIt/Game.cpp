#include "Game.h"
#include <Arduino.h>

#define ROUND_INTERVAL 500

Game::Game(Command** cmds, int size, Input* i, Audio* a, gameDisplay* g) {

  commands = cmds;
  numCmds = size;
  input = i;
  audio = a;
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

  unsigned long lastPrompt = 0;

  while (!input->gameStart()) {

    if (millis() - lastPrompt > 10000) {

      Serial.println("[GAME] WAITING FOR START BUTTON");
      audio->idleStart();
      lastPrompt = millis();

    }
  
    delay(20);

  }

  Serial.println("[GAME] START BUTTON PRESSED");
  audio->gameStart();

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
    gDisplay->gameWin(score);
    audio->audioWin();

    unsigned long winStart = millis();

    while (millis() - winStart < 20000) {
      if (input->gameStart()) break;  // skip celebration
      delay(20);
    }

  }
  else {

    gDisplay->gameOver(score);
    delay(3000);

  }

}