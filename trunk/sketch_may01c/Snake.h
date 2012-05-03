#ifndef SNAKE_H
#define SNAKE_H

#include <new.h>
#include "VSPDE.h"
#include "Arduino.h"
#include <stdlib.h> // for malloc and free
#include <math.h>
#include "Graphics.h"
#include "Cube.h"

#include "PointList.h"
/*
	Cube makes the assumption that the size doesn't change (copy and assignment would crash otherwise)

*/


class Snake {
	PointList* apple;
	Cube* cube;
	PointList* snake;
	int sizee;
	bool grow;
        bool gameover;
	public:
	Snake(int size);
	void Reset();
	PointList* SpawnApple();
	void EatApple();
	void Draw();
	void Move(int x, int y, int z);
	void Move();
	bool CheckIfInsidePlayer(PointList* p);
	void GameOver();
};

#endif
