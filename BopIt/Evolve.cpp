#include "Evolve.h"

#define SHAKE_CMD 3

Evolve::Evolve(Input* i, Audio* a) {

  evolveI = i;
  evolveA = a;

}

bool Evolve::execute(float timer) {

  evolveA->evolveAudio();

  bool result = evolveI->waitForCompletion(SHAKE_CMD, timer, evolveA);
  
  if (result) evolveA->evolveSuccess();
  else evolveA->fail();

  return result;
  
}