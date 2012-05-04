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
	sizeXYZ = size;

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

void Cube::initializeBuffer() {
	bufferSize = ceil(sizeXYZ / 8.0) + 3;
	buffer = (char*)malloc(bufferSize);
}

void Cube::initializePinBaseList(int* pins, int num) {
	pinBaseCount = num;
	pinBaseList1D = (int*)malloc(pinBaseCount*sizeof(int));
	memcpy(pinBaseList1D, pins, pinBaseCount*sizeof(int));

	pinBaseList2D = (int**)malloc(pinBaseCount*sizeof(int*));
	for(int x=0; x<dimX; x++) {
		pinBaseList2D[x] = pinBaseList1D + x*dimX;
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

	free(buffer);
	buffer = NULL;
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

void Cube::setLayer(int layer, bool value) {
	for(int x=0; x<dimX; ++x) {
		for(int y=0; y<dimY; ++y) {
			set(x, y, layer, value);
		}
	}
}

void Cube::setPin(int pin, bool value) {
	set(pinNum2Point(pin), value);
}

void Cube::setColumn(int columnX, int columnY, bool value) {
	for(int z=0; z<dimZ; ++z) {
		set(columnX, columnY, z, value);
	}
}

void Cube::flipPin(int pin) {
	flip(pinNum2Point(pin));
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


void Cube::compactBuffer() {
	memset(buffer, 0, bufferSize);
	buffer[0] = HEADER_BUFFER;
	*(short*)(&buffer[1]) = sizeXYZ;
	
	char* tempBuffer = buffer + 3;
	for (int i=0; i<sizeXY; ++i) {
		if (data1D[i])
			bitSet(tempBuffer[i], i & 7);
	}
}

void Cube::sendData() {
	compactBuffer();
	Serial.write((uint8_t*)buffer, bufferSize*sizeof(char));
}

void Cube::receiveData() {
	int i = 0;
	char header = Serial.read();
	if (header == HEADER_BUFFER) {
		short tempSize = (short(Serial.read()) << 8) + Serial.read();
		buffer[0] = header;
		*(short*)(&buffer[1]) = tempSize;
		Serial.readBytes((char*)(buffer + 3), tempSize*sizeof(bool));
	}
}

void Cube::BW_ReceiveData() {
	delay(1);
	if (Serial.available()) {
		int led = Serial.read() - '0';
		if (Serial.available()) {
			led *= 10;
			led += Serial.read() - '0';
		}

		int ledM1 = led - 1;
		char str[12];

		sprintf(str, "(%d,%d,%d)\n", int(ledM1) % dimX, int(ledM1 / dimX) % dimY, int(ledM1 / sizeXY) % dimZ);
		Serial.print(str);
		if (led >= 0 && led <= sizeXYZ) {
			flip(pinNum2Point(ledM1));
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
			digitalWrite(pinLayerList[dimZ-1], 0);
			digitalWrite(pinLayerList[0], 1);
		} else {
			digitalWrite(pinLayerList[z-1], 0);
			digitalWrite(pinLayerList[z], 1);
		}
		
		for (int x=0; x<dimX; ++x) {
			for (int y=0; y<dimY; ++y) {
				if (data3D[x][y][z]) {
					digitalWrite(pinBaseList2D[x][y], 0);
				} else {
					digitalWrite(pinBaseList2D[x][y], 1);
				}
				
			}
		}
		delay(1);
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


Point Cube::pinNum2Point(int num) {
	return Point((num) % dimX, (num / dimX) % dimY, (num / sizeXY) % dimZ);
}


void Cube::translate(int dirX, int dirY, int dirZ) {
	if (dirZ > 0) {
		for (int x = 0; x<dimX; ++x) {
			for (int y = 0; y<dimY; ++y) {
				for (int z=dimZ-1; z>0; --z) {
					set(x, y, z, get(x,y,z-1));
				}
			}
		}

		for (int x = 0; x<dimX; ++x) {
			for (int y = 0; y<dimY; ++y) {
				set(x, y, 0, false);
			}
		}
	} else if (dirZ < 0) {
		for (int x = 0; x<dimX; ++x) {
			for (int y = 0; y<dimY; ++y) {
				for (int z=0; z<dimZ-1; --z) {
					set(x, y, z, get(x,y,z+1));
				}
			}
		}

		for (int x = 0; x<dimX; ++x) {
			for (int y = 0; y<dimY; ++y) {
				set(x, y, dimZ-1, false);
			}
		}
	}



	if (dirX > 0) {
		for (int z = 0; z<dimZ; ++z) {
			for (int y = 0; y<dimY; ++y) {
				for (int x=dimX-1; x>0; --x) {
					set(x, y, z, get(x-1,y,z));
				}
			}
		}

		for (int z = 0; z<dimZ; ++z) {
			for (int y = 0; y<dimY; ++y) {
				set(0, y, z, false);
			}
		}
	} else if (dirX < 0) {
		for (int z = 0; z<dimZ; ++z) {
			for (int y = 0; y<dimY; ++y) {
				for (int x=0; x<dimX-1; --x) {
					set(x, y, z, get(x+1,y,z));
				}
			}
		}

		for (int z = 0; z<dimZ; ++z) {
			for (int y = 0; y<dimY; ++y) {
				set(dimX-1, y, z, false);
			}
		}
	}



	if (dirY > 0) {
		for (int x = 0; x<dimX; ++x) {
			for (int z = 0; z<dimZ; ++z) {
				for (int y=dimY-1; y>0; --y) {
					set(x, y, z, get(x,y-1,z));
				}
			}
		}

		for (int x = 0; x<dimX; ++x) {
			for (int z = 0; z<dimZ; ++z) {
				set(x, 0, z, false);
			}
		}
	} else if (dirY < 0) {
		for (int x = 0; x<dimX; ++x) {
			for (int z = 0; z<dimZ; ++z) {
				for (int y=0; y<dimY-1; --y) {
					set(x, y, z, get(x,y+1,z));
				}
			}
		}

		for (int x = 0; x<dimX; ++x) {
			for (int z = 0; z<dimZ; ++z) {
				set(x, dimY-1, z, false);
			}
		}
	}
}
