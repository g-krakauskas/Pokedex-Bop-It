#include "Catch.h"

#define DIAL 1

Catch::Catch(Input* i, Audio* a) {

  catchI = i;
  catchA = a;

}

bool Catch::execute(float timer) {

  catchA->catchAudio();

  bool result = catchI->waitForCompletion(DIAL, timer);

  if (result) catchA->catchSuccess();
  else catchA->fail();

  return result;

}