#ifndef CUBE_H
#define CUBE_H

#include <new.h>
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
	int sizeXZ;
	int sizeXY;
	int sizeYZ;
	bool* data1D;
	bool*** data3D;

	Cube(int x, int y, int z);
	~Cube();
  
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
	bool copy(Cube* dest, Cube* src); // Returns true if successful (same size)
	bool copyFrom(Cube* src); // Returns true if successful (same size)
	bool copyTo(Cube* dest); // Returns true if successful (same size)


	void sendData();
	void receiveData();


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

	void rotateXAxis(Point p, double deg);
	void rotateYAxis(Point p, double deg);
	void rotateZAxis(Point p, double deg);
	void rotateYXZ(Point p, double degY, double degX, double degZ);
	void translate(double x, double y, double z);

	bool validPoint(double x, double y, double z);
	bool validPoint(Point p);
};

#endif
