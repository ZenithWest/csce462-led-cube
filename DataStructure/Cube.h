#ifndef CUBE_H
#define CUBE_H

#include "Arduino.h"
#include <stdlib.h> // for malloc and free
#include "VSPDE.h"
#include "Graphics.h"
#include <math.h>

struct Graphics;
struct Point;


struct Cube {
	int dimX;
	int dimY;
	int dimZ;
	int size;
	int sizeXY;
	bool* data;

	Cube(int x, int y, int z);
  
	bool get(int x, int y, int z);	// Returns true if LED on, false otherwise
	void set(int x, int y, int z, bool value);
	void setHIGH(int x, int y, int z);	// Turns LED on
	void setLOW(int x, int y, int z);	// Turns LED off
	bool flip(int x, int y, int z);	// Flips and returns new value

	
	bool get(Point p);
	void set(Point p, bool value);
	void setHIGH(Point p);
	void setLOW(Point p);
	bool flip(Point p);
	void clear();

	// Graphics
	void drawLine(double x1, double y1, double z1, double x2, double y2, double z2);
	void drawSquare(double x1, double y1, double z1, double x2, double y2, double z2);
	void drawCircle(double x, double y, double z, double radius, double angle);

	void drawLine(Point p1, Point p2);
	void drawSquare(Point p1, Point p2);
	void drawCircle(Point p1, double radius, double angle);

	void drawLine(Line line);
	void drawSquare(Square);
	void drawCircle(Circle circle);

	void rotateXAxis(double deg);
	void rotateYAxis(double deg);
	void rotateZAxis(double deg);
	void rotateYXZ(double degY, double degX, double degZ);
	void translate(double x, double y, double z);
};

#endif
