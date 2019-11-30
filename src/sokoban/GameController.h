#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "Map.h"
#include "Definition.h"
#include "GameViewer.h"

class GameController
{
private:
    Map* map;
    GameViewer* gameViewer;
public:
    GameController(Map* map, GameViewer* gameViewer);
    void setGoalPos(int x, int y);
    void gameInitialize();
    void gameDelete();
    bool isInMapNow();
    bool isInMapNow(int x, int y);
    bool checkPosition(int ux, int uy);
    void move(int x, int y);
    void startGame();

    WINDOW* stepBoard, *pushBoard, *gameBoard;

};
#endif