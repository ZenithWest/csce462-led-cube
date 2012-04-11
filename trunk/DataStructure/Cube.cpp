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

	center.x = double(dimX)/2.0;
	center.y = double(dimY)/2.0;
	center.z = double(dimZ)/2.0;
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

void Cube::initializePinBaseList(int* pins, int num) {
	pinBaseCount = num;
	pinBaseList1D = (int*)malloc(pinBaseCount*sizeof(int));
	memcpy(pinBaseList1D, pins, pinBaseCount*sizeof(int));

	pinBaseList2D = (int**)malloc(pinBaseCount*sizeof(int*));
	for(int x=0; x<dimX; x++) {
		pinBaseList2D[x] = pinBaseList1D + x*pinBaseCount;
	}
}

void Cube::initializePinLayerList(int* pins, int num) {
	pinLayerCount = num;
	pinLayerList = (int*)malloc(pinLayerCount*sizeof(int));
	memcpy(pinLayerList, pins, pinLayerCount*sizeof(int));
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
		int led = Serial.read() - '0';
		if (Serial.available()) {
			led *= 10;
			led += Serial.read() - '0';
		}
		if (led >= 0 && led <= 14) {
			flip(0, led % 5, led / 5);
		} else if (led == 20) {
			rotateXAxis(center, 30);
		} else if (led == 21) {
			rotateYAxis(center, 30);
		} else if (led == 22) {
			rotateZAxis(center, 30);
		} else if (led == 99) {
			rotateZAxis(center, 30);
		} else if (led == 50) {
			Point p1(0,0,0);
			Point p2(dimX-1,dimY-1,dimZ-1);
			Line line(p1, p2);
			for (int i=0; i < 20; ++i) {
				clear();
				drawLine(line);
				for (int k=0; k<50; ++k) {
					BW_WritePins();
				}
				line = line.rotateX(45);
			}
		} else if (led == 51) {
			Point p1(0,0,0);
			Point p2(dimX-1,dimY-1,dimZ-1);
			Line line(p1, p2);
			for (int i=0; i < 20; ++i) {
				clear();
				drawLine(line);
				for (int k=0; k<50; ++k) {
					BW_WritePins();
				}
				line = line.rotateY(45);
			}
		} else if (led == 52) {
			Point p1(0,0,0);
			Point p2(dimX-1,dimY-1,dimZ-1);
			Line line(p1, p2);
			for (int i=0; i < 20; ++i) {
				clear();
				drawLine(line);
				for (int k=0; k<50; ++k) {
					BW_WritePins();
				}
				line = line.rotateZ(45);
			}
		}
	}
	
}

void Cube::BW_WritePins() {
	
	
	for (int z=0; z<dimZ; ++z) {
		if (z==0) {
			digitalWrite(pinLayerList[dimZ-1], HIGH);
			digitalWrite(pinLayerList[0], LOW);
		} else {
			digitalWrite(pinLayerList[z-1], HIGH);
			digitalWrite(pinLayerList[z], LOW);
		}
		for (int x=0; x<dimX; ++x) {
			for (int y=0; y<dimY; ++y) {
				digitalWrite(pinBaseList2D[x][y], data3D[x][y][z]);
			}
		}
		delay(5);
	}
}


// Graphics

void Cube::drawLine(double x1, double y1, double z1, double x2, double y2, double z2) {
	drawLine(Point(x1,y1,z1),Point(x2,y2,z2));
}

void Cube::drawCircle(double x, double y, double z, double radius, double angle) {
	Cube::drawCircle(Point(x,y,z),radius,angle);
}


void Cube::drawLine(Point p1, Point p2) {
	Line line(p1, p2);
	for (int x=0; x<dimX; ++x) {
		for (int y=0; y<dimY; ++y) {
			for (int z=0; z<dimZ; ++z) {
				if (line.distance(Point(x,y,z)) < 0.5) {
					setHIGH(x,y,z);
				}
			}
		}
	}
}

void Cube::drawLine(Line line) {
	Cube::drawLine(line.p1, line.p2);
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
			for (int z=0; z<dimZ; ++z) {
				if (cube->get(x, y, z)) {
					setHIGH(Graphics().rotateXAxis(Point(x,y,z), p, rad));
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
			for (int z=0; z<dimZ; ++z) {
				if (cube->get(x, y, z)) {
					setHIGH(Graphics().rotateYAxis(Point(x,y,z), p, rad));
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
			for (int z=0; z<dimZ; ++z) {
				if (cube->get(x, y, z)) {
					setHIGH(Graphics().rotateZAxis(Point(x,y,z), p, rad));
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
			for (double z=0; z<dimZ; ++z) {
				if (cube->get(x, y, z)) {
					setHIGH(Graphics().rotateYXZ(Point(x,y,z), p, radY, radX, radZ));
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
