#ifndef _DEFINITION_H_
#define _DEFINITION_H_

#include <locale.h>

struct Coordinates
{
	int x, y;
	Coordinates()
	{
		this->x = 0;
		this->y = 0;
	}
	Coordinates(int a, int b)
	{
		this->x = a;
		this->y = b;
	}
};

enum
{
	EMPTY = 0,
	WALL,
	BOX,
	GOAL,
	BOUND,
	PLAYER
};

#endif
