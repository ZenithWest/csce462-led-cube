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
	return get((int)p.x, (int)p.y, (int)p.z);
}

void Cube::set(Point p, bool value) {
	set((int)p.x, (int)p.y, (int)p.z, value);
}

void Cube::setHIGH(Point p) {
	set(p, true);
}

void Cube::setLOW(Point p) {
	set(p, false);
}

bool Cube::flip(Point p) {
	return flip(p.x, p.y, p.z);
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
					setHIGH(x, round(y*cos(rad) + z*sin(rad)), round(-y*sin(rad) + z*cos(rad)));
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
					setHIGH(round(x*cos(rad) - z*sin(rad)), y, round(x*sin(rad) + z*cos(rad)));
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
					setHIGH(round(x*cos(rad) - y*sin(rad)), round(x*sin(rad) + y*cos(rad)), z);
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
	for (int x=0; x<dimX; ++x) {
		for (int y=0; y<dimY; ++y) {
			for (int z=0; x<dimZ; ++z) {
				if (cube->get(x, y, z)) {
					double sinXZ = sin(radX) * sin(radZ);
					double sinXcosY = sin(radX) * cos(radZ);
					double xx = cos(radY) * cos(radX) * x + (cos(radY) * sinXcosY + sin(radY) * sin(radZ)) * y + (cos(radY) * sinXZ - sin(radY) * cos(radZ)) * z;
					double yy = -sin(radX) * x + cos(radX) * cos(radZ) * y + cos(radX) * sin(radZ) * z;
					double zz = sin(radY) * cos(radX) * x + (sin(radY) * sinXcosY - cos(radY) * sin(radZ)) * y + (sin(radY) * sinXZ + cos(radY) * cos(radZ)) * z;
					setHIGH(round(xx), round(yy), round(zz));
				}
			}
		}
	}

	delete cube;
}

void Cube::translate(double x, double y, double z) {

}



