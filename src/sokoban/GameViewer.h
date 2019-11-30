#ifndef _GMAEVIEWER_H_
#define _GAMEVIEWER_H_

#include "Map.h"
#include "ncurses.h"

class GameViewer
{
public:
    GameViewer();
    GameViewer(Map* map);

    void startView(WINDOW* startMenu);
    void renderLevelBoard(WINDOW* levelBoard);
    void renderStepBoard(WINDOW* stepBoard);
    void renderPushBoard(WINDOW* pushBoard);
    void renderTimeBoard(WINDOW* timeBoard);
    void renderGameBoard(WINDOW* gameBoard);
    void renderAll(WINDOW* levelBoard, WINDOW* stepBoard, WINDOW* pushBoard, WINDOW* timeBoard, WINDOW* gameBoard);
    void renderInit(WINDOW* levelBoard, WINDOW* stepBoard, WINDOW* pushBoard, WINDOW* timeBoard);
    void renderResult();
private:
    Map* map;
};
#endif