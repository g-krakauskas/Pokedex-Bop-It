#include "Input.h"

int Input::readInput() {

  if (detectDial()) return 1; //map to DIAL pin
  if (detectStick()) return 2; //map to JOYSTICK pin
  if (checkShake()) return 3; //map to ACCELEROMETER/SHAKE pin

  return 0;

}

bool Input::waitForCompletion(int userInput, float timer, Audio* a) {

  if (encoderGo) lastEncoderState = encoder.getEncoderPosition();

  unsigned long startTime = millis();

  while (millis() - startTime < (unsigned long)timer * 1000) {

    int current = readInput();

    if (current == userInput) {
      unsigned long drainStart = millis();
      while (readInput() != 0 && millis() - drainStart < 500){
        delay(10);
      }
      return true;
    }
    else if (current != 0) {
      unsigned long drainStart = millis();
      while (readInput() != 0 && millis() - drainStart < 500){
        delay(10);
      }
      a->wrongInput();
      return false;
    }

    delay(10);

  }

  return false;

}

bool Input::gameStart() {

  if (digitalRead(START) == LOW) { //map pin to game start/reset button
    return true;
  }

  return false;

}

void Input::begin() {

  Wire.begin(8, 9); // GPIO 8 = Data, GPIO 9 = Clk
  Wire.setClock(100000);
  
  Wire1.begin(15,16); //GPIO 15 = Data, GPIO 16 = Clk for ACCEL
  Wire1.setClock(100000);

  if (mpu.begin(0x68, &Wire1)) {
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G); // measurement range for mpu
    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ); // filters noise at freqs higher than 5 Hz
    mpuGo = true; 
    Serial.println("[INPUT] MPU6050 FOUND");
  }
  else Serial.println("[INPUT] MPU6050 NOT FOUND");

  if (encoder.begin(ENCODER_ADDR)) {
    encoder.enableEncoderInterrupt();
    lastEncoderState = encoder.getEncoderPosition();
    encoderGo = true;
    Serial.println("[INPUT] ENCODER ON");
  }
  else Serial.println("[INPUT] ENCODER OFF");

  Serial.println("[INPUT] JOYSTICK FUNCTIONAL WITH GPIO 4 and 7");

}

bool Input::checkShake() {

  if (!mpuGo) return false;

  sensors_event_t acc, gyro, temp;
  
  if (!mpu.getEvent(&acc, &gyro, &temp)) {
    Wire1.end();
    delay(10);
    Wire1.begin(15, 16);
    Wire1.setClock(100000);
    mpu.begin(0x68, &Wire1);
    return false;
  }

  float accTotal = sqrt(
    acc.acceleration.x * acc.acceleration.x +
    acc.acceleration.y * acc.acceleration.y + 
    acc.acceleration.z * acc.acceleration.z);

  static unsigned long lastBeat = 0;
  if (millis() - lastBeat > 1000) {
    Serial.print("[MPU] accTotal = ");
    Serial.println(accTotal, 2);
    lastBeat = millis();
  }

  if (!isfinite(accTotal) || accTotal < 0.5f || accTotal > 100.0f) {
    Serial.println("[INPUT] MPU LOCKED — attempting recovery");
    restartMPU();
    return false;
  }

  return accTotal > SHAKE;

}

bool Input::detectDial() {

  if (!encoderGo) return false;

  int32_t currentState = encoder.getEncoderPosition();
  int32_t twist = abs(currentState - lastEncoderState);

  if (twist >= ENCODER_TWIST) {
    Serial.print("[DIAL] FIRED twist=");
    Serial.print(twist);
    Serial.print(" curr=");
    Serial.print(currentState);
    Serial.print(" last=");
    Serial.println(lastEncoderState); 
    lastEncoderState = currentState;
    return true;
  }

  return false;

}

bool Input::detectStick() {

  int x = analogRead(STICK_X);
  int y = analogRead(STICK_Y);

  bool flickX = abs(x - STICK_C) > STICK_DZ;
  bool flickY = abs(y - STICK_C) > STICK_DZ;

  if (flickX || flickY) {
    Serial.print("[STICK] FIRED x=");
    Serial.print(x);
    Serial.print(" y=");
    Serial.println(y);
  }

  return flickX || flickY;

}

void Input::restartMPU() {

  Wire1.end();

  pinMode(16, OUTPUT);       
  pinMode(15, INPUT_PULLUP);

  for (int i = 0; i < 9 && digitalRead(15) == LOW; i++) {
    digitalWrite(16, LOW);
    delayMicroseconds(5);
    digitalWrite(16, HIGH);
    delayMicroseconds(5);
  }

  // reinitialize MPU
  Wire1.begin(15, 16);
  Wire1.setClock(100000);

  if (mpu.begin(0x68, &Wire1)) {
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
    Serial.println("[INPUT] MPU recovered");
  } 
  else {
    Serial.println("[INPUT] MPU recovery FAILED");
    mpuGo = false; 
  }

}