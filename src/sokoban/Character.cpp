#include <map>
#include "Character.h"

Character::Character() : Object()
{
}

Character::Character(std::pair<int, int> position) : Object(position)
{
}

Character &Character::doNothing()
{
    return *this;
}

Character &Character::stepCount()
{
    this->step++;
    return *this;
}

Character &Character::pushCount()
{
    this->push++;
    return *this;
}
