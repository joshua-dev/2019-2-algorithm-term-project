#ifndef _BOX_H_
#define _BOX_H_

#include "Movable.h"
#include<map>

class Box : Space
{
private:
    int value;
    std::pair<int, int> position;
    Movable moveBehavior;

public:
    //Default Constructor
    Box();
    Box(int value, std::pair<int, int> position, int state);
    //Default Destructor
    ~Box();
    //박스 옆이 빈 공간이라면 움직인다.
    bool onLeft();
    bool onRight();
    bool onUp();
    bool onDown();
};

#endif
