#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Arduino.h"
#include "VSPDE.h"
#include <math.h>

struct Graphics;
struct Point;

struct Graphics {
	Point rotateXAxis(Point p, Point center, double rad);
	Point rotateYAxis(Point p, Point center, double rad);
	Point rotateZAxis(Point p, Point center, double rad);
	Point rotateYXZ(Point p, Point center, double radY, double radX, double radZ);
	Point translate(Point p, Point center, double x, double y, double z);
};

// Need to move functions to cpp later

struct Point {
	double x;
	double y;
	double z;
	Point() : x(0.0), y(0.0), z(0.0) { }
	Point(double xx, double yy, double zz) : x(xx), y(yy), z(zz) { }
	Point operator+ (Point p) {
		x += p.x;
		y += p.y;
		z += p.z;
		return *this;
	}
	Point operator- (Point p) {
		x -= p.x;
		y -= p.y;
		z -= p.z;
		return *this;
	}
	Point operator- () {
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}
	Point operator* (int scale) {
		x = scale*x;
		y = scale*y;
		z = scale*z;
		return *this;
	}
	Point operator/ (int scale) {
		x = x/scale;
		y = y/scale;
		z = z/scale;
		return *this;
	}
	Point roundCopy() {
		return Point(round(x), round(y), round(z));
	}
	Point crossProduct(Point p2) {
		Point p1;
		p1.x = y*p2.z - z*p2.y;
		p1.y = z*p2.x - x*p2.z;
		p1.z = x*p2.y - y*p2.x;
		return p1;
	}
	double mag() {
		return sqrt(x*x + y*y + z*z);
	}

};

struct Line {
	Point p1;
	Point p2;
	double thickness;
	Line(Point pp1, Point pp2, double t = 1.0) : p1(pp1), p2(pp2), thickness(t) { }
	double distance(Point p) {
		return ((p-p1).crossProduct(p-p2)).mag() / (p2-p1).mag();
	}
	Line rotateX(double deg) {
		double rad = PI*deg/180.0;
		Line line(p1, p2);
		line.p1 = Graphics().rotateXAxis(line.p1, center(), rad);
		line.p2 = Graphics().rotateXAxis(line.p2, center(), rad);
		return line;
	}
	Line rotateY(double deg) {
		double rad = PI*deg/180.0;
		Line line(p1, p2);
		line.p1 = Graphics().rotateYAxis(line.p1, center(), rad);
		line.p2 = Graphics().rotateYAxis(line.p2, center(), rad);
		return line;
	}
	Line rotateZ(double deg) {
		double rad = PI*deg/180.0;
		Line line(p1, p2);
		line.p1 = Graphics().rotateZAxis(line.p1, center(), rad);
		line.p2 = Graphics().rotateZAxis(line.p2, center(), rad);
		return line;
	}
	Line translate(Point p) {
		return Line(p1 + p, p2 + p);
	}
	Point center() {
		return (p1+p2)/2;
	}
	double length() {
		return (p2-p1).mag();
	}
};

struct Square {
	Point p1;
	Point p2;
	double thickness;
	bool fill;
	Square(Point pp1, Point pp2, double t = 1.0, bool f = false) : p1(pp1), p2(pp2), thickness(t), fill(f) { }
	double sideLength() {

	}
	Point center() {

	}
};

struct Circle {
	Point center;
	double radius;
	double thickness;
	bool fill;
	Circle(Point c, double r) : center(c), radius(r), thickness(1.0), fill(false) { }
};

/*
struct Graphics {
	Point rotateXAxis(Point p, double rad);
	Point rotateYAxis(Point p, double rad);
	Point rotateZAxis(Point p, double rad);
	Point rotateYXZ(Point p, double radY, double radX, double radZ);
	Point translate(Point p, double x, double y, double z);
};
*/

#endif
