#include "Audio.h"

#define Start_Byte 0x7E
#define Version_Byte 0xFF
#define Command_Length 0x06
#define End_Byte 0xEF
#define Acknowledge 0x00

#define ESP_RX 17
#define ESP_TX 16

void Audio::begin() {

  Serial1.begin(9600, SERIAL_8N1, ESP_RX, ESP_TX);
  delay(1000);

  setVolume(30);
  delay(200);

  Serial.println("[AUDIO] DFPLAYER ON");

}

void Audio::setVolume(int vol) {

  execute_CMD(0x06, 0, (byte)vol);
  delay(200);

}
void Audio::catchAudio() {

  Serial.println("[AUDIO] CATCH IT (DIAL)");
  playTrack(TRACK_CATCH_IT);
  delay(COMMAND_AUDIO_MS);

}

void Audio::attackAudio() {

  Serial.println("[AUDIO] ATTACK IT (JOYSTICK)");
  playTrack(TRACK_ATTACK_IT);
  delay(COMMAND_AUDIO_MS);

}

void Audio::evolveAudio() {

  Serial.println("[AUDIO] EVOLVE IT (SHAKE)");
  playTrack(TRACK_EVOLVE_IT);
  delay(COMMAND_AUDIO_MS);

}

void Audio::catchSuccess() {

  Serial.println("[AUDIO] CAUGHT IT");
  playTrack(TRACK_CATCH_SUCCESS);
  delay(RESULT_AUDIO_MS); 

}

void Audio::attackSuccess() {

  Serial.println("[AUDIO] ATTACKED IT");
  playTrack(TRACK_ATTACK_SUCCESS);
  delay(RESULT_AUDIO_MS);

}

void Audio::evolveSuccess() {

  Serial.println("[AUDIO] EVOLVED IT");
  playTrack(TRACK_EVOLVE_SUCCESS);
  delay(RESULT_AUDIO_MS);

}

void Audio::fail() {

  Serial.println("[AUDIO] YOU FAILED");
  playTrack(TRACK_GAME_OVER);
  delay(RESULT_AUDIO_MS);

}

void Audio::idleStart() {

  playTrack(TRACK_NEW_ROUND);
  delay(200);

}

void Audio::gameStart() {

  playTrack(TRACK_NEW_ROUND_START);
  delay(5000);

}

void Audio::audioWin() {

  playTrack(TRACK_GAME_WIN);
  delay(200);
}

void Audio::wrongInput() {
  playTrack(TRACK_WRONG_INPUT);
  delay(2000);
}

void Audio::playTrack(int track) {

  execute_CMD(0x03, 0, (byte)track);

}

void Audio::execute_CMD(byte CMD, byte Par1, byte Par2) {

  word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);

  byte Command_line[10] = {
    Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
    Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte
  };

  for (byte k = 0; k < 10; k++) {
    Serial1.write(Command_line[k]);
  }
  
}