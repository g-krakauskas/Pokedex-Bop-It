#ifndef GAME_H
#define GAME_H

#include "Input.h"
#include "Command.h"
#include "Display.h"

class Game {

  private:

    int score;
    int level;
    float timer;

    gameDisplay* gDisplay;

    Command** commands;
    int numCmds;

    Input* input;

  public:

    Game(Command** cmds, int size, Input* i, gameDisplay* g);
    void run();

};

#endif