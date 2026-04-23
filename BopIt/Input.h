#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_seesaw.h>
#include <Wire.h>
#include "Audio.h"

#define START 21

#define SHAKE 30.0 // can adjust to change sens

#define ENCODER_ADDR 0x49 
#define ENCODER_TWIST 5 

#define STICK_X 4
#define STICK_Y 7
#define STICK_C 2048
#define STICK_DZ 1500

class Input {

  private:

    Adafruit_MPU6050 mpu;
    bool mpuGo = false;

    Adafruit_seesaw encoder;
    bool encoderGo = false;
    int32_t lastEncoderState = 0;

  public:

    void begin();
    bool waitForCompletion(int userInput, float timer, Audio* a);
    int readInput();
    bool gameStart();
    bool checkShake();
    bool detectDial();
    bool detectStick();
    void restartMPU();

};

#endif