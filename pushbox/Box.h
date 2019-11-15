#ifndef _BOX_H_
#define _BOX_H_

#include "Movable.h"

class Box : Space
{
private:
    Movable moveBehavior;
public:
    Box();
    Box(int value, std::pair<int, int> position, int state);
    ~Box();
    bool onLeft();
    bool onRight();
    bool onUp();
    bool onDown();
};

#endif