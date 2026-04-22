#ifndef AUDIO_H
#define AUDIO_H

#include <Arduino.h>

#define TRACK_CATCH_IT        1
#define TRACK_ATTACK_IT       2
#define TRACK_EVOLVE_IT       3
#define TRACK_CATCH_SUCCESS   4
#define TRACK_ATTACK_SUCCESS  5
#define TRACK_EVOLVE_SUCCESS  6
#define TRACK_GAME_OVER       7
#define TRACK_NEW_ROUND       8
#define TRACK_NEW_ROUND_START 9
#define TRACK_GAME_WIN        10

#define COMMAND_AUDIO_MS 800
#define RESULT_AUDIO_MS 400

class Audio {

  public:

    void begin();
    void setVolume(int vol);

    void catchAudio();
    void attackAudio();
    void evolveAudio();

    void catchSuccess();
    void attackSuccess();
    void evolveSuccess();

    void idleStart();
    void gameStart();

    void audioWin();
    void fail();

  private:

    void playTrack(int track);
    void execute_CMD(byte CMD, byte Par1, byte Par2);

};

#endif