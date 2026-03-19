#include "Attack.h"

#define JOYSTICK 2

Attack::Attack(Input* i, Audio* a) {

  attackI = i;
  attackA = a;

}

bool Attack::execute(int timer) {

  attackA->attackAudio();

  if (attackI->waitForCompletion(JOYSTICK, timer)) {
    attackA->catchSuccess();
    return true;
  }

  return false;
  
}