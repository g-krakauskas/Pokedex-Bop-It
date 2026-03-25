#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <LovyanGFX.h>
#include <SPI.h>

class gameDisplay {

  private:

    LGFX lcd;

  public:

    void begin();
    void displayScore(int score, int level);

};

class spriteDisplay {

  private:

    LGFX lcd;

  public:

    void begin();
    void displaySprite(const uint16_t* sprite);

};

#endif