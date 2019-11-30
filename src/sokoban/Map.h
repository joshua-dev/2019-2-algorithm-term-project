#ifndef __MAP_H__
#define __MAP_H__

#include "Definition.h"
#include <vector>
#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include "ncurses.h"

class Map
{
private:
    int numDest;
    int numBoxOnDest;
    int map[8][8];
    int default_map[8][8];
    int locOfCharacter[2];
    int numStep;
    int numPush;
public:
    Map();

    //Member Function
    void setElement(int x, int y, int input);
    int getElement(int x, int y);
    void setCharacter(int x, int y);
    void setLocOfCharacter(int x, int y);
    void findCharacter();
    void countBoxOnDest();
    void increaseNumStep();
    void increaseNumPush();

    //getter
    int getStep();
    int getPush();
    int getUser_posX();
    int getUser_posY(); 

};


#endif
