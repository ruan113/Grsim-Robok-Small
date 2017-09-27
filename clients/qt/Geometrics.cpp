#include "Geometrics.h"

struct VectorR Point::PointDistance(struct Point Ponto){
	struct VectorR Point2Vector;

	Point2Vector.x = Ponto.x - this->x;
	Point2Vector.y = Ponto.y - this->y;
	
	return Point2Vector;	
}

VectorR::operator VectorP() {
	struct VectorP Polar;
	Polar.mod = sqrt(pow(this->x,2) + pow(this->y,2));
	Polar.angle = atan(this->y/this->x);

	return Polar;
}
	
VectorP::operator VectorR() const{	
	struct VectorR Retangular;
	Retangular.x = this->mod*cos(this->angle);	
	Retangular.y = this->mod*sin(this->angle);

	return Retangular;	
}

struct VectorR VectorR::operator +(const struct VectorR &A){
	struct VectorR Final_vector;
	
	Final_vector.x = A.x + this->x;
	Final_vector.y = A.y + this->y;

	return Final_vector;
}


struct VectorR VectorR::operator *(const UFLOAT &Q) {
	VectorR Final_vector;
	UINT16 module = sqrt(pow(this->x,2) + pow(this->y,2));
	module *= Q;

	UFLOAT angle;
	if(this->x == 0)
		angle = 0;
	else
		angle = atan(this->y/this->x);
	
	Final_vector.x = (UFLOAT) module * cos(angle);
	Final_vector.y = (UFLOAT) module * sin(angle);

	return Final_vector;
}

struct VectorR VectorR::mpow(const UFLOAT &E) {
 	VectorR Final_vector;

	UFLOAT module = sqrt(pow(this->x,2) + pow(this->y,2));
	module = pow(module,E);

	UFLOAT angle;
	if(this->x == 0)
		angle = 0;
	else
		angle = atan((UFLOAT) this->y/(UFLOAT) this->x);
	
	Final_vector.x = (UFLOAT) module * cos(angle);
	Final_vector.y = (UFLOAT) module * sin(angle);

	return Final_vector;

}

UFLOAT VectorR::module() {
	return sqrt(pow(this->x,2)+pow(this->y,2));
}


