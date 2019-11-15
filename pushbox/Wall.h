#ifndef _WALL_H_
#define _WALL_H_

class Wall : Space
{
private:

public:
    Wall();
    Wall(int value, std::pair<int, int> position, int state);
    ~Wall();
};
#endif