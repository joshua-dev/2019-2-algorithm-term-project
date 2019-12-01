#include "GameController.h"
#include <queue>

void GameController::gameInitialize()
{
	setlocale(LC_ALL, "");
	initscr();
	resize_term(27, 65);
	start_color();
	curs_set(0);
	noecho();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);   //EMPTY color
	init_pair(3, COLOR_WHITE, COLOR_MAGENTA); //BLOCK color
	init_pair(4, COLOR_WHITE, COLOR_YELLOW);  //BOX color
	init_pair(5, COLOR_WHITE, COLOR_GREEN);   //GOAL color
	init_pair(6, COLOR_WHITE, COLOR_RED);	 //PLAYER color
	init_pair(7, COLOR_WHITE, COLOR_CYAN);	//Start menu color
	init_pair(8, COLOR_RED, COLOR_BLACK);	 //result color

	attron(COLOR_PAIR(7));
	mvprintw(6, 18, "                               ");
	mvprintw(7, 18, "  P U S H    B O X    G A M E  ");
	mvprintw(8, 18, "                               ");
	attroff(COLOR_PAIR(7));
	attron(COLOR_PAIR(6));
	mvprintw(12, 28, "          ");
	mvprintw(13, 28, "   |  |   ");
	mvprintw(14, 28, "          ");
	mvprintw(15, 28, "          ");
	attroff(COLOR_PAIR(6));

	mvprintw(19, 24, "Press \'S\' to start");

	while (1)
	{
		char temp = getch();
		if (temp != 's' && temp != 'S')
		{
			continue;
		}
		else
			break;
	}
	clear();
	startGame();
}

void GameController::gameDelete()
{
	delwin(levelBoard);
	delwin(stepBoard);
	delwin(pushBoard);
	delwin(resetBoard);
	delwin(gameBoard);
	endwin();
	return;
}

bool GameController::isInMapNow()
{
	return 0 < pushBox->getX_userPos() && pushBox->getX_userPos() < pushBox->getRow() &&
		   0 < pushBox->getY_userPos() && pushBox->getY_userPos() < pushBox->getCol();
}

bool GameController::isInMapNow(int dy, int dx)
{
	return 0 < dx && dx < pushBox->getRow() && 0 < dy && dy < pushBox->getCol();
}

bool GameController::CheckPosition(Coordinates userposition)
{
	if (!isInMapNow())
		return false;

	int dx = pushBox->getX_userPos() + userposition.x;
	int dy = pushBox->getY_userPos() + userposition.y;

	if (!isInMapNow(dy, dx))
		return false;

	if (pushBox->getMap(dy, dx) == 1)
		return false;

	return true;
}

void GameController::setGoalPos(vector<Coordinates> goalList)
{
	for (int i = 0; i < goalList.size(); i++)
	{
		int goalX = goalList[i].x;
		int goalY = goalList[i].y;

		if (pushBox->getMap(goalY, goalX) == EMPTY)
			pushBox->setMap(Coordinates(goalY, goalX), GOAL);
	}
}

void GameController::move(Coordinates userposition)
{
	pushBox->addStep();

	int curX = pushBox->getX_userPos();
	int curY = pushBox->getY_userPos();

	int nextX = curX + userposition.x;
	int nextY = curY + userposition.y;

	if (pushBox->getMap(nextY, nextX) == WALL)
		return;

	// When pushes the Box
	if (pushBox->getMap(nextY, nextX) == BOX)
	{
		int nextPosBox_X = nextX + userposition.x;
		int nextPosBox_Y = nextY + userposition.y;

		if (pushBox->getMap(nextPosBox_Y, nextPosBox_X) == BOX || pushBox->getMap(nextPosBox_Y, nextPosBox_X) == WALL)
			return;

		pushBox->setMap(Coordinates(curY, curX), EMPTY);
		pushBox->setMap(Coordinates(nextY, nextX), PLAYER);
		pushBox->setMap(Coordinates(nextPosBox_Y, nextPosBox_X), BOX);
		pushBox->setUserPos(Coordinates(nextX, nextY));
		pushBox->addPush();
		return;
	}

	pushBox->setMap(Coordinates(curY, curX), EMPTY);
	pushBox->setMap(Coordinates(nextY, nextX), PLAYER);
	pushBox->setUserPos(Coordinates(nextX, nextY));
}

bool GameController::postProcessing()
{
	setGoalPos(pushBox->getGoalList());
	gameViewer->renderAll(levelBoard, stepBoard, pushBoard, resetBoard, gameBoard);

	if (isSuccess())
	{
		vector<int> rec;
		rec.push_back(pushBox->getStep());
		rec.push_back(pushBox->getPush());
		rec.push_back(pushBox->getReset());
		pushBox->addRecords(rec);

		if (pushBox->getLevel() == FINALLEVEL)
			return showResult();

		else
		{
			pushBox->setLevel(pushBox->getLevel() + 1);
			pushBox->stepClear();
			pushBox->pushClear();
			pushBox->resetClear();
			pushBox->readMap();
			gameViewer->renderInit(levelBoard, stepBoard, pushBoard, resetBoard);
			gameViewer->renderAll(levelBoard, stepBoard, pushBoard, resetBoard, gameBoard);
		}
	}

	return false;
}

bool GameController::isSuccess()
{
	for (int i = 0; i < pushBox->getGoalList().size(); i++)
	{
		int x = pushBox->getGoalList()[i].x;
		int y = pushBox->getGoalList()[i].y;

		if (pushBox->getMap(y, x) == BOX)
			continue;

		else
			return false;
	}

	return true;
}

void GameController::goNextLevel()
{
	for (int i = 0; i < pushBox->getGoalList().size(); i++)
	{
		int x = pushBox->getGoalList()[i].x;
		int y = pushBox->getGoalList()[i].y;
		pushBox->setMap(Coordinates(y, x), BOX);
	}

	return;
}

void GameController::reset()
{
	pushBox->stepClear();
	pushBox->pushClear();
	pushBox->readMap();
	gameViewer->renderInit(levelBoard, stepBoard, pushBoard, resetBoard);
	gameViewer->renderAll(levelBoard, stepBoard, pushBoard, resetBoard, gameBoard);
	pushBox->addReset();
	return;
}

void GameController::startGame()
{
	mvprintw(3, 18, "P U S H    B O X    G A M E");
	mvprintw(24, 23, "Press \'r\' to reset ");
	mvprintw(26, 23, "Press \'a\' to auto-resolve ");
	refresh();

	gameBoard = newwin(15, 38, 8, 4);
	levelBoard = newwin(3, 13, 8, 45);
	stepBoard = newwin(3, 13, 12, 45);
	pushBoard = newwin(3, 13, 16, 45);
	resetBoard = newwin(3, 13, 20, 45);
	wbkgd(levelBoard, COLOR_PAIR(1));
	wattron(levelBoard, COLOR_PAIR(1));
	wbkgd(stepBoard, COLOR_PAIR(1));
	wattron(stepBoard, COLOR_PAIR(1));
	wbkgd(pushBoard, COLOR_PAIR(1));
	wattron(pushBoard, COLOR_PAIR(1));
	wbkgd(resetBoard, COLOR_PAIR(1));
	wattron(resetBoard, COLOR_PAIR(1));

	mvwprintw(levelBoard, 1, 1, "Level: ");
	mvwprintw(levelBoard, 1, 8, " ");
	mvwprintw(stepBoard, 1, 1, "Move: ");
	mvwprintw(stepBoard, 1, 8, " ");
	mvwprintw(pushBoard, 1, 1, "Push: ");
	mvwprintw(pushBoard, 1, 8, " ");
	mvwprintw(resetBoard, 1, 1, "Reset: ");
	mvwprintw(resetBoard, 1, 8, " ");
	wborder(levelBoard, '|', '|', '-', '-', '+', '+', '+', '+');
	wborder(stepBoard, '|', '|', '-', '-', '+', '+', '+', '+');
	wborder(pushBoard, '|', '|', '-', '-', '+', '+', '+', '+');
	wborder(resetBoard, '|', '|', '-', '-', '+', '+', '+', '+');
	wborder(gameBoard, '|', '|', '-', '-', '+', '+', '+', '+');

	wrefresh(levelBoard);
	wrefresh(stepBoard);
	wrefresh(pushBoard);
	wrefresh(resetBoard);
	wrefresh(gameBoard);
}

bool GameController::showResult()
{
	clear();
	gameViewer->renderResult();
	while (1)
	{
		char t = getch();
		if (t == 'q' || t == 'Q')
			return true;

		else if (t == 'n' || t == 'N')
		{
			pushBox->setLevel(1);
			pushBox->clearRecords();
			pushBox->resetClear();
			pushBox->readMap();
			clear();
			startGame();
			gameViewer->renderAll(levelBoard, stepBoard, pushBoard, resetBoard, gameBoard);
			return false;
		}

		else
			continue;
	}
}

void GameController::autoResolve()
{
	static queue<char> routes;

	// Get Goals' position
	vector<Coordinates> goals = pushBox->getGoalList();

	int goalPosX = goals[0].x;
	int goalPosY = goals[0].y;

	// Get Boxs' position
	int boxPosX, boxPosY;

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (pushBox->getMap(i, j) == BOX)
				boxPosX = i, boxPosY = j;

	int moveBoxX = goalPosX - boxPosX, moveBoxY = goalPosY - boxPosY;

	for (int i = 0; i < abs(moveBoxX); i++)
	{
		if (moveBoxX > 0)
			routes.push('r');
		else
			routes.push('l');
	}

	for (int i = 0; i < abs(moveBoxY); i++)
	{
		if (moveBoxY > 0)
			routes.push('d');
		else
			routes.push('u');
	}

	while (!routes.empty())
	{
		char direction = routes.back();
		routes.pop();

		switch (direction)
		{
			// Get Player's position
			int playerPosX = pushBox->getX_userPos(), playerPosY = pushBox->getY_userPos();

		case 'u':
			// set Player to Box's down position, move Up
			if (playerPosX != boxPosX || playerPosY != boxPosY + 1)
			{
				int movePlayerX = boxPosX - playerPosX, movePlayerY = boxPosY + 1 - playerPosY;
				for (int i = 0; i < abs(movePlayerX); i++)
				{
					if (movePlayerX > 0)
						move(Coordinates(1, 0));
					else
						move(Coordinates(-1, 0));
				}

				for (int i = 0; i < abs(movePlayerY); i++)
				{
					if (movePlayerY > 0)
						move(Coordinates(0, 1));
					else
						move(Coordinates(0, -1));
				}
			}
			move(Coordinates(0, -1));
			break;

		case 'd':
			// set Player to Box's up position, move Down
			if (playerPosX != boxPosX || playerPosY != boxPosY - 1)
			{
				int movePlayerX = boxPosX - playerPosX, movePlayerY = boxPosY - 1 - playerPosY;
				for (int i = 0; i < abs(movePlayerX); i++)
				{
					if (movePlayerX > 0)
						move(Coordinates(1, 0));
					else
						move(Coordinates(-1, 0));
				}

				for (int i = 0; i < abs(movePlayerY); i++)
				{
					if (movePlayerY > 0)
						move(Coordinates(0, 1));
					else
						move(Coordinates(0, -1));
				}
			}
			move(Coordinates(0, 1));
			break;

		case 'r':
			// set Player to Box's left position, move Right
			if (playerPosX != boxPosX - 1 || playerPosY != boxPosY)
			{
				int movePlayerX = boxPosX - 1 - playerPosX, movePlayerY = boxPosY - playerPosY;
				for (int i = 0; i < abs(movePlayerX); i++)
				{
					if (movePlayerX > 0)
						move(Coordinates(1, 0));
					else
						move(Coordinates(-1, 0));
				}

				for (int i = 0; i < abs(movePlayerY); i++)
				{
					if (movePlayerY > 0)
						move(Coordinates(0, 1));
					else
						move(Coordinates(0, -1));
				}
			}
			move(Coordinates(1, 0));
			break;

		case 'l':
			// set Player to Box's right position, move Left
			if (playerPosX != boxPosX + 1 || playerPosY != boxPosY)
			{
				int movePlayerX = boxPosX + 1 - playerPosX, movePlayerY = boxPosY - playerPosY;
				for (int i = 0; i < abs(movePlayerX); i++)
				{
					if (movePlayerX > 0)
						move(Coordinates(1, 0));
					else
						move(Coordinates(-1, 0));
				}

				for (int i = 0; i < abs(movePlayerY); i++)
				{
					if (movePlayerY > 0)
						move(Coordinates(0, 1));
					else
						move(Coordinates(0, -1));
				}
			}
			move(Coordinates(-1, 0));
			break;

		default:
			break;
		} // end swtich

	} // end while
}
