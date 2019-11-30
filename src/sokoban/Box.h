#ifndef _BOX_H_
#define _BOX_H_

#include "Object.h"
#include "Movable.h"
#include <map>

class Box : Object
{
private:
    int value = 2;
    std::pair<int, int> position;
    bool onDest = false;

public:
    // Overloaded Constructor
    Box(std::pair<int, int> position);

    //Default Destructor
    ~Box();

    Box &arrive();
    Box &setValue();
};

#endif
