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

void GameViewer::renderStepBoard(WINDOW* stepBoard)
{
    mvwprintw(stepBoard, 1, 7, "%d", map -> getStep());
    wrefresh(stepBoard);
    return;
}

void GameViewer::renderPushBoard(WINDOW* pushBoard)
{
    mvwprintw(pushBoard, 1, 7, "%d", map -> getPush());
    wrefresh(pushBoard);
    return;
}

void GameViewer::renderGameBoard(WINDOW* gameBoard)
{  
    map -> findCharacter();

    int ux = map -> getUser_posX();
    int uy = map -> getUser_posY();
    map -> setElement(ux, uy, CHARACTER);
    
   for(int i = 0; i < 8; i++)
   {
       for(int j = 0; j < 8; j++)
       {
           switch (map -> getElement(i, j))
           {
           case SPACE:
                attron(COLOR_PAIR(0));
			    mvprintw(17 + i, 20 + j, " ");
				attroff(COLOR_PAIR(0));
                break;
            case WALL:
                attron(COLOR_PAIR(1));
				mvprintw(17 + i, 20 + j, " ");
				attroff(COLOR_PAIR(1));
                break;
            case BOX:
                attron(COLOR_PAIR(2));
				mvprintw(17 + i, 20 + j, "\u2752");
				attroff(COLOR_PAIR(2));
                break;
            case DESTINATION:
                attron(COLOR_PAIR(3));
				mvprintw(17 + i, 20 + j, "\u2B1A");
				attroff(COLOR_PAIR(3));
                break;
            case OUTSIDE:
                attron(COLOR_PAIR(4));
				mvprintw(17 + i, 20 + j, " ");
				attroff(COLOR_PAIR(4));
                break;
            case CHARACTER:
                attron(COLOR_PAIR(4));
				mvprintw(17 + i, 20 + j, "C");
				attroff(COLOR_PAIR(4));
                break;
            case BOXONDESTINATION:
                attron(COLOR_PAIR(5));
				mvprintw(17 + i, 20 + j, "\u2752");
				attroff(COLOR_PAIR(5));
                break;
           }
       }
   }
}

void GameViewer::renderAll(WINDOW* stepBoard, WINDOW* pushBoard, WINDOW* gameBoard)
{
    renderStepBoard(stepBoard);
    renderPushBoard(pushBoard);
    renderGameBoard(gameBoard);
}

void GameViewer::renderInit(WINDOW* stepBoard, WINDOW* pushBoard)
{
    mvwprintw(stepBoard, 1, 8, "    ");
    mvwprintw(pushBoard, 1, 8, "    ");
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
        score -= step * 649 + push * 2646;
        mvprintw(5 + i * 2, 24, "Step %d", step);
        mvprintw(5 + i * 2, 34, "Push %d", push);
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

