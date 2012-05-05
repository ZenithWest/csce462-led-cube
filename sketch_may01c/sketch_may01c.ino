#include "Cube.h"
#include "Snake.h"

const int joyH = 1;        // L/R Parallax Thumbstick
const int joyV = 2;        // U/D Parallax Thumbstick

Snake* snake;// = new Snake(4);
Snake* snake2;
void setup() {
  // Inizialize Serial
  Serial.begin(9600);
  snake = new Snake(3);
 // snake2 = new Snake(3);
}
int wait = 3;
void loop(){

    // Display Joystick values using the serial monitor
    //outputJoystick();
    
    if(wait < 0)
    {
      int x = analogRead(joyH);
      int y = analogRead(joyV);
      snake->Move(x,y);
 //     snake2->Move();
    }
    else
    {
      Serial.println(wait);
      wait = wait - 1;
    }
    
    delay(500);                                      

}
void outputJoystick(){

    Serial.print(analogRead(joyH));
    Serial.print ("---"); 
    Serial.print(analogRead(joyV));
    Serial.println ("----------------");
}
