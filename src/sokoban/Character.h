#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Movable.h"

class Character : Object
{
private:
    int state;
    int step;
    int time;
    Movable *movable;

public:
    Character();
    Character(int value, std::pair<int, int> position, int state, int step, int time);
    void doNothing();
    int getState();
    int getStep();
    int getTime();
    void setState(int state);
    void setStep(int step);
    void setTime(int time);
};

#endif
