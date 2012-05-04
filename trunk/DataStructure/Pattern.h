#pragma once
#include "Cube.h"

class Pattern {
public:
	Cube* cube;
	int currentFrame;
	int totalFrames;
	int patternNumber;
	int patternPrev;
	


	Pattern(Cube* c);
	~Pattern(void);
	
	
	void receiveData();

	void initializePattern(int num);
	void nextFrame();

	void pattern101(int frame);
	void pattern102(int frame);
	void pattern103(int frame);
	void pattern104(int frame);
	void patternTranslate(int frame);
};

