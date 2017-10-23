#ifndef GEOMETRICS_H
#define GEOMETRICS_H

#include <cmath>
#include <cstdio>
#include "config.h"

struct VectorP;
struct VectorR;


struct VectorP {
	UFLOAT mod;
	UFLOAT angle;
	operator VectorR() const;
};

struct VectorR {
	UFLOAT x;
	UFLOAT y; 
	
	operator VectorP();
	struct VectorR operator +(const struct VectorR &A);
	struct VectorR operator *(const UFLOAT &Q);
	struct VectorR mpow(const UFLOAT &E);
	struct VectorR sum_angle(const UFLOAT &A);
	UFLOAT module();
	UFLOAT calculateAngle(VectorR V);
	struct Point deslocate_point(struct Point position);
	struct VectorR normalize();
};

struct Point {
	UFLOAT x;
 	UFLOAT y;
 	
	struct VectorR PointDistance(struct Point);
};



#endif
