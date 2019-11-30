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
    void renderStepBoard(WINDOW* stepBoard);
    void renderPushBoard(WINDOW* pushBoard);
    void renderGameBoard(WINDOW* gameBoard);
    void renderAll(WINDOW* stepBoard, WINDOW* pushBoard, WINDOW* gameBoard);
    void renderInit(WINDOW* stepBoard, WINDOW* pushBoard);
    void renderResult();
private:
    Map* map;
};
#endif