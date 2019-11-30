#ifndef _BOX_H_
#define _BOX_H_

#include "Movable.h"
#include <Object.cpp>
#include <map>

class Box : Object
{
private:
    int value = 2;
    std::pair<int, int> position;

public:
    // Default Constructor
    Box();

    // Overloaded Constructor
    Box(std::pair<int, int> position, int state);

    //Default Destructor
    ~Box();

    bool onLeft();
    bool onRight();
    bool onUp();
    bool onDown();
};

#endif
