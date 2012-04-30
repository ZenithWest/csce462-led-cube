#ifndef SNAKE_H
#define SNAKE_H

#include <new.h>
#include "VSPDE.h"
#include "Arduino.h"
#include <stdlib.h> // for malloc and free
#include <math.h>
#include "Graphics.h"
#include "Cube.h"
/*
	Cube makes the assumption that the size doesn't change (copy and assignment would crash otherwise)

*/

/*
class Snake {
	Point* apple;
	Cube* cube;
	vector<Point*> snake;
	int size;
	bool grow;
	Snake(int size);
	void Reset();
	Point* SpawnApple();
	void EatApple();
	void Draw();
	void Move(int x, int y, int z);
	void Move();
	bool CheckIfInsidePlayer(Point* p);
	void GameOver();
};
*/
#endif
