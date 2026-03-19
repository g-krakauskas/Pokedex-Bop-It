#ifndef Evolve
#define Evolve

#include "Command.h"
#include "Input.h"
#include "Audio.h"

class Evolve : public Command {

    private:

      Input* evolveI;
      Audio* evolveA;

    public:

      catch(Input* i, Audio* a);
      bool execute(int timer);

};

#endif