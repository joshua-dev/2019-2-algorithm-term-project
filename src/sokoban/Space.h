#ifndef _SPACE_H_
#define _SPACE_H_

// Interface for map space

#include <map>

class Space
{
private:
    int value;
    std::pair<int, int> position;

public:
    /** constructor */
    Space(int value, std::pair<int, int> position);

    int getValue();
    void setValue(int value);

    std::pair<int, int> getPosition();
    void setPosition(std::pair<int, int>);
};

#endif
