#include <string.h>

#define ROWSIZE 3
#define CUBESIZE ROWSIZE*ROWSIZE*ROWSIZE

bool cube[CUBESIZE];
bool buffer[ROWSIZE];

// Pin Definitions
const int row[3] = { 14, 15, 16};
const int plane[3] = {17, 18, 19};
const int active[] = { 9, 2, 3, 4, 5, 6, 7, 8 };

void setup() {
  for ( unsigned i = 0; i < CUBESIZE; ++i ) {
    cube[i] = false;
  }
  pinMode( row[0], OUTPUT );
  pinMode( row[1], OUTPUT );
  pinMode( row[2], OUTPUT );
  pinMode( plane[0], OUTPUT );
  pinMode( plane[1], OUTPUT );
  pinMode( plane[2], OUTPUT );
  pinMode( active[0], OUTPUT );
  pinMode( active[1], OUTPUT );
  pinMode( active[2], OUTPUT );
  pinMode( active[3], OUTPUT );
  pinMode( active[4], OUTPUT );
  pinMode( active[5], OUTPUT );
  pinMode( active[6], OUTPUT );
  pinMode( active[7], OUTPUT );
  
  Serial.begin(9600);
  Serial.println("L3D v0.1 Initialized.");
}

void loop() {
  // Receive serial data
  while ( Serial.available() ) {
    Serial.print("Received: ");
    Serial.println( (char) Serial.read() );
  }
  
  // Refresh cube
  for ( unsigned curPlane = 0; curPlane < ROWSIZE; ++curPlane ) {
    // set decoder
    digitalWrite( plane[0], curPlane & 0x1 );
    digitalWrite( plane[1], curPlane & 0x2 );
    digitalWrite( plane[2], curPlane & 0x4 );
    
    for ( unsigned curRow = 0; curRow < ROWSIZE; ++curRow ) {
      // set Row decoder
      digitalWrite( row[0], curRow & 0x1 );
      digitalWrite( row[1], curRow & 0x2 );
      digitalWrite( row[2], curRow & 0x4 );
    
      memcpy( buffer, cube + curPlane*ROWSIZE*ROWSIZE + curRow*ROWSIZE, ROWSIZE);
      
      // Possible Optimization: Unroll this loop
      for ( unsigned u = 0; u < ROWSIZE; ++u ) {
        digitalWrite( row[u], curRow & (1 << u) );
      }
    }
  }
}
