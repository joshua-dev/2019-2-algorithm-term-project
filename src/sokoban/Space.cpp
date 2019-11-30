#include "Space.h"

Space::Space(int value, std::pair<int, int> position)
{
    this->value = value;
    this->position = position;
}

int Space::getValue()
{
    return this->value;
}

void Space::setValue(int value)
{
    this->value = value;
}

std::pair<int, int> Space::getPosition()
{
    return this->position;
}

void Space::setPosition(std::pair<int, int> position)
{
    this->position = position;
}
