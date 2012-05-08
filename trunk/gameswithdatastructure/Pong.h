#ifndef PONG_H
#define PONG_H

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


class Paddle{
public:
Paddle(int Size){Position = new PointList(0,0,0); size = Size; speed = 50;}
PointList* Position;
int size;
int speed;
};

class PongBall{
public:
PongBall(){Position = new PointList(0,0,0); Direction = new PointList(0,0,0);speed = 50;}
PointList* Position;
PointList* Direction;
int speed;
};

class Pong {
	int size;
	Paddle* p1;
	Paddle* p2;
	PongBall* ball;
        Cube* cube;
    bool gameover;
	public:
	Pong(Cube* cube,int Size, int paddlesize); //size of cube;
	void Reset();
	void MoveBall();
	void MovePaddle(Paddle* p, int x, int z); //x,z -1 or 0 or 1 ... direction
	void MovePaddle1(int x, int y); // x y of joystick 1..1023
        void MovePaddle2();
	void Draw();
	void Move(int x, int y, int z);
	void GameOver();
};

#endif
