#include <string.h>

#define BAUD 115200
#define PLANECOUNT 6
#define ROWSIZE 3
#define PLANESIZE ROWSIZE*ROWSIZE
#define CUBESIZE PLANECOUNT*PLANESIZE
#define USEC_DELAY 3000
#define DEMO_DELAY 400

/* NOTE: Arduino micros() rolls over after ~70 minutes */
/* WARNING: Maximum plane size is 49 by hardware limitation */

bool cube[CUBESIZE];
char curPlane = 0;
long waitUntil = 0;
char serialCounter = 0;

// Pin Definitions
/* MSB Oriented decoder */
/*
const char planeDecoder[3] = {11, 12, 13};
const char active[] = { 2, 3, 4, 5, 6, 7, 8,
                       9, 10, 14, 15, 16, 17, 18,
                       19, 20, 21, 22, 23, 24, 25,
                       26, 27, 28, 29, 30, 31, 32,
                       33, 34, 35, 36, 37, 38, 39,
                       40, 41, 42, 43, 44, 45, 46,
                       47, 48, 49, 50, 51, 52, 53 };
*/

const char planeDecoder[6] = {22, 24, 26, 23, 25, 27};
const char active[] = { 52, 50, 48, 46, 44, 42, 40,
                        38, 36 };
                        
const bool scene[10][CUBESIZE] = {
  // Go up
  { true, true, true, true, false, true, true, true, true,
   false, false, false, false, true, false, false, false, false,
   false, false, false, false, false, false, false, false, false,
   false, false, false, false, false, false, false, false, false,
   false, false, false, false, false, false, false, false, false,
   false, false, false, false, false, false, false, false, false },
  { false, false, false, false, false, false, false, false, false,
    true, true, true, true, false, true, true, true, true,
    false, false, false, false, true, false, false, false, false,
    false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false },
  { false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false,
    true, true, true, true, false, true, true, true, true,
    false, false, false, false, true, false, false, false, false,
    false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false },
  { false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, 
    true, true, true, true, false, true, true, true, true,
    false, false, false, false, true, false, false, false, false,
    false, false, false, false, false, false, false, false, false },
  {  false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false,
    true, true, true, true, false, true, true, true, true,
    false, false, false, false, true, false, false, false, false },
    
    // And go down
  { false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false,
    false, false, false, false, true, false, false, false, false,
    true, true, true, true, false, true, true, true, true},
  { false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false,
    false, false, false, false, true, false, false, false, false,
    true, true, true, true, false, true, true, true, true,
    false, false, false, false, false, false, false, false, false},
  { false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false,
    false, false, false, false, true, false, false, false, false,
    true, true, true, true, false, true, true, true, true,
    false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false },
  { false, false, false, false, false, false, false, false, false,
    false, false, false, false, true, false, false, false, false,
    true, true, true, true, false, true, true, true, true,
    false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false },
  { false, false, false, false, true, false, false, false, false,
    true, true, true, true, false, true, true, true, true,
    false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false },
};

long nextScene = 0;
long curScene = 0;

void setup() {
  for ( unsigned i = 0; i < CUBESIZE; ++i ) {
    cube[i] = false;
  }
  pinMode( planeDecoder[0], OUTPUT );
  pinMode( planeDecoder[1], OUTPUT );
  pinMode( planeDecoder[2], OUTPUT );
  pinMode( planeDecoder[3], OUTPUT );
  pinMode( planeDecoder[4], OUTPUT );
  pinMode( planeDecoder[5], OUTPUT );
  
  for ( unsigned i = 0; i < 9; ++i )
    pinMode( active[i], OUTPUT );
  
  Serial.begin(BAUD);
  Serial.println("L3D v0.2 Initialized.");
}

void loop() {
  // Receive serial data
  //while ( Serial.available() ) {
    /*
    char data = Serial.read();
    data -= 65;
    Serial.print("Received: ");
    Serial.print( (unsigned char) data );
    Serial.print( "\t" );
    Serial.println( data, BIN );
    cube[ (unsigned char) data ] ^= 1;
    */
    //Serial.readBytes(cube, CUBESIZE);
  //}
  if ( millis() > nextScene ) {
    memcpy(cube, scene[curScene], CUBESIZE);
    nextScene = millis() + DEMO_DELAY;
    curScene == 9 ? curScene = 0 : curScene++;
  }
    
    // Put to cube
    /*
    if ( CUBESIZE - serialCounter*8 > 8 ) {
      cube[serialCounter*8] = data & 0x80;
      cube[serialCounter*8 + 1] = data & 0x40;
      cube[serialCounter*8 + 2] = data & 0x20;
      cube[serialCounter*8 + 3] = data & 0x10;
      cube[serialCounter*8 + 4] = data & 0x8;
      cube[serialCounter*8 + 5] = data & 0x4;
      cube[serialCounter*8 + 6] = data & 0x2;
      cube[serialCounter*8 + 7] = data & 0x1;
    }
    else if ( CUBESIZE - serialCounter*8 > 0 ) {
      for ( unsigned char i = 0; i < CUBESIZE - serialCounter*8; ++i )
        cube[serialCounter*8 + i] = data & ( 1 << i );
    }
    ++serialCounter;
  }
  serialCounter = 0; */
  
  // Serial.println("Loop start");
  
  // Sleep if not time to refresh
  while ( micros() < waitUntil );
  
  // Refresh next plane
  char planeSelect[6] = { curPlane == 0x0, curPlane == 0x1, curPlane == 0x2, curPlane == 0x3,
                           curPlane == 0x4, curPlane == 0x5 };
  digitalWrite(planeDecoder[0], planeSelect[0]);
  digitalWrite(planeDecoder[1], planeSelect[1]);
  digitalWrite(planeDecoder[2], planeSelect[2]);
  digitalWrite(planeDecoder[3], planeSelect[3]);
  digitalWrite(planeDecoder[4], planeSelect[4]);
  digitalWrite(planeDecoder[5], planeSelect[5]);
  
  // Hmm, maybe this can be unrolled? Does it need to be? *shrugs*
  for (unsigned u = 0; u < PLANESIZE; ++u)
    digitalWrite(active[u], cube[curPlane*PLANESIZE + u] ^ 1);
  
  // Next Plane
  curPlane == PLANECOUNT - 1 ? curPlane = 0 : ++curPlane;
  waitUntil = micros() + USEC_DELAY;
}
