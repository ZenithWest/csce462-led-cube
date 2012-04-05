#include <stdlib.h> // for malloc and free
void* operator new(size_t size) { return malloc(size); }
void* operator new[](size_t size) { return malloc(size); }
void operator delete(void* ptr) { free(ptr); } 


class Point {
public:
  int x;
  int y;
  int z;
  Point(int xx, int yy, int zz) : x(xx), y(yy), z(zz) { }
};

class Cube {
public:
  int dimX;
  int dimY;
  int dimZ;
  boolean*** data;
  
  Cube(int X, int Y, int Z) {
    dimX = X;
    dimY = Y;
    dimZ = Z;
    
    // Initialize 3-dimenisonal data
    data = new boolean**[X];
    //data = (boolean***)malloc(X*sizeof(boolean**));
    for (int i=0; i<X; ++i) {
       data[i] = new boolean*[Y];
       //data[i] = (boolean**)malloc(Y*sizeof(boolean*));
       for (int k=0; k<Y; ++k) {
          data[i][k] = new boolean[Z];
          //data[i][k] = (boolean*)malloc(Z*sizeof(boolean));
       } 
    }
  }
  
  // Returns true if LED on, false otherwise
  boolean getValue(int x, int y, int z) {
    return data[x][y][z];
  }
  
   boolean getValue(Point p) {
    return data[p.x][p.y][p.z];
  }
  
  // Turns LED on
  void setHIGH(int x, int y, int z) {
      data[x][y][z] = true;
  }
  
  // Turns LED off
  void setLOW(int x, int y, int z) {
      data[x][y][z] = false;
  }
  
  // Flips and returns new value
  boolean flipValue(int x, int y, int z) {
      data[x][y][z] = !data[x][y][z];
      return data[x][y][z];
  }
  
  void drawLine(Point p1, Point p2) {
    
  }
};

Cube* cube;

void setup() {
   cube = new Cube(3,3,3);
}

void loop() {
  
}
