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
	VectorR rtr;
	rtr.x = this->x * Q;
	rtr.y = this->y * Q;
	return rtr;

	/*VectorR Final_vector;
	UFLOAT module = sqrt(pow(this->x,2) + pow(this->y,2));
	module *= Q;

	UFLOAT angle;
	if(this->x == 0)
		angle = 0;
	else
		angle = atan(this->y/this->x);

	if(module < 0) {
		module = -module;
		angle += 3.1415926535;
	}	

	Final_vector.x = (UFLOAT) module * cos(angle);
	Final_vector.y = (UFLOAT) module * sin(angle);

	if(this->x < 0) Final_vector.x = -Final_vector.x;
	if(this->y < 0) Final_vector.y = -Final_vector.y;

	return Final_vector;*/
}

struct VectorR VectorR::mpow(const UFLOAT &E) {
 	VectorR Final_vector;

	UFLOAT module = sqrt(pow(this->x,2) + pow(this->y,2));
	if(module != 0)
		module = pow(module,E);

	UFLOAT angle;
	if(this->x == 0)
		angle = 0;
	else
		angle = atan((UFLOAT) fabs(this->y)/(UFLOAT) fabs(this->x));

	Final_vector.x = (UFLOAT) module * cos(angle);
	Final_vector.y = (UFLOAT) module * sin(angle);

	if(this->x < 0) Final_vector.x = -Final_vector.x;
	if(this->y < 0) Final_vector.y = -Final_vector.y;

	return Final_vector;

}

struct VectorR VectorR::sum_angle(const UFLOAT &A) {
	VectorR rtr;

	UFLOAT module = sqrt(pow(this->x,2) + pow(this->y,2));

	UFLOAT angle;
	if(this->x == 0)
		this->x = 0.001;

	angle = atan((UFLOAT) this->y/(UFLOAT) this->x);
	angle += A;
	if((this->y <= 0 && this->x < 0))
		angle += 3.1415926535;
	if((this->y > 0 && this->x < 0))
		angle -= 3.1415926535;

	rtr.x = (UFLOAT) module * cos(angle);
	rtr.y = (UFLOAT) module * sin(angle);

	return rtr;
}

UFLOAT VectorR::module() {
	return sqrt(pow(this->x,2) + pow(this->y,2));
}

struct Point VectorR::deslocate_point(struct Point position) {
	position.x += this->x;
	position.y += this->y;

	return position;
}

UFLOAT VectorR::calculateAngle(VectorR V) {

	if(this->module() == 0 || V.module() == 0)
		return 0;
	
	return acos(((this->x * V.x) + (this->y * V.y))/(this->module() * V.module()));

}
	

struct VectorR VectorR::normalize(){
	struct VectorR rtr;
	UFLOAT module = this->module();
	rtr.x = this->x/module;
	rtr.y = this->y/module;

	return rtr;
}
	
