#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "Map.h"

class GameManager
{
private:
    Map *map;

public:
    GameManager();
    GameManager(Map *map);
    ~GameManager();
    void gameStart();
    void gameOver();
    void gameSuccess();
};

#endif
