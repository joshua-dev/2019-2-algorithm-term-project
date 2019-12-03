#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "GameViewer.h"
#include "Solver.h"
#include <queue>

class GameController
{
public:
	/**
	 * Constructor
	 */
	GameController(){};

	GameController(PushBox *model, GameViewer *view) : pushBox(model), gameViewer(view)
	{
	}

	void setGoalPos(vector<Coordinates> goalposition);
	void gameInitialize();
	void gameDelete();
	bool isInMapNow();
	bool isInMapNow(int dy, int dx);
	bool CheckPosition(Coordinates userPos);
	void move(Coordinates userPos);
	bool postProcessing();
	bool isSuccess();
	WINDOW *levelBoard, *stepBoard, *pushBoard, *resetBoard, *gameBoard;
	void goNextLevel();
	void reset();
	void autoResolve();
	void startGame();
	bool showResult();

private:
	const int FINALLEVEL = 5;
	PushBox *pushBox;
	GameViewer *gameViewer;
};

#endif
