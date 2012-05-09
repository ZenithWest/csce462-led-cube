#ifndef PADDLE_H
#define PADDLE_H
#include "Cube.h"
#include "Pointlist.h"
class Paddle{
public:
Paddle(int Size){Position = new PointList(0,0,0); size = Size; speed = 50;}
PointList* Position;
int size;
int speed;
};

#endif
