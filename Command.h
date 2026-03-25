#ifndef COMMAND_H
#define COMMAND_H

class Command {

  public: 
    
    virtual bool execute(int timer) = 0;

};

#endif

