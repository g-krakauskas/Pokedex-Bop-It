#include "Display.h"

gameDisplay::gameDisplay() : 

  scoreScreen(SCORE_ADDR, 20, 4), 
  levelScreen(LEVEL_ADDR, 20, 4) {

}

void gameDisplay::begin() {

  scoreScreen.init();
  scoreScreen.backlight();
  scoreScreen.clear();

  scoreScreen.setCursor(5, 0);
  scoreScreen.print("SCORE: ");
  Serial.println("[DISPLAY] S-SCREEN STARTED");

  levelScreen.init();
  levelScreen.backlight();
  levelScreen.clear();
  levelScreen.setCursor(5, 0);
  levelScreen.print("LEVEL: ");
  Serial.println("[DISPLAY] L-SCREEN STARTED");

}

void gameDisplay::displayScore(int score, int level) {

  scoreScreen.init();
  scoreScreen.backlight();
  scoreScreen.setCursor(5, 0);
  scoreScreen.print("SCORE: ");

  levelScreen.init();
  levelScreen.backlight();
  levelScreen.setCursor(5, 0);
  levelScreen.print("LEVEL: ");

  int digits;
  if (score >= 100) digits = 3;
  else if (score >= 10) digits = 2;
  else digits = 1;

  int place = (20 - digits) / 2;

  scoreScreen.setCursor(0, 1);
  scoreScreen.print("                    ");
  scoreScreen.setCursor((place - 1), 1);
  scoreScreen.print(score);

  levelScreen.setCursor(0, 1);
  levelScreen.print("                    "); 
  levelScreen.setCursor((place - 1), 1);
  levelScreen.print(level);

  Serial.print("[DISPLAY] SCORE = ");
  Serial.print(score);
  Serial.print("  LEVEL = ");
  Serial.println(level);  

}

void gameDisplay::gameOver(int score) {

  int digits;
  if (score >= 100) digits = 3;
  else if (score >= 10) digits = 2;
  else digits = 1;

  int place = (20 - digits) / 2;

  scoreScreen.init();
  scoreScreen.backlight();
  scoreScreen.setCursor(3, 0);
  scoreScreen.print("GAME OVER:");
  scoreScreen.setCursor((place - 2), 1);
  scoreScreen.print(score);

  Serial.print("[DISPLAY] GAME OVER: SCORE = ");
  Serial.print(score);

}

void gameDisplay::gameWin(int score) {

  scoreScreen.init();
  scoreScreen.backlight();
  scoreScreen.setCursor(4, 0);
  scoreScreen.print("YOU WIN!");
  scoreScreen.setCursor(6, 1);
  scoreScreen.print(score);

  Serial.print("[DISPLAY] YOU WIN: SCORE = ");
  Serial.print(score);

}

void gameDisplay::pressStart() {

  scoreScreen.init();
  scoreScreen.backlight();
  scoreScreen.clear();
  scoreScreen.setCursor(1, 0);
  scoreScreen.print("POKEDEX BOP IT");

  levelScreen.init();
  levelScreen.backlight();
  levelScreen.clear();
  levelScreen.setCursor(2, 0);
  levelScreen.print("PRESS START!");

  Serial.println("[DISPLAY] PRESS START BUTTON");

}