
#include "Arduino.h"
#include "VSPDE.h"
#include "Graphics.h"
#include "Cube.h"
//#include <Print.h>
//#include "MsTimer2.h"
//#include "mthread.h"

Cube* cube;
bool pin41;
bool pin43;
bool pin45;
bool pin47;
bool pin49;
bool pin22;
bool pin24;
bool pin26;

/*
// Our custom Thread:
class FooThread : public Thread
{
public:
  FooThread(int id);
protected:
  bool loop();
private:
  int id;
};

FooThread::FooThread(int id)
{
  // Set the ID:
  this->id = id;

}

bool FooThread::loop()
{

  // Die if requested:
  if(kill_flag)
	 return false;
	
  cube->BW_WritePins();
  //sleep(1);
  return true;

}

// Our custom Thread:
class FooThread2 : public Thread
{
public:
  FooThread2(int id);
protected:
  bool loop();
private:
  int id;
};

FooThread2::FooThread2(int id)
{
  // Set the ID:
  this->id = id;

}

bool FooThread2::loop()
{

  // Die if requested:
  if(kill_flag)
	 return false;
	
  cube->BW_ReceiveData();
  //sleep(1);
  return true;

}
*/

void setup() {
	Serial.begin(9600);
	pinMode(41, OUTPUT);
	pinMode(43, OUTPUT);
	pinMode(45, OUTPUT);
	pinMode(47, OUTPUT);
	pinMode(49, OUTPUT);
	pinMode(22, OUTPUT);
	pinMode(24, OUTPUT);
	pinMode(26, OUTPUT);
	pin41 = false;
	pin43 = false;
	pin45 = false;
	pin47 = false;
	pin49 = false;
	pin22 = true;
	pin24 = true;
	pin26 = true;
	cube = new Cube(1,5,3);

	//MsTimer2::set(1, writepins);
	//MsTimer2::set(1, readpin);
	//MsTimer2::start();

	//main_thread_list->add_thread(new FooThread(0));
	//main_thread_list->add_thread(new FooThread2(1));
}

//void serialEvent() {
//	int led;
	//cube->receiveData();
//	Serial.println("Read");
//	led = Serial.parseInt();
//	cube->flip(0, led % 5, led / 5);
	/*
	if (Serial.available()) {
		
		char byte;
		byte = Serial.read();
		switch (byte) {
		case '1':
			pin41 = !pin41;
			digitalWrite(41, pin41);
			if (pin41) {
				Serial.println("41 ON");
			} else {
				Serial.println("41 OFF");
			}
			break;
		case '2':
			pin43 = !pin43;
			digitalWrite(43, pin43);
			if (pin43) {
				Serial.println("43 ON");
			} else {
				Serial.println("43 OFF");
			}
			break;
		case '3':
			pin45 = !pin45;
			digitalWrite(45, pin45);
			if (pin45) {
				Serial.println("45 ON");
			} else {
				Serial.println("45 OFF");
			}
			break;
		case '4':
			pin47 = !pin47;
			digitalWrite(47, pin47);
			if (pin47) {
				Serial.println("47 ON");
			} else {
				Serial.println("47 OFF");
			}
			break;
		case '5':
			pin49 = !pin49;
			digitalWrite(49, pin49);
			if (pin49) {
				Serial.println("49 ON");
			} else {
				Serial.println("49 OFF");
			}
			break;

		case 'a':
			pin22 = !pin22;
			digitalWrite(22, pin22);
			
			if (pin22) {
				Serial.println("22 ON");
			} else {
				Serial.println("22 OFF");
			}
			break;
		case 'b':
			pin24 = !pin24;
			digitalWrite(24, pin24);
			
			if (pin24) {
				Serial.println("24 ON");
			} else {
				Serial.println("24 OFF");
			}
			break;
		case 'c':
			pin26 = !pin26;
			digitalWrite(26, pin26);
			
			if (pin26) {
				Serial.println("26 ON");
			} else {
				Serial.println("26 OFF");
			}
			break;
		}
	}
	*/
//}



void loop() {
	noInterrupts();

  cube->BW_WritePins();
  interrupts();

  cube->BW_ReceiveData();
}

