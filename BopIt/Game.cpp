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

  Serial.println("[GAME] POWER ON");

  if (!skipIdle) {

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

  }

  skipIdle = false;

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
        
        level++;

        if (level == 2) {
          timer = timer - 1.0f;
        }
        else if (level == 3) {
          timer = timer - 0.5f;
        }
        else {
          timer = timer - 0.25f;
        }

        timer = max(1.0f, timer);
        
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

    const unsigned long TRACK_WIN_MS  = 64000;
    unsigned long winStart = millis();

    while (!input->gameStart()) {

      if (millis() - winStart >= TRACK_WIN_MS) {
        
        Serial.println("[GAME] PRESS START TO REPLAY");
        audio->idleStart();

        unsigned long promptStart = millis();
        bool pressed = false;

        while (millis() - promptStart < 4000) {
          if (input->gameStart()) {
            pressed = true;
            break;
          }
          delay(20);
        }

        if (pressed) break;

        audio->audioWin();
        winStart = millis();

      }

      delay(20);

    }

    Serial.println("[GAME] START PRESSED ");

    while(input->gameStart()) {
      delay(20);
    }
    
    delay(200);

    skipIdle = true;

  }
  else {

    gDisplay->gameOver(score, level);
    delay(3000);

  }

}