#ifndef Attack
#define Attack

#include "Command.h"
#include "Input.h"
#include "Audio.h"

class Attack : public Command {

    private:

      Input* attackI;
      Audio* attackA;

    public:

      catch(Input* i, Audio* a);
      bool execute(int timer);

};

#endif