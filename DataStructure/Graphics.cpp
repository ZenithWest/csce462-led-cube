#include "Graphics.h"

Point Graphics::rotateXAxis(Point p, double rad) {
	p.x =  p.x;
	p.y =  p.y*cos(rad) + p.z*sin(rad);
	p.z = -p.y*sin(rad) + p.z*cos(rad);
}

Point Graphics::rotateYAxis(Point p, double rad){
	p.x =  p.x*cos(rad) - p.z*sin(rad);
	p.y =  p.y;
	p.z =  p.x*sin(rad) + p.z*cos(rad);
}

Point Graphics::rotateZAxis(Point p, double rad){
	p.x =  p.x*cos(rad) - p.y*sin(rad);
	p.y =  p.x*sin(rad) + p.y*cos(rad);
	p.z =  p.z;
}

Point Graphics::rotateYXZ(Point p, double radY, double radX, double radZ){
	double sinXZ = sin(radX)*sin(radZ);
	double sinXcosY = sin(radX)*cos(radZ);
	p.x =  cos(radY)*cos(radX)*p.x  +  (cos(radY)*sinXcosY + sin(radY)*sin(radZ))*p.y  +  (cos(radY)*sinXZ - sin(radY)*cos(radZ))*p.z;
	p.y =     (-sin(radX))*p.x      +             (cos(radX)*cos(radZ))*p.y            +            (cos(radX)*sin(radZ))*p.z;
	p.z =  sin(radY)*cos(radX)*p.x  +  (sin(radY)*sinXcosY - cos(radY)*sin(radZ))*p.y  +  (sin(radY)*sinXZ + cos(radY)*cos(radZ))*p.z;
}

Point translate(Point p, double x, double y, double z) {

}

