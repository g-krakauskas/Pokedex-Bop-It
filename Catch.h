#ifndef CATCH_H
#define CATCH_H

#include "Command.h"
#include "Input.h"
#include "Audio.h"

class Catch : public Command {

    private:

      Input* catchI;
      Audio* catchA;

    public:

      Catch(Input* i, Audio* a);
      bool execute(int timer);

};

#endif