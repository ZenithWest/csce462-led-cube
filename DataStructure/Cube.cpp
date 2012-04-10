#include <stdlib.h> // for malloc and free
#include "Cube.h"

void Cube::initializeSize(int x, int y, int z) {
	dimX = x;
	dimY = y;
	dimZ = z;
	
	sizeXZ = dimX*dimZ;
	sizeXY = dimX*dimY;
	sizeYZ = dimY*dimZ;
	size = sizeXY*dimZ;
}

// Initialize 3-dimensional data as contiguous array
void Cube::initializeData1D() {
	data1D = (bool*)malloc(size*sizeof(bool)); //data1D = new bool[size];
	clear();
}

// Initialize 3-dimensional data pointers (for faster access)
void Cube::initializeData3D() {
	data3D = (bool***)malloc(dimX*sizeof(bool**)); //data3D = new bool**[x];
	for(int i=0; i<dimX; i++) {
		data3D[i] = (bool**)malloc(dimY*sizeof(bool*)); // data3D[i] = new bool*[y];
		for(int j=0; j<dimY; j++) {
			data3D[i][j] = data1D + (i*sizeYZ) + (j*dimZ);
		}
	}
}

void Cube::deallocateMemory() {
	free(data1D);
	data1D = NULL;
	for(int i=0; i<dimX; ++i) {
		free(data3D[i]);
		data3D[i] = NULL;
	}
	free(data3D);
	data3D = NULL;
}

Cube::Cube(int x, int y, int z) {
	initializeSize(x, y, z);
	initializeData1D();
	initializeData3D();
}

Cube::Cube(const Cube& c) {
	initializeSize(c.dimX, c.dimY, c.dimZ);
	initializeData1D();
	initializeData3D();

	copy(*this, c);
}

Cube::~Cube() {
	deallocateMemory();
}

Cube& Cube::operator=(const Cube& rhs) {
	return copy(rhs);
}

// Returns true if LED on, false otherwise
bool Cube::get(int x, int y, int z) {
	return data3D[x][y][z];
}

bool Cube::get(int x, int y, int z) const {
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

bool Cube::get(Point p) const {
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


/////////// COPY //////////////////

Cube* Cube::copy() {
	Cube* cpyCube = new Cube(dimX, dimY, dimZ);
	return copy(cpyCube, this);
}

Cube& Cube::copy(Cube& dest, const Cube& src) {
	if (dest.dimX == src.dimX) {
		if (dest.dimY == src.dimY) {
			if (dest.dimZ == src.dimZ) {
				memcpy(dest.data1D, src.data1D, src.size*sizeof(bool));
			}
		}
	}
	return dest;
}

Cube* Cube::copy(Cube* dest, Cube* src) {
	return &copy(*dest, *src);
}

Cube* Cube::copy(Cube* src) {
	return copy(this, src);
}

Cube& Cube::copy(const Cube& src) {
	return copy(*this, src);
}


/////////// COMBINE ///////////////////

Cube* Cube::combine(Cube* cube) {
	return &combine(*cube);
}

Cube& Cube::combine(const Cube& cube) {
	for (int x=0; x<dimX; ++x) {
		for (int y=0; y<dimY; ++y) {
			for (int z=0; x<dimZ; ++z) {
				if (cube.get(x, y, z)) {
					setHIGH(x, y, z);
				}
			}
		}
	}
}



void Cube::sendData() {
	Serial.write((uint8_t*)data1D, size*sizeof(bool));
}

void Cube::receiveData() {
	int i = 0;
	Serial.readBytes((char*)data1D, size*sizeof(bool));
}

void Cube::BW_ReceiveData() {
	delay(1);
	if (Serial.available()) {
		int led;
		led = Serial.read() - '0';
		if (Serial.available()) {
			led *= 10;
			led += Serial.read() - '0';
		}

		flip(0, led % 5, led / 5);
	}
	
}

// My test code (Cube(1,5,3) what xyz means might change we need to decide on what is what)
void Cube::BW_WritePins() {
	
	digitalWrite(26, HIGH);
	digitalWrite(22, LOW);
	digitalWrite(41, data3D[0][4][0]);
	digitalWrite(43, data3D[0][3][0]);
	digitalWrite(45, data3D[0][2][0]);
	digitalWrite(47, data3D[0][1][0]);
	digitalWrite(49, data3D[0][0][0]);
	delay(10);
	//delayMicroseconds(1);
	
	digitalWrite(22, HIGH);
	digitalWrite(24, LOW);
	digitalWrite(41, data3D[0][4][1]);
	digitalWrite(43, data3D[0][3][1]);
	digitalWrite(45, data3D[0][2][1]);
	digitalWrite(47, data3D[0][1][1]);
	digitalWrite(49, data3D[0][0][1]);
	delay(10);
	
	digitalWrite(24, HIGH);
	digitalWrite(26, LOW);
	digitalWrite(41, data3D[0][4][2]);
	digitalWrite(43, data3D[0][3][2]);
	digitalWrite(45, data3D[0][2][2]);
	digitalWrite(47, data3D[0][1][2]);
	digitalWrite(49, data3D[0][0][2]);
	delay(10);
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

	cube->deallocateMemory();
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
	
	cube->deallocateMemory();
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
	
	cube->deallocateMemory();
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
	
	cube->deallocateMemory();
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

bool Cube::validPoint(double x, double y, double z) const {
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

bool Cube::validPoint(Point p) const {
	return validPoint(p.x, p.y, p.z);
}
