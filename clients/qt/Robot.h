#ifndef ROBOT_H
#define ROBOT_H

#include <cmath>
#include <cstdio>
#include "config.h"
#include "Geometrics.h"

class Robot {
	public:
	Robot();
	void calculateMovement(void *fs);
	void calculateWheels();

	UINT8 id;
	Point position;
	UFLOAT orientation;
	UFLOAT Q_pivot;
	UFLOAT Q_ball;
	UFLOAT Q_robot;
	UFLOAT e_pivot;
	UFLOAT e_ball;
	UFLOAT e_robot;

	VectorR speed;
	INT8 wheel_speed[4];
	Point pivot;
};

#include "Fieldstate.h"
#endif
