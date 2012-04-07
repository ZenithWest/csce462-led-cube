#include <stdlib.h> // for malloc and free
#include "Cube.h"

void* operator new(size_t size) { 
  return malloc(size); 
}
void* operator new[](size_t size) { 
  return malloc(size); 
}
void operator delete(void* ptr) { 
  free(ptr); 
} 

Cube::Cube(int X, int Y, int Z) {
   dimX = X;
   dimY = Y;
   dimZ = Z;

   // Initialize 3-dimensional data
   data = new bool**[X];
   //data = (boolean***)malloc(X*sizeof(boolean**));
   for (int i=0; i<X; ++i) {
   data[i] = new bool*[Y];
   //data[i] = (boolean**)malloc(Y*sizeof(boolean*));
   for (int k=0; k<Y; ++k) {
      data[i][k] = new bool[Z];
      //data[i][k] = (boolean*)malloc(Z*sizeof(boolean));
   } 
   }
}

// Returns true if LED on, false otherwise
bool Cube::getValue(int x, int y, int z) {
   return data[x][y][z];
}

bool Cube::getValue(Point p) {
   return data[p.x][p.y][p.z];
}

// Turns LED on
void Cube::setHIGH(int x, int y, int z) {
   data[x][y][z] = true;
}

void Cube::setHIGH(Point p) {
   data[p.x][p.y][p.z] = true;
}

// Turns LED off
void Cube::setLOW(int x, int y, int z) {
   data[x][y][z] = false;
}

void Cube::setLOW(Point p) {
   data[p.x][p.y][p.z] = false;
}

// Flips and returns new value
bool Cube::flipValue(int x, int y, int z) {
   data[x][y][z] = !data[x][y][z];
   return data[x][y][z];
}

bool Cube::flipValue(Point p) {
   data[p.x][p.y][p.z] = !data[p.x][p.y][p.z];
   return data[p.x][p.y][p.z];
}

void Cube::drawLine(Point p1, Point p2) {

}

void Cube::drawCircle(Point p1, int radius) {

}

void Cube::rotateX(int dir) {

}

void Cube::translate(int x, int y, int z) {

}

void Cube::clearCube() {
   for (int x=0; x<dimX; ++x) {
   for (int y=0; y<dimY; ++y) {
      for (int z=0; z<dimZ; ++z) {
         data[x][y][z] = false;  
      }
   }
   } 
}

