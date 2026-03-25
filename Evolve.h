#ifndef EVOLVE_H
#define EVOLVE_H

#include "Command.h"
#include "Input.h"
#include "Audio.h"

class Evolve : public Command {

    private:

      Input* evolveI;
      Audio* evolveA;

    public:

      Evolve(Input* i, Audio* a);
      bool execute(int timer);

};

#endif