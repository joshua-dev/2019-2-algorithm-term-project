#include <ncurses.h>
#include <clocale>
#include "Map.cpp"

using namespace std;

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "");

	/*
	0 : Null space
	1 : Wall
	2 : Box
	3 : Destination
	4 : Outside
	5 : Character
	6 : Box on destination
	*/

	int mapOne[10][10] = {
		{4, 4, 1, 1, 1, 1, 4, 4, 4, 4},
		{4, 4, 1, 3, 0, 1, 1, 4, 4, 4},
		{4, 4, 1, 3, 0, 0, 1, 4, 4, 4},
		{4, 4, 1, 3, 0, 0, 1, 4, 4, 4},
		{4, 4, 1, 1, 0, 0, 1, 1, 1, 4},
		{4, 4, 4, 1, 0, 0, 0, 0, 1, 4},
		{4, 4, 4, 1, 0, 0, 0, 0, 1, 4},
		{4, 4, 4, 1, 0, 0, 1, 1, 1, 4},
		{4, 4, 4, 1, 1, 1, 1, 4, 4, 4},
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4}};

	int mapTwo[10][10] = {
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
		{4, 4, 1, 1, 1, 1, 1, 4, 4, 4},
		{4, 4, 1, 0, 0, 0, 1, 4, 4, 4},
		{4, 4, 1, 3, 3, 3, 1, 4, 4, 4},
		{4, 4, 1, 0, 0, 0, 1, 1, 4, 4},
		{4, 4, 1, 0, 0, 0, 0, 1, 4, 4},
		{4, 4, 1, 0, 0, 0, 0, 1, 4, 4},
		{4, 4, 1, 1, 1, 1, 1, 1, 4, 4},
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4}};

	int mapThree[10][10] = {
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
		{4, 1, 1, 1, 1, 1, 1, 1, 1, 4},
		{4, 1, 3, 0, 0, 0, 0, 0, 1, 4},
		{4, 1, 0, 3, 0, 0, 0, 0, 1, 4},
		{4, 1, 3, 0, 0, 0, 0, 0, 1, 4},
		{4, 1, 1, 1, 1, 1, 0, 0, 1, 4},
		{4, 4, 4, 4, 4, 1, 1, 1, 1, 4},
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4}};

	Map map1(mapOne);
	Map map2(mapTwo);
	Map map3(mapThree);

	WINDOW *win1; // Map1
	WINDOW *win2; // Map2
	WINDOW *win3; // Map3
	WINDOW *win4; // step 횟수
	WINDOW *win5; // push 횟수
	WINDOW *win6; // end

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
	mvprintw(1, 9, "             Level 1           ");
	mvprintw(2, 1, "------------------------------------------------");

	win1 = newwin(12, 12, 16, 19);
	wbkgd(win1, COLOR_PAIR(10));
	wattron(win1, COLOR_PAIR(10));
	;
	wborder(win1, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

	wrefresh(win1); // 화면 업데이트. win1 화면 실제 출력

	// 박스랑 캐릭터 초기 위치 설정
	map1.setElement(3, 5, 2);
	map1.setElement(4, 4, 2);
	map1.setElement(5, 5, 2);
	map1.setCharacter(2, 4);

	// 처음 맵 출력
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map1.map[i][j] == 0)
			{
				attron(COLOR_PAIR(0));
				mvprintw(17 + i, 20 + j, " ");
				attroff(COLOR_PAIR(0));
			}
			else if (map1.map[i][j] == 1)
			{
				attron(COLOR_PAIR(1));
				mvprintw(17 + i, 20 + j, " ");
				attroff(COLOR_PAIR(1));
			}
			else if (map1.map[i][j] == 2)
			{
				attron(COLOR_PAIR(2));
				mvprintw(17 + i, 20 + j, "\u2752");
				attroff(COLOR_PAIR(2));
			}
			else if (map1.map[i][j] == 3)
			{
				attron(COLOR_PAIR(3));
				mvprintw(17 + i, 20 + j, "\u2B1A");
				attroff(COLOR_PAIR(3));
			}
			else if (map1.map[i][j] == 4)
			{
				attron(COLOR_PAIR(4));
				mvprintw(17 + i, 20 + j, " ");
				attroff(COLOR_PAIR(4));
			}
			else if (map1.map[i][j] == 5)
			{
				attron(COLOR_PAIR(4));
				mvprintw(17 + i, 20 + j, "C");
				attroff(COLOR_PAIR(4));
			}
			else if (map1.map[i][j] == 6)
			{
				attron(COLOR_PAIR(5));
				mvprintw(17 + i, 20 + j, "\u2752");
				attroff(COLOR_PAIR(5));
			}
		}
	}

	win4 = newwin(5, 14, 7, 9);
	wbkgd(win4, COLOR_PAIR(3));
	wattron(win4, COLOR_PAIR(3));
	//mvwprintw(win4, 9, 11, "STEP : &d", map1.numStep);
	mvprintw(9, 12, "Step : %d", map1.numStep);
	wborder(win4, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(win4); // 화면 업데이트. win4 화면 실제 출력

	win5 = newwin(5, 14, 7, 27);
	wbkgd(win5, COLOR_PAIR(3));
	wattron(win5, COLOR_PAIR(3));
	mvprintw(9, 30, "PUSH : %d", map1.numPush);
	wborder(win5, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(win5); // 화면 업데이트. win5 화면 실제 출력

	refresh();

	curs_set(0);
	int ch;

	while (map1.numDest != map1.numBoxOnDest)
	{
		keypad(stdscr, true);
		//PrintMap();
		ch = getch();
		if (ch == KEY_UP)
		{
			map1.move(72); // 위
			// 바뀔 때마다 맵 출력
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (map1.map[i][j] == 0)
					{
						attron(COLOR_PAIR(0));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(0));
					}
					else if (map1.map[i][j] == 1)
					{
						attron(COLOR_PAIR(1));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(1));
					}
					else if (map1.map[i][j] == 2)
					{
						attron(COLOR_PAIR(2));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(2));
					}
					else if (map1.map[i][j] == 3)
					{
						attron(COLOR_PAIR(3));
						mvprintw(17 + i, 20 + j, "\u2B1A");
						attroff(COLOR_PAIR(3));
					}
					else if (map1.map[i][j] == 4)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(4));
					}
					else if (map1.map[i][j] == 5)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, "C");
						attroff(COLOR_PAIR(4));
					}
					else if (map1.map[i][j] == 6)
					{
						attron(COLOR_PAIR(5));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(5));
					}
				}
			}
			mvprintw(9, 12, "Step : %d", map1.numStep);
			mvprintw(9, 30, "PUSH : %d", map1.numPush);
		}
		else if (ch == KEY_LEFT)
		{
			map1.move(75); // 왼쪽
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (map1.map[i][j] == 0)
					{
						attron(COLOR_PAIR(0));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(0));
					}
					else if (map1.map[i][j] == 1)
					{
						attron(COLOR_PAIR(1));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(1));
					}
					else if (map1.map[i][j] == 2)
					{
						attron(COLOR_PAIR(2));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(2));
					}
					else if (map1.map[i][j] == 3)
					{
						attron(COLOR_PAIR(3));
						mvprintw(17 + i, 20 + j, "\u2B1A");
						attroff(COLOR_PAIR(3));
					}
					else if (map1.map[i][j] == 4)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(4));
					}
					else if (map1.map[i][j] == 5)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, "C");
						attroff(COLOR_PAIR(4));
					}
					else if (map1.map[i][j] == 6)
					{
						attron(COLOR_PAIR(5));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(5));
					}
				}
			}
			mvprintw(9, 12, "Step : %d", map1.numStep);
			mvprintw(9, 30, "PUSH : %d", map1.numPush);
		}
		else if (ch == KEY_RIGHT)
		{
			map1.move(77); // 오른쪽
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (map1.map[i][j] == 0)
					{
						attron(COLOR_PAIR(0));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(0));
					}
					else if (map1.map[i][j] == 1)
					{
						attron(COLOR_PAIR(1));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(1));
					}
					else if (map1.map[i][j] == 2)
					{
						attron(COLOR_PAIR(2));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(2));
					}
					else if (map1.map[i][j] == 3)
					{
						attron(COLOR_PAIR(3));
						mvprintw(17 + i, 20 + j, "\u2B1A");
						attroff(COLOR_PAIR(3));
					}
					else if (map1.map[i][j] == 4)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(4));
					}
					else if (map1.map[i][j] == 5)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, "C");
						attroff(COLOR_PAIR(4));
					}
					else if (map1.map[i][j] == 6)
					{
						attron(COLOR_PAIR(5));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(5));
					}
				}
			}
			mvprintw(9, 12, "Step : %d", map1.numStep);
			mvprintw(9, 30, "PUSH : %d", map1.numPush);
		}
		else if (ch == KEY_DOWN)
		{
			map1.move(80); // 아래
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (map1.map[i][j] == 0)
					{
						attron(COLOR_PAIR(0));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(0));
					}
					else if (map1.map[i][j] == 1)
					{
						attron(COLOR_PAIR(1));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(1));
					}
					else if (map1.map[i][j] == 2)
					{
						attron(COLOR_PAIR(2));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(2));
					}
					else if (map1.map[i][j] == 3)
					{
						attron(COLOR_PAIR(3));
						mvprintw(17 + i, 20 + j, "\u2B1A");
						attroff(COLOR_PAIR(3));
					}
					else if (map1.map[i][j] == 4)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(4));
					}
					else if (map1.map[i][j] == 5)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, "C");
						attroff(COLOR_PAIR(4));
					}
					else if (map1.map[i][j] == 6)
					{
						attron(COLOR_PAIR(5));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(5));
					}
				}
			}
		}
		mvprintw(9, 12, "Step : %d", map1.numStep);
		mvprintw(9, 30, "PUSH : %d", map1.numPush);
	}

	//두번째맵
	getch();
	mvprintw(1, 10, "             Level 2           ");
	mvprintw(2, 1, "------------------------------------------------");

	win2 = newwin(12, 12, 16, 19);
	wbkgd(win2, COLOR_PAIR(10));
	wattron(win2, COLOR_PAIR(10));
	wborder(win2, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(win2); // 화면 업데이트. win2 화면 실제 출력

	// 박스랑 캐릭터 초기 위치 설정
	map2.setElement(4, 3, 2);
	map2.setElement(4, 4, 2);
	map2.setElement(4, 5, 2);
	map2.setCharacter(6, 4);
	map2.numStep = 0;
	map2.numPush = 0;
	mvprintw(9, 12, "Step : %d ", map2.numStep);
	mvprintw(9, 30, "PUSH : %d ", map2.numPush);
	// 처음 맵 출력
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map2.map[i][j] == 0)
			{
				attron(COLOR_PAIR(0));
				mvprintw(17 + i, 20 + j, " ");
				attroff(COLOR_PAIR(0));
			}
			else if (map2.map[i][j] == 1)
			{
				attron(COLOR_PAIR(1));
				mvprintw(17 + i, 20 + j, " ");
				attroff(COLOR_PAIR(1));
			}
			else if (map2.map[i][j] == 2)
			{
				attron(COLOR_PAIR(2));
				mvprintw(17 + i, 20 + j, "\u2752");
				attroff(COLOR_PAIR(2));
			}
			else if (map2.map[i][j] == 3)
			{
				attron(COLOR_PAIR(3));
				mvprintw(17 + i, 20 + j, "\u2B1A");
				attroff(COLOR_PAIR(3));
			}
			else if (map2.map[i][j] == 4)
			{
				attron(COLOR_PAIR(4));
				mvprintw(17 + i, 20 + j, " ");
				attroff(COLOR_PAIR(4));
			}
			else if (map2.map[i][j] == 5)
			{
				attron(COLOR_PAIR(4));
				mvprintw(17 + i, 20 + j, "C");
				attroff(COLOR_PAIR(4));
			}
			else if (map2.map[i][j] == 6)
			{
				attron(COLOR_PAIR(5));
				mvprintw(17 + i, 20 + j, "\u2752");
				attroff(COLOR_PAIR(5));
			}
		}
	}

	refresh();
	curs_set(0);
	int ch2;
	while (map2.numDest != map2.numBoxOnDest)
	{
		keypad(stdscr, true);
		//PrintMap();
		ch2 = getch();
		if (ch2 == KEY_UP)
		{
			map2.move(72); // 위
			// 바뀔 때마다 맵 출력
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (map2.map[i][j] == 0)
					{
						attron(COLOR_PAIR(0));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(0));
					}
					else if (map2.map[i][j] == 1)
					{
						attron(COLOR_PAIR(1));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(1));
					}
					else if (map2.map[i][j] == 2)
					{
						attron(COLOR_PAIR(2));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(2));
					}
					else if (map2.map[i][j] == 3)
					{
						attron(COLOR_PAIR(3));
						mvprintw(17 + i, 20 + j, "\u2B1A");
						attroff(COLOR_PAIR(3));
					}
					else if (map2.map[i][j] == 4)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(4));
					}
					else if (map2.map[i][j] == 5)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, "C");
						attroff(COLOR_PAIR(4));
					}
					else if (map2.map[i][j] == 6)
					{
						attron(COLOR_PAIR(5));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(5));
					}
				}
			}
			mvprintw(9, 12, "Step : %d ", map2.numStep);
			mvprintw(9, 30, "PUSH : %d ", map2.numPush);
		}
		else if (ch2 == KEY_LEFT)
		{
			map2.move(75); // 왼쪽
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (map2.map[i][j] == 0)
					{
						attron(COLOR_PAIR(0));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(0));
					}
					else if (map2.map[i][j] == 1)
					{
						attron(COLOR_PAIR(1));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(1));
					}
					else if (map2.map[i][j] == 2)
					{
						attron(COLOR_PAIR(2));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(2));
					}
					else if (map2.map[i][j] == 3)
					{
						attron(COLOR_PAIR(3));
						mvprintw(17 + i, 20 + j, "\u2B1A");
						attroff(COLOR_PAIR(3));
					}
					else if (map2.map[i][j] == 4)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(4));
					}
					else if (map2.map[i][j] == 5)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, "C");
						attroff(COLOR_PAIR(4));
					}
					else if (map2.map[i][j] == 6)
					{
						attron(COLOR_PAIR(5));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(5));
					}
				}
			}
			mvprintw(9, 12, "Step : %d ", map2.numStep);
			mvprintw(9, 30, "PUSH : %d ", map2.numPush);
		}
		else if (ch2 == KEY_RIGHT)
		{
			map2.move(77); // 오른쪽
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (map2.map[i][j] == 0)
					{
						attron(COLOR_PAIR(0));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(0));
					}
					else if (map2.map[i][j] == 1)
					{
						attron(COLOR_PAIR(1));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(1));
					}
					else if (map2.map[i][j] == 2)
					{
						attron(COLOR_PAIR(2));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(2));
					}
					else if (map2.map[i][j] == 3)
					{
						attron(COLOR_PAIR(3));
						mvprintw(17 + i, 20 + j, "\u2B1A");
						attroff(COLOR_PAIR(3));
					}
					else if (map2.map[i][j] == 4)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(4));
					}
					else if (map2.map[i][j] == 5)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, "C");
						attroff(COLOR_PAIR(4));
					}
					else if (map2.map[i][j] == 6)
					{
						attron(COLOR_PAIR(5));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(5));
					}
				}
			}
			mvprintw(9, 12, "Step : %d ", map2.numStep);
			mvprintw(9, 30, "PUSH : %d ", map2.numPush);
		}
		else if (ch2 == KEY_DOWN)
		{
			map2.move(80); // 아래
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (map2.map[i][j] == 0)
					{
						attron(COLOR_PAIR(0));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(0));
					}
					else if (map2.map[i][j] == 1)
					{
						attron(COLOR_PAIR(1));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(1));
					}
					else if (map2.map[i][j] == 2)
					{
						attron(COLOR_PAIR(2));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(2));
					}
					else if (map2.map[i][j] == 3)
					{
						attron(COLOR_PAIR(3));
						mvprintw(17 + i, 20 + j, "\u2B1A");
						attroff(COLOR_PAIR(3));
					}
					else if (map2.map[i][j] == 4)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(4));
					}
					else if (map2.map[i][j] == 5)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, "C");
						attroff(COLOR_PAIR(4));
					}
					else if (map2.map[i][j] == 6)
					{
						attron(COLOR_PAIR(5));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(5));
					}
				}
			}
			mvprintw(9, 12, "Step : %d ", map2.numStep);
			mvprintw(9, 30, "PUSH : %d ", map2.numPush);
		}
	}

	//세번째맵
	getch();
	mvprintw(1, 10, "             Level 3           ");
	mvprintw(2, 1, "------------------------------------------------");

	win3 = newwin(12, 12, 16, 19);

	wbkgd(win3, COLOR_PAIR(10));
	wattron(win3, COLOR_PAIR(10));
	wborder(win3, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(win3); // 화면 업데이트. win3 화면 실제 출력

	// 박스랑 캐릭터 초기 위치 설정
	map3.setElement(4, 4, 2);
	map3.setElement(4, 5, 2);
	map3.setElement(4, 6, 2);
	map3.setCharacter(4, 7);
	map3.numStep = 0;
	map3.numPush = 0;
	mvprintw(9, 12, "Step : %d ", map3.numStep);
	mvprintw(9, 30, "PUSH : %d ", map3.numPush);
	// 처음 맵 출력
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map3.map[i][j] == 0)
			{
				attron(COLOR_PAIR(0));
				mvprintw(17 + i, 20 + j, " ");
				attroff(COLOR_PAIR(0));
			}
			else if (map3.map[i][j] == 1)
			{
				attron(COLOR_PAIR(1));
				mvprintw(17 + i, 20 + j, " ");
				attroff(COLOR_PAIR(1));
			}
			else if (map3.map[i][j] == 2)
			{
				attron(COLOR_PAIR(2));
				mvprintw(17 + i, 20 + j, "\u2752");
				attroff(COLOR_PAIR(2));
			}
			else if (map3.map[i][j] == 3)
			{
				attron(COLOR_PAIR(3));
				mvprintw(17 + i, 20 + j, "\u2B1A");
				attroff(COLOR_PAIR(3));
			}
			else if (map3.map[i][j] == 4)
			{
				attron(COLOR_PAIR(4));
				mvprintw(17 + i, 20 + j, " ");
				attroff(COLOR_PAIR(4));
			}
			else if (map3.map[i][j] == 5)
			{
				attron(COLOR_PAIR(4));
				mvprintw(17 + i, 20 + j, "C");
				attroff(COLOR_PAIR(4));
			}
			else if (map3.map[i][j] == 6)
			{
				attron(COLOR_PAIR(5));
				mvprintw(17 + i, 20 + j, "\u2752");
				attroff(COLOR_PAIR(5));
			}
		}
	}

	refresh();
	curs_set(0);
	int ch3;
	while (map3.numDest != map3.numBoxOnDest)
	{
		keypad(stdscr, true);
		//PrintMap();
		ch3 = getch();
		if (ch3 == KEY_UP)
		{
			map3.move(72); // 위
			// 바뀔 때마다 맵 출력
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (map3.map[i][j] == 0)
					{
						attron(COLOR_PAIR(0));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(0));
					}
					else if (map3.map[i][j] == 1)
					{
						attron(COLOR_PAIR(1));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(1));
					}
					else if (map3.map[i][j] == 2)
					{
						attron(COLOR_PAIR(2));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(2));
					}
					else if (map3.map[i][j] == 3)
					{
						attron(COLOR_PAIR(3));
						mvprintw(17 + i, 20 + j, "\u2B1A");
						attroff(COLOR_PAIR(3));
					}
					else if (map3.map[i][j] == 4)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(4));
					}
					else if (map3.map[i][j] == 5)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, "C");
						attroff(COLOR_PAIR(4));
					}
					else if (map3.map[i][j] == 6)
					{
						attron(COLOR_PAIR(5));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(5));
					}
				}
			}
			mvprintw(9, 12, "Step : %d ", map3.numStep);
			mvprintw(9, 30, "PUSH : %d ", map3.numPush);
		}
		else if (ch3 == KEY_LEFT)
		{
			map3.move(75); // 왼쪽
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (map3.map[i][j] == 0)
					{
						attron(COLOR_PAIR(0));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(0));
					}
					else if (map3.map[i][j] == 1)
					{
						attron(COLOR_PAIR(1));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(1));
					}
					else if (map3.map[i][j] == 2)
					{
						attron(COLOR_PAIR(2));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(2));
					}
					else if (map3.map[i][j] == 3)
					{
						attron(COLOR_PAIR(3));
						mvprintw(17 + i, 20 + j, "\u2B1A");
						attroff(COLOR_PAIR(3));
					}
					else if (map3.map[i][j] == 4)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(4));
					}
					else if (map3.map[i][j] == 5)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, "C");
						attroff(COLOR_PAIR(4));
					}
					else if (map3.map[i][j] == 6)
					{
						attron(COLOR_PAIR(5));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(5));
					}
				}
			}
			mvprintw(9, 12, "Step : %d ", map3.numStep);
			mvprintw(9, 30, "PUSH : %d ", map3.numPush);
		}
		else if (ch3 == KEY_RIGHT)
		{
			map3.move(77); // 오른쪽
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (map3.map[i][j] == 0)
					{
						attron(COLOR_PAIR(0));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(0));
					}
					else if (map3.map[i][j] == 1)
					{
						attron(COLOR_PAIR(1));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(1));
					}
					else if (map3.map[i][j] == 2)
					{
						attron(COLOR_PAIR(2));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(2));
					}
					else if (map3.map[i][j] == 3)
					{
						attron(COLOR_PAIR(3));
						mvprintw(17 + i, 20 + j, "\u2B1A");
						attroff(COLOR_PAIR(3));
					}
					else if (map3.map[i][j] == 4)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(4));
					}
					else if (map3.map[i][j] == 5)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, "C");
						attroff(COLOR_PAIR(4));
					}
					else if (map3.map[i][j] == 6)
					{
						attron(COLOR_PAIR(5));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(5));
					}
				}
			}
			mvprintw(9, 12, "Step : %d ", map3.numStep);
			mvprintw(9, 30, "PUSH : %d ", map3.numPush);
		}
		else if (ch3 == KEY_DOWN)
		{
			map3.move(80); // 아래
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (map3.map[i][j] == 0)
					{
						attron(COLOR_PAIR(0));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(0));
					}
					else if (map3.map[i][j] == 1)
					{
						attron(COLOR_PAIR(1));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(1));
					}
					else if (map3.map[i][j] == 2)
					{
						attron(COLOR_PAIR(2));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(2));
					}
					else if (map3.map[i][j] == 3)
					{
						attron(COLOR_PAIR(3));
						mvprintw(17 + i, 20 + j, "\u2B1A");
						attroff(COLOR_PAIR(3));
					}
					else if (map3.map[i][j] == 4)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, " ");
						attroff(COLOR_PAIR(4));
					}
					else if (map3.map[i][j] == 5)
					{
						attron(COLOR_PAIR(4));
						mvprintw(17 + i, 20 + j, "C");
						attroff(COLOR_PAIR(4));
					}
					else if (map3.map[i][j] == 6)
					{
						attron(COLOR_PAIR(5));
						mvprintw(17 + i, 20 + j, "\u2752");
						attroff(COLOR_PAIR(5));
					}
				}
			}
			mvprintw(9, 12, "Step : %d ", map3.numStep);
			mvprintw(9, 30, "PUSH : %d ", map3.numPush);
		}
	}

	getch();
	delwin(win3); // destroy win3
	delwin(win4);
	delwin(win5);

	win6 = newwin(31, 41, 5, 5);
	wbkgd(win6, COLOR_PAIR(10));
	wattron(win6, COLOR_PAIR(3));
	mvwprintw(win6, 15, 17, "SUCCESS!");
	wborder(win6, '@', '@', '@', '@', '@', '@', '@', '@');
	wrefresh(win6);
	getch();
	delwin(win6);

	endwin(); // end ncurses mode

	return 0;
} // main
