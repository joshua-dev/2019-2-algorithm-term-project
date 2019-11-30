#include "Wall.h"

Wall::Wall() 
{
    this -> value = 1;
}

Wall::Wall(std::pair<int, int> position) : Wall()
{
    this -> position = position;
}

Wall::~Wall()
{

}

