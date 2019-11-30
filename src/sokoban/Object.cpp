#include "Object.h"

Object::Object()
{
    value = 0;
}
Object::Object(int value, std::pair<int, int> position)
{
    this->value = value;
    this->position = position;
}

int Object::getValue()
{
    return this->value;
}

void Object::setValue(int value)
{
    this->value = value;
}

std::pair<int, int> Object::getPosition()
{
    return this->position;
}

void Object::setPosition(std::pair<int, int> position)
{
    this->position = position;
}
