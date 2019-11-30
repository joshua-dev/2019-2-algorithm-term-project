#ifndef _OBJECT_H_
#define _OBJECT_H_

// Interface for map objects
#include<map>

class Object
{
protected:
    int value = 0;
    std::pair<int, int> position;

public:
    /** constructor */
    Object();
    Object(int value, std::pair<int, int> position);

    int getValue();
    void setValue(int value);

    std::pair<int, int> getPosition();
    void setPosition(std::pair<int, int>);
};

#endif
