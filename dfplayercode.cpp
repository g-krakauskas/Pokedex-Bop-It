#define Start_Byte 0x7E
#define Version_Byte 0xFF
#define Command_Length 0x06
#define End_Byte 0xEF
#define Acknowledge 0x00
#define ACTIVATED LOW

// --- Track constants ---
#define TRACK_CATCH_IT        1
#define TRACK_ATTACK_IT       2
#define TRACK_EVOLVE_IT       3
#define TRACK_CATCH_SUCCESS   4
#define TRACK_ATTACK_SUCCESS  5
#define TRACK_EVOLVE_SUCCESS  6
#define TRACK_GAME_OVER       7
#define TRACK_NEW_ROUND       8
#define TRACK_NEW_ROUND_START 9

int buttonNext = 2;
int buttonPause = 3;
int buttonPrevious = 4;
boolean isPlaying = false;

void setup() {
  pinMode(buttonPause, INPUT_PULLUP);
  pinMode(buttonNext, INPUT_PULLUP);
  pinMode(buttonPrevious, INPUT_PULLUP);

  Serial1.begin(9600, SERIAL_8N1, 18, 17);
  delay(1000);
  playFirst();
  isPlaying = true;
}

void loop() {
  if (digitalRead(buttonPause) == ACTIVATED) {
    if (isPlaying) {
      pauseTrack();
      isPlaying = false;
    } else {
      isPlaying = true;
      resumeTrack();
    }
  }

  if (digitalRead(buttonNext) == ACTIVATED) {
    if (isPlaying) {
      playNext();
    }
  }

  if (digitalRead(buttonPrevious) == ACTIVATED) {
    if (isPlaying) {
      playPrevious();
    }
  }
}

void playFirst() {
  execute_CMD(0x3F, 0, 0);
  delay(500);
  setVolume(20);
  delay(500);
  execute_CMD(0x11, 0, 1);
  delay(500);
}

void pauseTrack() {
  execute_CMD(0x0E, 0, 0);
  delay(500);
}

void resumeTrack() {
  execute_CMD(0x0D, 0, 1);
  delay(500);
}

void playNext() {
  execute_CMD(0x01, 0, 1);
  delay(500);
}

void playPrevious() {
  execute_CMD(0x02, 0, 1);
  delay(500);
}

void playTrack(int track) {
  execute_CMD(0x03, 0, (byte)track);
  delay(500);
}

void setVolume(int volume) {
  execute_CMD(0x06, 0, volume);
  delay(2000);
}

void execute_CMD(byte CMD, byte Par1, byte Par2) {
  word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);

  byte Command_line[10] = {
    Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
    Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte
  };

  for (byte k = 0; k < 10; k++) {
    Serial1.write(Command_line[k]);
  }
}
