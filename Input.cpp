#include "Input.h"

int Input::readInput() {

  if (!digitalRead(1)) return 1; //map to DIAL pin
  if (!digitalRead(2)) return 2; //map to JOYSTICK pin
  if (checkShake()) return 3; //map to ACCELEROMETER/SHAKE pin

  return 0;

}

bool Input::waitForCompletion(int userInput, int timer) {

  unsigned long startTime = millis();

  while (millis() - startTime < (unsigned long)timer * 1000) {
    if (readInput() == userInput) {
      return true;
    }
    delay(10);
  }

  return false;

}

bool Input::gameOn() {

  if (digitalRead(4) == LOW) { //map pin to on/off switch
    return true;
  }

  return false;

}

bool Input::gameStart() {

  if (digitalRead(5) == LOW) { //map pin to game start/reset button
    return true;
  }

  return false;

}

void Input::begin() {

  Wire.begin(8, 9); // GPIO 8 = Data, GPIO 9 = Clk

  if (mpu.begin()) {
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G); // measurement range for mpu
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); // filters noise at freqs higher than 21 Hz
    mpuGo = true; 
    Serial.println("[INPUT] MPU6050 FOUND");
  }
  else Serial.println("[INPUT] MPU6050 NOT FOUND");

}

bool Input::checkShake() {

  if (!mpuGo) return false;

  sensors_event_t acc, gyro, temp;
  mpu.getEvent(&acc, &gyro, &temp);

  float accTotal = sqrt(
    acc.acceleration.x * acc.acceleration.x +
    acc.acceleration.y * acc.acceleration.y + 
    acc.acceleration.z * acc.acceleration.z) - 9.8;

  return abs(accTotal) > SHAKE;

}