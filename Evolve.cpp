#include "Evolve.h"

#define SHAKE_PIN 3

Evolve::Evolve(Input* i, Audio* a) {

  evolveI = i;
  evolveA = a;

}

bool Evolve::execute(int timer) {

  evolveA->evolveAudio();

  if (evolveI->waitForCompletion(SHAKE_PIN, timer)) {
    evolveA->evolveSuccess();
    return true;
  }

  return false;
  
}