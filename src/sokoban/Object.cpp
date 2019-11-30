#include "Object.h"


Object::Object() : position(std::pair(0, 0))
{
}

Object::Object(std::pair<int, int> position, int value = 0) : position(position), value(value)
{
}

int Object::getValue()
{
    return this->value;
}


Object &Object::setValue(int value)

{
    this->value = value;
    return *this;
}

std::pair<int, int> Object::getPosition()
{
    return this->position;
}


Object &Object::setPosition(std::pair<int, int> position)

{
    this->position = position;
    return *this;
}
