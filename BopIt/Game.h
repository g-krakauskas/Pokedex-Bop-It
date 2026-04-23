#ifndef GAME_H
#define GAME_H

#include "Input.h"
#include "Command.h"
#include "Display.h"
#include "Audio.h"

class Game {

  private:

    int score;
    int level;
    float timer;
    bool skipIdle = false;

    gameDisplay* gDisplay;

    Command** commands;
    int numCmds;

    Input* input;
    Audio* audio;

  public:

    Game(Command** cmds, int size, Input* i, Audio* a, gameDisplay* g);
    void run();

};

#endif