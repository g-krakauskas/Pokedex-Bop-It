#ifndef Catch
#define Catch

#include "Command.h"
#include "Input.h"
#include "Audio.h"

class Catch : public Command {

    private:

      Input* catchI;
      Audio* catchA;

    public:

      catch(Input* i, Audio* a);
      bool execute(int timer);

};

#endif