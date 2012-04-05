#include <stdlib.h> // for malloc and free
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

  void setHIGH(Point p) {
    data[p.x][p.y][p.z] = true;
  }

  // Turns LED off
  void setLOW(int x, int y, int z) {
    data[x][y][z] = false;
  }

  void setLOW(Point p) {
    data[p.x][p.y][p.z] = false;
  }

  // Flips and returns new value
  boolean flipValue(int x, int y, int z) {
    data[x][y][z] = !data[x][y][z];
    return data[x][y][z];
  }

  boolean flipValue(Point p) {
    data[p.x][p.y][p.z] = !data[p.x][p.y][p.z];
    return data[p.x][p.y][p.z];
  }

  void drawLine(Point p1, Point p2) {

  }

  void drawCircle(Point p1, int radius) {

  }

  void rotateX(int dir) {

  }

  void translate(int x, int y, int z) {

  }

  void clearCube() {
    for (int x=0; x<dimX; ++x) {
      for (int y=0; y<dimY; ++y) {
        for (int z=0; z<dimZ; ++z) {
          data[x][y][z] = false;  
        }
      }
    } 
  }


};

Cube* cube;

void setup() {
  cube = new Cube(3,3,3);
}

void loop() {

}

