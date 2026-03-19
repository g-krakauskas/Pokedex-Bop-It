#ifndef Game
#define Game

#include "Input.h"
#include "Command.h"

class Game {

  private:

    int score;
    int level;
    float timer;

    Command** commands;
    int numCmds;

    Input* input;

  public:

    Game(Command** cmds, int size, Input* i);
    void run();

};

#endif
