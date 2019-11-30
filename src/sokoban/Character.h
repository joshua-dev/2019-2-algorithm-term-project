#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Object.cpp"
#include <map>

class Character : Object
{
private:
    int step = 0, push = 0;
    int value = 5;

public:
    // Default Constructor
    Character();

    // Overloaded Constructor
    Character(std::pair<int, int> position);

    Character &doNothing();
    Character &stepCount();
    Character &pushCount();
};

#endif
