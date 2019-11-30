#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <map>

// Interface for map objects

class Object
{
protected:
    int value = 0;
    std::pair<int, int> position;

public:
    // Default Constructor
    Object();

    // Overloaded Constructor
    Object(std::pair<int, int> position, int value = 0);

    int getValue();
    Object &setValue(int value);

    std::pair<int, int> getPosition();
    Object &setPosition(std::pair<int, int>);

    friend class Box;
    friend class Character;
    friend class Destination;
    friend class Wall;
};

#endif
