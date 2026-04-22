#include "Attack.h"

#define JOYSTICK 2

Attack::Attack(Input* i, Audio* a) {

  attackI = i;
  attackA = a;

}

bool Attack::execute(float timer) {

  attackA->attackAudio();

  bool result = attackI->waitForCompletion(JOYSTICK, timer);

  if (result) attackA->attackSuccess(); 
  else attackA->fail();

  return result;
  
}