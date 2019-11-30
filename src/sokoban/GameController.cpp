#include "GameController.h"

GameController::GameController(Map* map, GameViewer* gameViewer)
{
    this -> map = map;
    this -> gameViewer = gameViewer;
}

void GameController::setGoalPos(int x, int y)
{

}

void GameController::gameInitialize()
{
    initscr();
	resize_term(40, 50);
	start_color();
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
	init_pair(0, COLOR_BLACK, COLOR_BLUE);
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, COLOR_WHITE);
	init_pair(5, COLOR_RED, COLOR_BLACK);

    border('|', '|', '-', '-', '+', '+', '+', '+');
	mvprintw(1, 9, "Welcome To The Push Box Game!");
	mvprintw(2, 12, "Press Any Key To Start");
	refresh(); // 화면 업데이트. 화면 실제 출력
	curs_set(0);
    getch();

    startGame();
}

void gameDelete()
{

}

bool isInMapNow()
{

}

bool isInMapNow(int x, int y)
{

}

bool checkPosition(int ux, int uy)
{

}

void GameController::move(int x, int y)
{
    map -> increaseNumStep();

    //캐릭터 방향에 비어있거나 목적지이면 캐릭터 이동
    int ux = map -> getUser_posX();
    int uy = map -> getUser_posY();

    int nextX = ux + x;
    int nextY = uy + y;

    //캐릭터가 움직이는 방향이 벽일 경우
    if(map -> getElement(nextX, nextY) == WALL)
    {
        return;
    }

    //Box를 밀때
    if(map -> getElement(nextX, nextY) == BOX)
    {
        int nextPosBox_X = nextX + x;
        int nextPosBox_Y = nextY + y;

        if(map -> getElement(nextPosBox_X, nextPosBox_Y) == BOX ||
            map -> getElement(nextPosBox_X, nextPosBox_Y) == WALL)
            {
                return;
            }
        map -> setElement(ux, uy, SPACE);
        map -> setElement(nextX, nextY, CHARACTER);
        map -> setElement(nextPosBox_X, nextPosBox_Y, BOX);
        map -> setLocOfCharacter(nextX, nextY);
        map -> increaseNumPush();
        return;
    }

    map -> setElement(ux, uy, SPACE);
    map -> setElement(nextX, nextY, CHARACTER);
    map -> setLocOfCharacter(nextX, nextY);
}

void GameController::startGame()
{
    mvprintw(3, 18, "P U S H    B O X    G A M E");
	refresh();

    gameBoard = newwin(12, 12, 16, 19);
    wbkgd(gameBoard, COLOR_PAIR(10));
    wattron(gameBoard, COLOR_PAIR(10));
    wborder(gameBoard, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(gameBoard);

    stepBoard = newwin(5, 14, 7, 9);
    wbkgd(stepBoard, COLOR_PAIR(3));
    wattron(stepBoard, COLOR_PAIR(3));
    mvprintw(1, 1, "Step: ");
    wborder(stepBoard, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(stepBoard);

    pushBoard = newwin(5, 14, 7, 27);
    wbkgd(pushBoard, COLOR_PAIR(3));
    wattron(pushBoard, COLOR_PAIR(3));
    mvwprintw(pushBoard, 1, 1, "PUSH: ");
    wborder(pushBoard, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(pushBoard);
}