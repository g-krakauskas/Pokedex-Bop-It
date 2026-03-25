#include "Display.h"

#define TFT_CLK 12
#define TFT_MOSI 11
#define TFT_DC 10
#define TFT_RST 6

#define TFT_CS_GAME 13
#define TFT_CS_SPRITE 14

void gameDisplay::begin() {

  // TODO: configure LGFX with correct pins for ESP32-S3
  // lcd.init() will need an LGFX config struct specifying the SPI pins above
  Serial.println("[DISPLAY] gameDisplay::begin() - DISABLED");
 
  // lcd.init();
  // lcd.setRotation(1);
  // lcd.fillScreen(TFT_BLACK);

}

void gameDisplay::displayScore(int score, int level) {

  Serial.print("[DISPLAY] displayScore() SCORE = ");
  Serial.print(score);
  Serial.print(" LEVEL = ");
  Serial.println(level);

  // lcd.fillScreen(TFT_BLACK);
  // lcd.setTextSize(3);
  // lcd.setTextColor(TFT_WHITE);

  // String scoreText = "Score: " + String(score);
  // String levelText = "Level: " + String(level);

  // int cx = lcd.width() / 2;
  // int cy = lcd.height() / 2;

  // lcd.drawCenterString(scoreText, cx, cy - 30);
  // lcd.drawCenterString(levelText, cx, cy + 10);

}

void spriteDisplay::begin() {

  // TODO: configure LGFX with correct pins for ESP32-S3
  Serial.println("[DISPLAY] spriteDisplay::begin() - DISABLED");
 
  // lcd.init();
  // lcd.setRotation(1);
  // lcd.fillScreen(TFT_BLACK);
  
}

void spriteDisplay::displaySprite(const uint16_t* sprite) {

  Serial.println("[DISPLAY] displaySprite() called - DISABLED");
  
  // TODO: uncomment once display is configured and sprite array is defined
  // int spriteW = 240;
  // int spriteH = 240;
  // int x = (lcd.width() - spriteW) / 2;
  // int y = (lcd.height() - spriteH) / 2;
  // lcd.fillScreen(TFT_BLACK);
  // lcd.pushImage(x, y, spriteW, spriteH, sprite);
  
}