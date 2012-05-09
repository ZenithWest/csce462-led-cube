#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <new.h>
#include "VSPDE.h"
#include "Arduino.h"
#include <stdlib.h> // for malloc and free
#include <math.h>
#include "Graphics.h"
#include "Cube.h"
#include "Paddle.h"
#include "PointList.h"
/*
	Cube makes the assumption that the size doesn't change (copy and assignment would crash otherwise)

*/




class Ball{
public:
Ball(){Position = new PointList(0,0,0); Direction = new PointList(0,0,0);speed = 50;}
PointList* Position;
PointList* Direction;
int speed;
};

class Breakout {
	int size;
	Paddle* p1;
	Ball* ball;
    Cube* cube;
	Cube* Blocks;
    bool gameover;
	public:
	Breakout(Cube* cube, int Size, int paddlesize); //size of cube;
	void Reset();
	void MoveBall();
	void MovePaddle(Paddle* p, int x, int z); //x,z -1 or 0 or 1 ... direction
	void MovePaddle1(int x, int y); // x y of joystick 1..1023
	void Draw();
	void GameOver();
};

#endif
