#ifndef Input
#define Input

#include <Arduino.h>

class Input {

  public:

    bool waitForCompletion(int userInput, int timer);
    int readInput();
    bool gameOn();
    bool gameStart();

};

#endif