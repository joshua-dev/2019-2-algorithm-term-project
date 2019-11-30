#ifndef _GAMEVIEWER_H_
#define _GAMEVIEWER_H_

#include "PushBox.h"

class GameViewer {
public:
	GameViewer() {};
	GameViewer(PushBox* model)
	{
		PushBox = model;
	}
	void startview(WINDOW* startMenu) {

		startMenu = newwin(19, 40, 6, 2);
	}
	void renderLevelBoard(WINDOW* levelBoard) {
		mvwprintw(levelBoard, 1, 8, "%d", PushBox->getLevel());
		wrefresh(levelBoard);
		return;
	}
	void renderStepBoard(WINDOW* stepBoard) {
		mvwprintw(stepBoard, 1, 8, "%d", PushBox->getStep());
		wrefresh(stepBoard);
		return;
	}
	void renderPushBoard(WINDOW* pushBoard) {
		mvwprintw(pushBoard, 1, 8, "%d", PushBox->getPush());
		wrefresh(pushBoard);
		return;
	}
	void renderTimeBoard(WINDOW* resetBoard) {
		mvwprintw(resetBoard, 1, 8, "%d", PushBox->getReset());
		wrefresh(resetBoard);
		return;
	}
	void renderGameBoard(WINDOW* gameBoard) {
		int rowHandle = (15 - PushBox->getRow()) / 2;
		int colHandle = (38 - PushBox->getCol() * 2) / 2 + 1;
		int ux = PushBox->getX_userPos();
		int uy = PushBox->getY_userPos();
		char temp = PushBox->getMap(uy, ux);
		PushBox->setMap(Coordinates(uy, ux), PLAYER);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 20; j++) {
				switch (PushBox->getMap(i, j / 2))
				{
				case EMPTY:
					wattron(gameBoard, COLOR_PAIR(2));
					mvwprintw(gameBoard, i + rowHandle, j + colHandle, " ");
					wattroff(gameBoard, COLOR_PAIR(2));
					break;
				case WALL:
					wattron(gameBoard, COLOR_PAIR(3));
					mvwprintw(gameBoard, i + rowHandle, j + colHandle, " ");
					wattroff(gameBoard, COLOR_PAIR(3));
					break;
				case BOX:
					wattron(gameBoard, COLOR_PAIR(4));
					if (j % 2 == 0) {
						mvwprintw(gameBoard, i + rowHandle, j + colHandle, "I");
					}
					else {
						mvwprintw(gameBoard, i + rowHandle, j + colHandle, "I");
					}
					wattroff(gameBoard, COLOR_PAIR(4));
					break;
				case GOAL:
					wattron(gameBoard, COLOR_PAIR(5));
					if (j % 2 == 0) {
						mvwprintw(gameBoard, i + rowHandle, j + colHandle, ">");
					}
					else
					{
						mvwprintw(gameBoard, i + rowHandle, j + colHandle, "<");
					}
					wattroff(gameBoard, COLOR_PAIR(5));
					break;
				case BOUND:mvwprintw(gameBoard, i + rowHandle, j + colHandle, " ");
					break;
				case PLAYER:
					wattron(gameBoard, COLOR_PAIR(6));
					if (j % 2 == 0) {
						mvwprintw(gameBoard, i + rowHandle, j + colHandle, "'");
					}
					else
					{
						mvwprintw(gameBoard, i + rowHandle, j + colHandle, "'");
					}
					wattroff(gameBoard, COLOR_PAIR(6));
					break;
				}
			}
		}
		wrefresh(gameBoard);
		PushBox->setMap(Coordinates(uy, ux), temp);
		return;
	};
	void renderAll(WINDOW* levelBoard, WINDOW* stepBoard, WINDOW* pushBoard, WINDOW* resetBoard, WINDOW* gameBoard) {
		renderLevelBoard(levelBoard);
		renderStepBoard(stepBoard);
		renderPushBoard(pushBoard);
		renderTimeBoard(resetBoard);
		renderGameBoard(gameBoard);
	}
	void renderInit(WINDOW* levelBoard, WINDOW* stepBoard, WINDOW* pushBoard, WINDOW* resetBoard) {
		mvwprintw(levelBoard, 1, 8, "   ");
		mvwprintw(stepBoard, 1, 8, "   ");
		mvwprintw(pushBoard, 1, 8, "   ");
		mvwprintw(resetBoard, 1, 8, "   ");
	}
	void renderResult() {
		attron(COLOR_PAIR(8));
		mvprintw(2, 27, "S C O R E");
		attroff(COLOR_PAIR(8));
		int score = 1000000, step, push, reset;
		for (int i = 0; i < PushBox->getRecords().size(); i++) {
			step = PushBox->getRecords()[i][0];
			push = PushBox->getRecords()[i][1];
			reset = PushBox->getRecords()[i][2];
			score -= step * 649 + push * 2646 + reset * 47332;
			mvprintw(5 + i * 2, 9, "Level %d", i + 1);
			mvprintw(5 + i * 2, 24, "Step %d", step);
			mvprintw(5 + i * 2, 34, "Push %d", push);
			mvprintw(5 + i * 2, 44, "Reset %d", reset);
		}
		if (score < 0) score = 0;
		attron(COLOR_PAIR(2));
		mvprintw(18, 0, "                                                                 ", score);
		mvprintw(19, 0, "                      Total Score: %d                             ", score);
		mvprintw(20, 0, "                                                                 ", score);
		attroff(COLOR_PAIR(2));
		mvprintw(22, 18, "Press \'n\' to start new game");
		mvprintw(23, 18, "Press \'q\' to quit the game");
	}
private:
	PushBox* PushBox;
};

#endif