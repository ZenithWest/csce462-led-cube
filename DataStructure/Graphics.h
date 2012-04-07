#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Arduino.h"
#include "VSPDE.h"


struct Point {
	double x;
	double y;
	double z;
	Point(double xx, double yy, double zz) : 
		x(xx), y(yy), z(zz) { 
	}
};

struct Line {
	Point p1;
	Point p2;
	double thickness;
	bool fill;
	Line(Point pp1, Point pp2) : p1(pp1), p2(pp2), thickness(1.0), fill(false) { }
};

struct Square {
	Point p1;
	Point p2;
	double thickness;
	bool fill;
	Square(Point pp1, Point pp2) : p1(pp1), p2(pp2), thickness(1.0), fill(false) { }
};

struct Circle {
	Point center;
	double radius;
	double thickness;
	bool fill;
	Circle(Point c, double r) : center(c), radius(r), thickness(1.0), fill(false) { }
};

struct Graphics {
	Point rotateXAxis(Point p, double rad);
	Point rotateYAxis(Point p, double rad);
	Point rotateZAxis(Point p, double rad);
	Point rotateYXZ(Point p, double radY, double radX, double radZ);
	Point translate(Point p, double y, double z);
};


#endif
