#ifndef _WALL_H_
#define _WALL_H_

#include<map>
#include "Object.h"

class Wall : Object
{
private:
public:
    Wall();
    Wall(std::pair<int, int> position);
    ~Wall();
};

#endif
