#include "Box.h"
#include "Object.h"
#include <map>

Box::Box(std::pair<int, int> position) : position(position)
{
}

Box::~Box()
{
}

Box &Box::arrive()
{
    this->value = 6;
    this->onDest = true;
    return *this;
}

Box &Box::setValue()
{
    if (this->onDest)
        this->value = 6;
    else
        this->value = 2;

    return *this;
}
