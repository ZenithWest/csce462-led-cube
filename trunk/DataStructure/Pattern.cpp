#include "Pattern.h"


Pattern::Pattern(Cube* c) {
	cube = c;
	currentFrame = 0;
	totalFrames = 0;
	srand(1000);
}


Pattern::~Pattern(void) {

}

void Pattern::receiveData() {
	delay(1);
	if (Serial.available()) {
		int led = Serial.read() - '0';
		if (Serial.available()) {
			led *= 10;
			led += Serial.read() - '0';
		}
		if (Serial.available()) {
			led *= 10;
			led += Serial.read() - '0';
		}

		int ledM1 = led - 1;
		char str[12];

		Serial.print(led);
		Serial.print(": ");

		sprintf(str, "(%d,%d,%d)\n", int(ledM1) % cube->dimX, int(ledM1 / cube->dimX) % cube->dimY, int(ledM1 / cube->sizeXY) % cube->dimZ);
		Serial.print(str);
		if (led >= 0 && led <= cube->sizeXYZ) {
			cube->flip(cube->pinNum2Point(ledM1));
			patternNumber = 0;
		} else if (led == 98) {
			cube->clear();
			patternNumber = 0;
		} else if (led == 99) {
			cube->setAll();
			patternNumber = 0;
		} else if (led > 99) {
			initializePattern(led);
		}
		

		while (Serial.available()) led = Serial.read();
	}
	
}

// 100: Pause/Restart
// 101: Vertial layers
// 102: Spinning Columns
// 103: Fill
// 104: Random
// 105-107: Translate with Random

void Pattern::initializePattern(int num) {
	if (num == 100) {
		if (patternNumber == 100) {
			patternNumber = patternPrev;
		} else {
			patternPrev = patternNumber;
			patternNumber = 100;
		}
	} else {
		currentFrame = 0;
		patternPrev = patternNumber;
		patternNumber = num;
	}
	switch(num) {
	case 101:
		totalFrames = 110;
		break;
	case 102:
		totalFrames = 80;
		break;
	case 103:
		totalFrames = 107;
		break;
	case 104:
		totalFrames = 5;
		break;
	case 105:
	case 106:
	case 107:
		totalFrames = 25;
		break;
	default:
		break;
	}
}

void Pattern::nextFrame() {
	currentFrame = (++currentFrame) % totalFrames;
	switch(patternNumber) {
	case 101:
		pattern101(currentFrame);
		break;
	case 102:
		pattern102(currentFrame);
		break;
	case 103:
		pattern103(currentFrame);
		break;
	case 104:
		pattern104(currentFrame);
		break;
	case 105:
	case 106:
	case 107:
		patternTranslate(currentFrame);
		break;
	default:
		break;
	}
}

void Pattern::pattern101(int frame) {
	cube->clear();
	if (frame < 10) 
		cube->setLayer(0, true);
	else if (frame < 20) 
		cube->setLayer(1, true);
	else if (frame < 30) 
		cube->setLayer(2, true);
	else if (frame < 40) 
		cube->setLayer(3, true);
	else if (frame < 50) 
		cube->setLayer(4, true);
	else if (frame < 60) 
		cube->setLayer(5, true);
	else if (frame < 70) 
		cube->setLayer(4, true);
	else if (frame < 80) 
		cube->setLayer(3, true);
	else if (frame < 90) 
		cube->setLayer(2, true);
	else if (frame < 100) 
		cube->setLayer(1, true);
	else
		cube->setLayer(0, true);
}

void Pattern::pattern102(int frame) {
	cube->clear();
	cube->setColumn(1, 1, true);
	if (frame < 10) 
		cube->setColumn(0, 0, true);
	else if (frame < 20) 
		cube->setColumn(0, 1, true);
	else if (frame < 30) 
		cube->setColumn(0, 2, true);
	else if (frame < 40) 
		cube->setColumn(1, 2, true);
	else if (frame < 50) 
		cube->setColumn(2, 2, true);
	else if (frame < 60) 
		cube->setColumn(2, 1, true);
	else if (frame < 70) 
		cube->setColumn(2, 0, true);
	else
		cube->setColumn(1, 0, true);
}

void Pattern::pattern103(int frame) {
	//cube->clear();
	if (currentFrame < 54) {
		cube->setPin(currentFrame, true);
	} else {
		cube->setPin((totalFrames - currentFrame), false);
	}
}

void Pattern::pattern104(int frame) {
	//cube->clear();
	//if (currentFrame == 0) {
		cube->flipPin(rand() % (cube->sizeXYZ));
		
	//}
}


void Pattern::patternTranslate(int frame) {
	if (currentFrame == 0) {
		if (patternNumber == 105) {
			cube->translate(0,0,1);
			for (int i=0; i<cube->sizeXY; ++i) {
				cube->setPin(i, rand() % 2);
			}
		}
		else if (patternNumber == 106) {
			cube->translate(0,1,0);
			for (int x=0; x<cube->dimX; ++x) {
				for (int z=0; z<cube->dimZ; ++z) {
					cube->set(x, 0, z, rand() % 2);
				}
			}
		}
		else if (patternNumber == 107) {
			cube->translate(1,0,0);
			for (int z=0; z<cube->dimZ; ++z) {
				for (int y=0; y<cube->dimY; ++y) {
					cube->set(0, y, z, rand() % 2);
				}
			}
		}
	}
}

