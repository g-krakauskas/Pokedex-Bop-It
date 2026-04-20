#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define SCORE_ADDR 0x27
#define LEVEL_ADDR 0x26 

class gameDisplay {

  private:

    LiquidCrystal_I2C scoreScreen;
    LiquidCrystal_I2C levelScreen;

  public:

    gameDisplay();
    void begin();
    void displayScore(int score, int level);
    void gameOver(int score);
    void gameWin(int score);
    void pressStart();

};

#endif