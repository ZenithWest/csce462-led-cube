#include <stdlib.h> // for malloc and free
#include "VSPDE.h"

void* operator new(size_t size) { 
  return malloc(size); 
}
void* operator new[](size_t size) { 
  return malloc(size); 
}
void operator delete(void* ptr) { 
  free(ptr); 
} 


class Point {
public:
  int x;
  int y;
  int z;
  Point(int xx, int yy, int zz) : 
  x(xx), y(yy), z(zz) { 
  }
};

class Cube {
public:
  int dimX;
  int dimY;
  int dimZ;
  boolean*** data;

  Cube(int X, int Y, int Z);

  
  boolean getValue(int x, int y, int z);	// Returns true if LED on, false otherwise
  boolean getValue(Point p);
  void setHIGH(int x, int y, int z);// Turns LED on
  void setHIGH(Point p);
  void setLOW(int x, int y, int z);	// Turns LED off
  void setLOW(Point p);
  boolean flipValue(int x, int y, int z);	// Flips and returns new value
  boolean flipValue(Point p);
  void drawLine(Point p1, Point p2);
  void drawCircle(Point p1, int radius);
  void rotateX(int dir);
  void translate(int x, int y, int z);
  void clearCube();
};
