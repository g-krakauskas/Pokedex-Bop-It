#ifndef ATTACK_H
#define ATTACK_H

#include "Command.h"
#include "Input.h"
#include "Audio.h"

class Attack : public Command {

    private:

      Input* attackI;
      Audio* attackA;

    public:

      Attack(Input* i, Audio* a);
      bool execute(int timer);

};

#endif