#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <new.h>
#include "VSPDE.h"
#include "Arduino.h"
#include <stdlib.h> // for malloc and free
#include <math.h>
#include "Graphics.h"
#include "Cube.h"
#include "Paddle.h"
#include "PointList.h"
#include "Snake.h"
#include "Pong.h"
#include "Breakout.h"
#include "Pattern.h"
/*
	Cube makes the assumption that the size doesn't change (copy and assignment would crash otherwise)

*/

class MenuScreen {
        int counter;
        int countdown;
        int timetoScroll;
	int currentSelection;
        int patternNumber;
        int size;
	bool inMenu;
	int minSelection;
	int maxSelection; 
	Snake* snake;
	Pong* pong;
	Breakout* breakout;
        Pattern* pattern;
        Cube* cube;
	Cube* Blocks;
	public:
	MenuScreen(Cube* c, int size); //size of cube;
	void Joystick(int x, int y);
	void Reset();
	void Draw();
	void CreateGame();
	void GameOver();
};

#endif
