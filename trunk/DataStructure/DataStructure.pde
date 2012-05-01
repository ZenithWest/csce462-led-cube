
#include "Arduino.h"
#include "VSPDE.h"
#include "Cube.h"

Cube* cube;

void setup() {
	Serial.begin(115200);

	pinMode(36, OUTPUT);
	pinMode(38, OUTPUT);
	pinMode(40, OUTPUT);
	pinMode(42, OUTPUT);
	pinMode(44, OUTPUT);
	pinMode(46, OUTPUT);
	pinMode(48, OUTPUT);
	pinMode(50, OUTPUT);
	pinMode(52, OUTPUT);

	pinMode(22, OUTPUT);
	pinMode(24, OUTPUT);
	pinMode(26, OUTPUT);

	cube = new Cube(3,3,3);

	int pinBaseList[9];
	int pinLayerList[5];

	pinBaseList[0] = 52;
	pinBaseList[1] = 50;
	pinBaseList[2] = 48;
	pinBaseList[3] = 46;
	pinBaseList[4] = 44;
	pinBaseList[5] = 42;
	pinBaseList[6] = 40;
	pinBaseList[7] = 38;
	pinBaseList[8] = 36;

	pinLayerList[0] = 22;
	pinLayerList[1] = 24;
	pinLayerList[2] = 26;

	cube->initializePinBaseList(&pinBaseList[0], 9);
	cube->initializePinLayerList(&pinLayerList[0], 3);
}


void loop() {
  cube->BW_WritePins();
  cube->BW_ReceiveData();
}

