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

void Cube::setAll() {
	memset(data1D, 1, size*sizeof(bool));
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

		led -= 1;
		
		char str[12];

		sprintf(str, "(%d,%d,%d)\n", (led / 9) % 3, (led / 3) % 3, led % 3);
		Serial.print(str);
		if (led > 0 && led <= 27) {
			flip((led / 9)  % 3, (led / 3) % 3, led % 3);
		} else if (led == 99) {
			clear();
		} else if (led == 98) {
			setAll();
		}
		

		while (Serial.available()) led = Serial.read();
	}
	
}

void Cube::BW_WritePins() {

	
	for (int z=0; z<dimZ; ++z) {
		if (z==0) {
			//pinMode(pinLayerList[dimZ-1], OUTPUT);
			digitalWrite(pinLayerList[dimZ-1], HIGH);
			digitalWrite(pinLayerList[0], LOW);
			//pinMode(pinLayerList[0], INPUT);
		} else {
			//pinMode(pinLayerList[z-1], OUTPUT);
			digitalWrite(pinLayerList[z-1], HIGH);
			digitalWrite(pinLayerList[z], LOW);
			//pinMode(pinLayerList[z], INPUT);
		}
		for (int x=0; x<dimX; ++x) {
			for (int y=0; y<dimY; ++y) {
				if (data3D[x][y][z]) {
					//pinMode(pinBaseList2D[x][y], OUTPUT);
					digitalWrite(pinBaseList2D[x][y], HIGH);
				} else {
					digitalWrite(pinBaseList2D[x][y], LOW);
					//pinMode(pinBaseList2D[x][y], INPUT);
				}
				
			}
		}
		delay(250);
	}
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
