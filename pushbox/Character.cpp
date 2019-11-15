#include<map>
#include "Character.h"

Character::Character(int value, std::pair<int, int> position, int state, int step, int time) : Space(value, position)
{
    this -> setState(state);
    this -> setStep(step);
    this -> setTime(time);
}