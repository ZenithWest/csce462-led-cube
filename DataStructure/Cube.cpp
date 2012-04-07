#include <stdlib.h> // for malloc and free
#include "Cube.h"
/*
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
*/
Cube::Cube(int x, int y, int z) {
	dimX = x;
	dimY = y;
	dimZ = z;
	
	sizeXZ = dimX*dimZ;
	sizeXY = dimX*dimY;
	sizeYZ = dimY*dimZ;
	size = sizeXY*dimZ;

	// Initialize 3-dimensional data as contiguous array
	data1D = (bool*)malloc(size*sizeof(bool)); //data1D = new bool[size];

	// Initialize 3-dimensional data pointers (for faster access)
	data3D = (bool***)malloc(x*sizeof(bool**)); //data3D = new bool**[x];
	for(int i=0; i<x; i++) {
		data3D[i] = (bool**)malloc(y*sizeof(bool*)); // data3D[i] = new bool*[y];
		for(int j=0; j<y; j++) {
			data3D[i][j] = data1D + (i*sizeYZ) + (j*z);
		}
	}
}

Cube::~Cube() {
	free(data1D);
	for(int i=0; i<dimX; ++i) {
		free(data3D[i]);
	}
	free(data3D);
}

// Returns true if LED on, false otherwise
bool Cube::get(int x, int y, int z) {
	return data3D[x][y][z];
}

void Cube::set(int x, int y, int z, bool value) {
	data3D[x][y][z] = value;
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
	if (validPoint(p)) {
		return get(round(p.x), round(p.y), round(p.z));
	}
	return false;
}

void Cube::set(Point p, bool value) {
	if (validPoint(p)) {
		set(round(p.x), round(p.y), round(p.z), value);
	}
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
	memset(data1D, 0, size*sizeof(bool));
}

bool Cube::copy(Cube* dest, Cube* src) {
	if (dest->dimX == src->dimX) {
		if (dest->dimY == src->dimY) {
			if (dest->dimZ == src->dimZ) {
				memcpy(dest->data1D, src->data1D, src->size*sizeof(bool));
				return true;
			}
		}
	}
	return false;
}

bool Cube::copyFrom(Cube* src) {
	return copy(this, src);
}

bool Cube::copyTo(Cube* dest) {
	return Cube::copy(dest, this);
}


void Cube::sendData() {
	Serial.write((uint8_t*)data1D, size*sizeof(bool));
}

void Cube::receiveData() {
	int i = 0;
	while (Serial.available() > 0) {
		data1D[i] = Serial.read();
		++i;
	}
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

void Cube::rotateXAxis(Point p, double deg) {
	Cube* cube = new Cube(dimX, dimY, dimZ);
	memcpy(cube->data1D, data1D, size*sizeof(bool));
	clear();
	double rad = PI*deg/180.0;
	for (int x=0; x<dimX; ++x) {
		for (int y=0; y<dimY; ++y) {
			for (int z=0; x<dimZ; ++z) {
				if (cube->get(x, y, z)) {
					setHIGH(Graphics().rotateXAxis(Point(x,y,z)-p, rad)+p);
				}
			}
		}
	}

	delete cube;
}

void Cube::rotateYAxis(Point p, double deg) {
	Cube* cube = new Cube(dimX, dimY, dimZ);
	
	memcpy(cube->data1D, data1D, size*sizeof(bool));
	clear();
	
	double rad = PI*deg/180.0;
	
	for (int x=0; x<dimX; ++x) {
		for (int y=0; y<dimY; ++y) {
			for (int z=0; x<dimZ; ++z) {
				if (cube->get(x, y, z)) {
					setHIGH(Graphics().rotateYAxis(Point(x,y,z)-p, rad)+p);
				}
			}
		}
	}

	delete cube;
}

void Cube::rotateZAxis(Point p, double deg) {
	Cube* cube = new Cube(dimX, dimY, dimZ);
	
	cube->copy(cube, this);
	clear();
	
	double rad = PI*deg/180.0;
	
	for (int x=0; x<dimX; ++x) {
		for (int y=0; y<dimY; ++y) {
			for (int z=0; x<dimZ; ++z) {
				if (cube->get(x, y, z)) {
					setHIGH(Graphics().rotateZAxis(Point(x,y,z)-p, rad)+p);
				}
			}
		}
	}

	delete cube;
}

void Cube::rotateYXZ(Point p, double degY, double degX, double degZ) {
	Cube* cube = new Cube(dimX, dimY, dimZ);
	
	cube->copy(cube, this);
	clear();
	
	double radY = PI*degY/180.0;
	double radX = PI*degX/180.0;
	double radZ = PI*degZ/180.0;
	
	for (double x=0; x<dimX; ++x) {
		for (double y=0; y<dimY; ++y) {
			for (double z=0; x<dimZ; ++z) {
				if (cube->get(x, y, z)) {
					setHIGH(Graphics().rotateYXZ(Point(x,y,z)-p, radY, radX, radZ)+p);
				}
			}
		}
	}

	delete cube;
}

void Cube::translate(double x, double y, double z) {

}

bool Cube::validPoint(double x, double y, double z) {
	if (x < dimX + 0.5) {
		if (y < dimY + 0.5) {
			if (z < dimZ + 0.5) {
				if (x > -0.5) {
					if (y > -0.5) {
						if (z > -0.5) {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool Cube::validPoint(Point p) {
	return validPoint(p.x, p.y, p.z);
}
