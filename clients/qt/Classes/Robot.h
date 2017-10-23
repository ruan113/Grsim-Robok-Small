#ifndef ROBOT_H
#define ROBOT_H

#define SEARCHING_BALL 0
#define ALIGN_FAR 1
#define ALIGN_BALL 2
#define SEARCHING_GOAL 3

#include <cmath>
#include <cstdio>
#include "config.h"
#include "Geometrics.h"
#include "Fieldstate.h"

class Robot {
public:
    Robot();
    void calculateMovement(void *fs_i);
    void strategyRun(void *fs_i);
    void strategyKickoff(void *fs_i);
    void strategyStop(void *fs_i);
    void calculateWheels();

    UINT8 id;
    Point adjust;
    Point position;
    Point pivot;
    Point pivot_stop;
    UFLOAT orientation;
    UFLOAT Q_pivot;
    UFLOAT Q_ball_0;
    UFLOAT Q_ball_2;
    UFLOAT Q_robot;
    UFLOAT Q_goal;
    UFLOAT Q_adjust;
    UFLOAT e_pivot;
    UFLOAT e_ball_0;
    UFLOAT e_ball_2;
    UFLOAT e_robot;
    UFLOAT e_goal;
    UFLOAT e_adjust;
    UFLOAT K_adjust;

    UINT8 state;

    VectorR speed;
    INT8 wheel_speed[4];
};
#endif
