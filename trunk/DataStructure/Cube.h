#include <stdlib.h> // for malloc and free
#include "VSPDE.h"

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
  bool*** data;

  Cube(int X, int Y, int Z);

  
  bool getValue(int x, int y, int z);	// Returns true if LED on, false otherwise
  bool getValue(Point p);
  void setHIGH(int x, int y, int z);// Turns LED on
  void setHIGH(Point p);
  void setLOW(int x, int y, int z);	// Turns LED off
  void setLOW(Point p);
  bool flipValue(int x, int y, int z);	// Flips and returns new value
  bool flipValue(Point p);
  void drawLine(Point p1, Point p2);
  void drawCircle(Point p1, int radius);
  void rotateX(int dir);
  void translate(int x, int y, int z);
  void clearCube();
};
