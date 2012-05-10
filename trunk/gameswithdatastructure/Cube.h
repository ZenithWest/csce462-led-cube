#ifndef CUBE_H
#define CUBE_H

#include <new.h>
#include "VSPDE.h"
#include "Arduino.h"
#include <stdlib.h> // for malloc and free
#include "Graphics.h"

struct Graphics;
struct Point;

/*
	Cube makes the assumption that the size doesn't change (copy and assignment would crash otherwise)

*/

#define HEADER_BUFFER 'B'


struct Cube {
	int dimX;
	int dimY;
	int dimZ;
	
	int size;
	int sizeXZ;
	int sizeXY;
	int sizeYZ;
	int sizeXYZ; // same as size
	
	int* pinBaseList1D;
	int** pinBaseList2D;
	int pinBaseCount;
	int pinBaseSize;
	
	int* pinLayerList;
	int pinLayerCount;
	
	Point center;

	bool* data1D;
	bool*** data3D;
	char* buffer; // To store a compact version of data1D for transmission
	short bufferSize;

	void initializeSize(int x, int y, int z);
	void initializeData1D();
	void initializeData3D();
	void initializeBuffer();
	void initializePinBaseList(int* pins, int num);
	void initializePinLayerList(int* pins, int num);
	void deallocateMemory();

	Cube(int x, int y, int z);
	Cube(const Cube& c);
	~Cube();

	Cube& operator=(const Cube& rhs);
  

	bool get(int x, int y, int z);	// Returns true if LED on, false otherwise
	bool get(int x, int y, int z) const;
	void set(int x, int y, int z, bool value=true);
	void setHIGH(int x, int y, int z);	// Turns LED on
	void setLOW(int x, int y, int z);	// Turns LED off
	bool flip(int x, int y, int z);	// Flips and returns new value
		
	bool get(Point p);
	bool get(Point p) const;
	void set(Point p, bool value=true);
	void setHIGH(Point p);
	void setLOW(Point p);
	bool flip(Point p);
	
	void setLayer(int layer, bool value=true);
	void setColumn(int columnX, int columnY, bool value=true);
	void setPin(int pin, bool value=true);
	void flipPin(int pin);

	void clear();
	void setAll();

	Cube* copy(); // Creates a new cube from this and returns pointer to new cube
	Cube& copy(Cube& dest, const Cube& src); // Copies data from src to dest and returns reference to dest
	Cube* copy(Cube* dest, Cube* src); // Copies data from src to dest and returns pointer to dest
	Cube* copy(Cube* src); // Copies data from src to this and returns pointer to this
	Cube& copy(const Cube& src); // Copies data from src to this and returns reference to this


	Cube* combine(Cube* cube);
	Cube& combine(const Cube& cube);

	
	void compactBuffer();
	void sendData();
	void receiveData();
	void BW_WritePins();
	void BW_ReceiveData();
        void decoder(int z);


	bool validPoint(double x, double y, double z);
	bool validPoint(double x, double y, double z) const;
	bool validPoint(Point p);
	bool validPoint(Point p) const;

	// simple translation in direction (neg, none, pos) directions.
	void translate(int dirX, int dirY, int dirZ);
	

	Point pinNum2Point(int num);
};

#endif
