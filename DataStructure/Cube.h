#ifndef CUBE_H
#define CUBE_H

#include <new.h>
#include "VSPDE.h"
#include "Arduino.h"
#include <stdlib.h> // for malloc and free
#include "Graphics.h"
#include <math.h>

struct Graphics;
struct Point;

/*
	Cube makes the assumption that the size doesn't change (copy and assignment would crash otherwise)

*/


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

	void initializeSize(int x, int y, int z);
	void initializeData1D();
	void initializeData3D();
	void deallocateMemory();

	Cube(int x, int y, int z);
	Cube(const Cube& c);
	~Cube();

	Cube& operator=(const Cube& rhs);
  
	bool get(int x, int y, int z);	// Returns true if LED on, false otherwise
	bool get(int x, int y, int z) const;
	void set(int x, int y, int z, bool value);
	void setHIGH(int x, int y, int z);	// Turns LED on
	void setLOW(int x, int y, int z);	// Turns LED off
	bool flip(int x, int y, int z);	// Flips and returns new value

	
	bool get(Point p);
	bool get(Point p) const;
	void set(Point p, bool value);
	void setHIGH(Point p);
	void setLOW(Point p);
	bool flip(Point p);


	void clear();


	Cube* copy(); // Creates a new cube from this and returns pointer to new cube
	Cube& copy(Cube& dest, const Cube& src); // Copies data from src to dest and returns reference to dest
	Cube* copy(Cube* dest, Cube* src); // Copies data from src to dest and returns pointer to dest
	Cube* copy(Cube* src); // Copies data from src to this and returns pointer to this
	Cube& copy(const Cube& src); // Copies data from src to this and returns reference to this


	Cube* combine(Cube* cube);
	Cube& combine(const Cube& cube);


	void sendData();
	void receiveData();
	void BW_WritePins();
	void BW_ReceiveData();


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
	bool validPoint(double x, double y, double z) const;
	bool validPoint(Point p);
	bool validPoint(Point p) const;
};

#endif
