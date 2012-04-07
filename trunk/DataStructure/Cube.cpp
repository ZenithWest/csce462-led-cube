#include <stdlib.h> // for malloc and free
#include "Cube.h"

void* operator new(size_t size) { 
  return malloc(size); 
}

void* operator new[](size_t size) { 
  return malloc(size); 
}

void operator delete(void* ptr) { 
  free(ptr); 
}

void operator delete[](void* ptr) { 
  free(ptr); 
} 

Cube::Cube(int x, int y, int z) {
	dimX = x;
	dimY = y;
	dimZ = z;
	sizeXY = dimX*dimY;
	size = sizeXY*dimZ;
	// Initialize 3-dimensional data
	data = new bool[size];

}

// Returns true if LED on, false otherwise
bool Cube::get(int x, int y, int z) {
	return *(data + x + dimX*y + sizeXY*z);
}

void Cube::set(int x, int y, int z, bool value) {
	*(data + x + dimX*y + sizeXY*z) = value;
}

// Turns LED on
void Cube::setHIGH(int x, int y, int z) {
	set(x, y, z, true);
}

// Turns LED off
void Cube::setLOW(int x, int y, int z) {
	set(x, y, z, false);
}

// Flips and returns new value
bool Cube::flip(int x, int y, int z) {
	bool value = get(x, y, z);
	value = !value;
	set(x, y, z, value);

	return value;
}

bool Cube::get(Point p) {
	return get(round(p.x), round(p.y), round(p.z));
}

void Cube::set(Point p, bool value) {
	set(round(p.x), round(p.y), round(p.z), value);
}

void Cube::setHIGH(Point p) {
	set(p, true);
}

void Cube::setLOW(Point p) {
	set(p, false);
}

bool Cube::flip(Point p) {
	return flip(round(p.x), round(p.y), round(p.z));
}

void Cube::clear() {
	memset(data, 0, size*sizeof(bool));
}


// Graphics

void drawLine(double x1, double y1, double z1, double x2, double y2, double z2) {

}

void drawCircle(double x, double y, double z, double radius, double angle) {

}


void Cube::drawLine(Point p1, Point p2) {

}

void Cube::drawCircle(Point p1, double radius, double angle) {

}

void Cube::rotateXAxis(double deg) {
	Cube* cube = new Cube(dimX, dimY, dimZ);
	memcpy(cube->data, data, size*sizeof(bool));
	clear();
	double rad = PI*deg/180.0;
	for (int x=0; x<dimX; ++x) {
		for (int y=0; y<dimY; ++y) {
			for (int z=0; x<dimZ; ++z) {
				if (cube->get(x, y, z)) {
					setHIGH(Graphics.rotateXAxis(Point(x,y,z), rad));
				}
			}
		}
	}

	delete cube;
}

void Cube::rotateYAxis(double deg) {
	Cube* cube = new Cube(dimX, dimY, dimZ);
	memcpy(cube->data, data, size*sizeof(bool));
	clear();
	double rad = PI*deg/180.0;
	for (int x=0; x<dimX; ++x) {
		for (int y=0; y<dimY; ++y) {
			for (int z=0; x<dimZ; ++z) {
				if (cube->get(x, y, z)) {
					setHIGH(Graphics.rotateYAxis(Point(x,y,z), rad));
				}
			}
		}
	}

	delete cube;
}

void Cube::rotateZAxis(double deg) {
	Cube* cube = new Cube(dimX, dimY, dimZ);
	memcpy(cube->data, data, size*sizeof(bool));
	clear();
	double rad = PI*deg/180.0;
	for (int x=0; x<dimX; ++x) {
		for (int y=0; y<dimY; ++y) {
			for (int z=0; x<dimZ; ++z) {
				if (cube->get(x, y, z)) {
					setHIGH(Graphics.rotateZAxis(Point(x,y,z), rad));
				}
			}
		}
	}

	delete cube;
}

void Cube::rotateYXZ(double degY, double degX, double degZ) {
	Cube* cube = new Cube(dimX, dimY, dimZ);
	memcpy(cube->data, data, size*sizeof(bool));
	clear();
	double radY = PI*degY/180.0;
	double radX = PI*degX/180.0;
	double radZ = PI*degZ/180.0;
	for (double x=0; x<dimX; ++x) {
		for (double y=0; y<dimY; ++y) {
			for (double z=0; x<dimZ; ++z) {
				if (cube->get(x, y, z)) {
					setHIGH(Graphics.rotateYXZ(Point(x,y,z), radY, radX, radZ));
				}
			}
		}
	}

	delete cube;
}

void Cube::translate(double x, double y, double z) {

}



