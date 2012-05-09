
#include "Arduino.h"
#include "VSPDE.h"
#include "Cube.h"
#include "Pattern.h"
#include "Snake.h"
#include "Pong.h"
#include "Breakout.h"
#include "MenuScreen.h"

Cube* cube;
Pattern* pattern;
Snake* snake;
Pong* pong;
Breakout* breakout;
const int joyH = 1;        // L/R Parallax Thumbstick
const int joyV = 0;        // U/D Parallax Thumbstick

int pinBaseList[9] = { 52, 50, 48, 46, 44, 42, 40, 38, 36 };
int pinLayerList[6] = {22, 24, 26, 23, 25, 27};

//
 MenuScreen* menu;
void setup() {
	Serial.begin(115200);


	for (int xy=0; xy<9; ++xy)
		pinMode(pinBaseList[xy], OUTPUT);
	
	for (int z=0; z<6; ++z)
		pinMode(pinLayerList[z], OUTPUT);

	cube = new Cube(3,3,6);

	cube->initializePinBaseList(&pinBaseList[0], 9);
	cube->initializePinLayerList(&pinLayerList[0], 6);
         menu = new MenuScreen(cube,3);
       // breakout = new Breakout(cube,3,2);
        //pong = new Pong(cube,3,2);
        //snake = new Snake(cube,3);
       //cube->setHIGH(0,0,2);
	//pattern = new Pattern(cube);
}


int counter = 1;

void loop() {
  int x = analogRead(joyH);
  int y = analogRead(joyV);
  
 // Serial.println(x);
  //cube->setHIGH(2,0,0);
  //pong->Draw();
 // breakout->Draw();
 menu->Joystick(x,y);
  cube->setHIGH(2,2,4);
  
  if(counter % 30 == 0) 
  {
    //int x13 = random(2);
        
    //    Serial.println(x13);
     //   breakout->MovePaddle1(x, y);
      //pong->MovePaddle1(x, y);
     // Serial.println("MOVE");
      
      // Serial.println(x);
      //Serial.println(y);
   // snake->Move(x,y);
  }
  if(counter % 200 == 0)
  {
   // pong->MoveBall();
    //breakout->MoveBall();
  }
  //snake->Draw();
  cube->BW_WritePins();
  counter++;
  /*
  if (Serial.available() && (counter % 100) == 0) {
	  cube->clear();
	  pattern->printCharacter(Serial.read());
	}
	counter++;*/
  //cube->receiveData();
  //pattern->receiveData();
  //pattern->nextFrame();
  //delay(10);
}
