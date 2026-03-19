#include "Catch.h"

#define DIAL 1

Catch::Catch(Input* i, Audio* a) {

  catchI = i;
  catchA = a;

}

bool Catch::execute(int timer) {

  catchA->catchAudio();

  if (catchI->waitForCompletion(DIAL, timer)) {
    catchA ->catchSuccess();
    return true;
  }

  return false;

}