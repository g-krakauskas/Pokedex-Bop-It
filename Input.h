#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define SHAKE 15.0 // can adjust for change sens

class Input {

  private:

    Adafruit_MPU6050 mpu;
    bool mpuGo = false;

  public:

    void begin();
    bool waitForCompletion(int userInput, int timer);
    int readInput();
    bool gameOn();
    bool gameStart();
    bool checkShake();

};

#endif