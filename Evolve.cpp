#include "Evolve.h"

#define SHAKE 3

Evolve::Evolve(Input* i, Audio* a) {

  evolveI = i;
  evolveA = a;

}

bool Evolve::execute(int timer) {

  evolveA->evolveAudio();

  if (evolveI->waitForCompletion(SHAKE, timer)) {
    evolveA->catchSuccess();
    return true;
  }

  return false;
  
}