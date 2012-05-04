
#include "Arduino.h"
#include "VSPDE.h"
#include "Cube.h"
#include "Pattern.h"

Cube* cube;
Pattern* pattern;

int pinBaseList[9] = { 52, 50, 48, 46, 44, 42, 40, 38, 36 };
int pinLayerList[6] = {22, 24, 26, 23, 25, 27};


void setup() {
	Serial.begin(115200);


	for (int xy=0; xy<9; ++xy)
		pinMode(pinBaseList[xy], OUTPUT);
	
	for (int z=0; z<6; ++z)
		pinMode(pinLayerList[z], OUTPUT);

	cube = new Cube(3,3,6);

	cube->initializePinBaseList(&pinBaseList[0], 9);
	cube->initializePinLayerList(&pinLayerList[0], 6);

	pattern = new Pattern(cube);
}


int counter = 0;

void loop() {
  cube->BW_WritePins();
  /*
  if (Serial.available() && (counter % 100) == 0) {
	  cube->clear();
	  pattern->printCharacter(Serial.read());
	}
  counter++;*/
  pattern->receiveData();
  pattern->nextFrame();
}

