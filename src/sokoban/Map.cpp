#include "Map.h"
#include<iostream>
#include<fstream>
#include<cstdlib>

Map::Map()
{
    std::ifstream in;
    in.open("map.txt");

    for(int i = 0; i < 8; i++)
    {
        int temp;
        for(int j = 0; j < 8; j++)
        {
            in >> temp;
            map[i][j] = temp;
        }
    }

    countBoxOnDest();
    numStep = 0;
    numPush = 0;
}

void Map::setElement(int x, int y, int input)
{
    this -> map[x][y] = input;
}

int Map::getElement(int x, int y)
{
    return map[x][y];
}

void Map::setCharacter(int x, int y)
{
    this -> map[x][y] = 5;
}

void Map::setLocOfCharacter(int x, int y)
{
    this -> locOfCharacter[0] = x;
    this -> locOfCharacter[1] = y;
}

void Map::findCharacter()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(map[i][j] == 5)
            {
                locOfCharacter[0] = i;
                locOfCharacter[1] = j;
                return;
            }
        }
    }
}
void Map::countBoxOnDest()
{
    this -> numBoxOnDest = 0;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(this -> map[i][j] == 6)
            {
                this ->numBoxOnDest++;
            }
        }
    }
}

void Map::increaseNumStep()
{
    this -> numStep++;
}

void Map::increaseNumPush()
{
    this -> numPush++;
}

int Map::getStep()
{
    return this -> numStep;
}

int Map::getPush()
{
    return this -> numPush;
}

int Map::getUser_posX()
{
    return this -> locOfCharacter[0];
}

int Map::getUser_posY()
{
    return this -> locOfCharacter[1];
}
