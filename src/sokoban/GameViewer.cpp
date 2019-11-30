#include "GameViewer.h"

GameViewer::GameViewer()
{

}
GameViewer::GameViewer(Map* map)
{
    this -> map = map;
}

void GameViewer::startView(WINDOW* startMenu)
{
    startMenu = newwin(19,40,6,2);
}

void GameViewer::renderLevelBoard(WINDOW* levelBoard)
{
    mvwprintw(levelBoard, 1, 8, "%d", 1);
    wrefresh(levelBoard);
    return;
}

void GameViewer::renderStepBoard(WINDOW* stepBoard)
{
    mvwprintw(stepBoard, 1, 8, "%d", 2);
    wrefresh(stepBoard);
    return;
}

void GameViewer::renderPushBoard(WINDOW* pushBoard)
{
    mvwprintw(pushBoard, 1, 8, "%d", 3);
    wrefresh(pushBoard);
    return;
}

void GameViewer::renderTimeBoard(WINDOW* timeBoard)
{
    mvwprintw(timeBoard, 1, 8, "%d", 4);
    wrefresh(timeBoard);
    return;
}

void GameViewer::renderGameBoard(WINDOW* gameBoard)
{

}

void GameViewer::renderAll(WINDOW* levelBoard, WINDOW* stepBoard, WINDOW* pushBoard, WINDOW* timeBoard, WINDOW* gameBoard)
{
    renderLevelBoard(levelBoard);
    renderStepBoard(stepBoard);
    renderPushBoard(pushBoard);
    renderTimeBoard(timeBoard);
    renderGameBoard(gameBoard);
}

void GameViewer::renderInit(WINDOW* levelBoard, WINDOW* stepBoard, WINDOW* pushBoard, WINDOW* timeBoard)
{
    mvwprintw(levelBoard, 1, 8, "   ");
    mvwprintw(stepBoard, 1, 8, "    ");
    mvwprintw(pushBoard, 1, 8, "    ");
    mvwprintw(timeBoard, 1, 8, "    ");
}

void GameViewer::renderResult()
{
    attron(COLOR_PAIR(8));
    mvprintw(2, 27, "S C O R E");
    attroff(COLOR_PAIR(8));
    int score = 1000000, step, push, reset;
    for(int i = 0; i < 10; i++)
    {
        step = 1;
        push = 1;
        reset = 1;
        score -= step * 649 + push * 2646 + reset * 47332;
        mvprintw(5 + i * 2, 9, "Level %d", i + 1);
        mvprintw(5 + i * 2, 24, "Step %d", step);
        mvprintw(5 + i * 2, 34, "Push %d", push);
        mvprintw(5 + i * 2, 44, "Reset %d", reset);
    }

    if(score < 0) score = 0;
    attron(COLOR_PAIR(2));
    mvprintw(18, 0, "                                                                 ", score);
	mvprintw(19, 0, "                      Total Score: %d                             ", score);
	mvprintw(20, 0, "                                                                 ", score);
    attroff(COLOR_PAIR(2));
    mvprintw(22, 18, "Press \'n\' to start new game");
    mvprintw(23, 19, "Press \'q\' to quit the game");
}

