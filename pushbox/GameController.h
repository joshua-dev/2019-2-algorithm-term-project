#ifndef __GAMECONTROLLER__
#define __GMAECONTROLLER__

#include "PushBoxGame.h"
#include<GameView.h"

class GameController
{
public:
    GameController() { };
    GameController(PushGame* stage, GameViewer* view)
    {
        this -> game = stage;
        this -> view = view;
    }
private:
    PushGame* game;
    GameViewer* viewer;
}

#endif