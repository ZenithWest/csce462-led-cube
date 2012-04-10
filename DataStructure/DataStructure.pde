
#include "Arduino.h"
#include "VSPDE.h"
#include "Graphics.h"
#include "Cube.h"

Cube* cube;

void setup() {
	Serial.begin(115200);

	pinMode(41, OUTPUT);
	pinMode(43, OUTPUT);
	pinMode(45, OUTPUT);
	pinMode(47, OUTPUT);
	pinMode(49, OUTPUT);
	pinMode(22, OUTPUT);
	pinMode(24, OUTPUT);
	pinMode(26, OUTPUT);

	cube = new Cube(1,5,3);

	int pinBaseList[5];
	int pinLayerList[5];

	pinBaseList[0] = 49;
	pinBaseList[1] = 47;
	pinBaseList[2] = 45;
	pinBaseList[3] = 43;
	pinBaseList[4] = 41;

	pinLayerList[0] = 22;
	pinLayerList[1] = 24;
	pinLayerList[2] = 26;

	cube->initializePinBaseList(&pinBaseList[0], 5);
	cube->initializePinLayerList(&pinLayerList[0], 3);

}


void loop() {
  cube->BW_WritePins();
  cube->BW_ReceiveData();
}

