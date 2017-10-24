#include "Robot.h"
#include "Fieldstate.h"

Robot::Robot() {
    this->id = 0;
    this->position.x = 0;
    this->position.y = 0;
    this->orientation = 0;
}

void Robot::calculateMovement(void *fs_i) {
    Fieldstate *fs = (Fieldstate *) fs_i;

    printf("Estado da partida: %d\n", fs->match_state);

    //switch(fs->match_state) {
    //case KICKOFF:
    //	this->strategyKickoff(fs_i);
    //	break;
    //case RUN:
    this->strategyRun(fs_i);
    //	break;
    //case STOP:
    //default:
    //	this->strategyStop(fs_i);
    //	break;
    //}
}

void Robot::strategyKickoff(void *fs_i) {
    VectorR final_vector;

    //printf("[Kickoff] Robo %d: %d,x: %f, y:%f\n", this->id, this->state,this->position.x,this->position.y);

    UINT8  e = 0;
    UFLOAT Q = 40;

    Point kickstart = {-100, 0};

    VectorR Distance2Pivo;
    Distance2Pivo = this->position.PointDistance(kickstart);
    Distance2Pivo = Distance2Pivo.mpow(e);
    Distance2Pivo = Distance2Pivo * Q;
    final_vector  = final_vector + Distance2Pivo;

    this->speed = final_vector;
}

void Robot::strategyStop(void *fs_i) {
    Fieldstate *fs = (Fieldstate *) fs_i;

    VectorR final_vector = {0,0};

    //printf("[Stop] Robo %d: %d,x: %f, y:%f %f %f\n", this->id, this->state,this->position.x,this->position.y,fs->ball.position.x,fs->ball.position.y);

    /*UINT8  e = 0;
    UFLOAT Q = 40;

    VectorR Distance2Pivo;
    Distance2Pivo = this->position.PointDistance(this->pivot_stop);
    Distance2Pivo = Distance2Pivo.mpow(e);
    Distance2Pivo = Distance2Pivo * Q;
    final_vector  = final_vector + Distance2Pivo;

    //printf("[Stop] Final %f %f", final_vector.x, final_vector.y);*/

    this->speed = final_vector;
}

void Robot::strategyRun(void *fs_i) {
    Fieldstate *fs = (Fieldstate *) fs_i;
    VectorR final_vector = {0,0};

    // CÁLCULOS PARA TODOS OS ESTADOS
    for(int i = 0; i < 6; i++){
        VectorR Distance2robot = this->position.PointDistance(fs->blue[i].position);
        Distance2robot = Distance2robot.mpow(this->e_robot);
        Distance2robot = Distance2robot * this->Q_robot;
        final_vector   = final_vector + Distance2robot;
    }

    for(int i = 0; i < 6; i++){
        VectorR Distance2robot = this->position.PointDistance(fs->yellow[i].position);
        Distance2robot = Distance2robot.mpow(this->e_robot);
        Distance2robot = Distance2robot * this->Q_robot;
        final_vector   = final_vector + Distance2robot;
    }

    // ANALIZANDO O ESTADO
    VectorR Distance2goal = this->position.PointDistance(fs->enemy_goal);
    VectorR Ball2enemy_goal = fs->ball.position.PointDistance(fs->enemy_goal);
    VectorR Distance2ball = this->position.PointDistance(fs->ball.position);

    this->state = 0;
    if(Distance2ball.module() < 300)
        BITSET(this->state,1);
    else
        BITCLR(this->state,1);

    if(Distance2goal.calculateAngle(Ball2enemy_goal) < 0.04 && Distance2goal.module() > Ball2enemy_goal.module())
        BITSET(this->state,0);
    else
        BITCLR(this->state,0);

    //printf("Robo %d: %d,x: %f, y:%f ,DRG: %f, A: %f DBG: %f\n", this->id, this->state,this->position.x,this->position.y, Distance2goal.module(), Distance2goal.calculateAngle(Ball2enemy_goal),Ball2enemy_goal.module());

    VectorR Distance2back;
    VectorR Distance2adjust;
    VectorR Distance2Pivo;
    Point pointDeslocate;

    // CONSTANTES DE ACORDO COM O ESTADO
    switch(this->state) {
    case SEARCHING_BALL:
    case ALIGN_FAR:
        Distance2Pivo = this->position.PointDistance(this->pivot);
        Distance2Pivo = Distance2Pivo.mpow(this->e_pivot);
        Distance2Pivo = Distance2Pivo * this->Q_pivot;
        final_vector  = final_vector + Distance2Pivo;

        Distance2ball = Distance2ball.mpow(this->e_ball_0);
        Distance2ball = Distance2ball * this->Q_ball_0;
        final_vector = final_vector + Distance2ball;
        break;

    case ALIGN_BALL:
        Distance2ball = Distance2ball.mpow(this->e_ball_2);
        Distance2ball = Distance2ball * this->Q_ball_2;
        final_vector  = final_vector + Distance2ball;

        Distance2back = Ball2enemy_goal.normalize()*this->K_adjust;
        pointDeslocate = Distance2back.deslocate_point(fs->ball.position);
        Distance2adjust = this->position.PointDistance(pointDeslocate);
        Distance2adjust = Distance2adjust.mpow(this->e_adjust);
        Distance2adjust = Distance2adjust * this->Q_adjust;
        final_vector  = final_vector + Distance2adjust;
        break;

    case SEARCHING_GOAL:
        Distance2goal = Distance2goal.mpow(this->e_goal);
        Distance2goal = Distance2goal * this->Q_goal;
        final_vector  = final_vector + Distance2goal;

        Distance2ball = Distance2ball.mpow(this->e_ball_0);
        Distance2ball = Distance2ball * this->Q_ball_0;
        final_vector = final_vector + Distance2ball;

        break;
    }

    // SET FINAL
    this->speed = final_vector;
}

void Robot::calculateWheels() {
    this->wheel_speed[0] = (INT8) (-(this->speed.x - this->speed.y)/2.828427125);
    this->wheel_speed[1] = (INT8) ((this->speed.x + this->speed.y)/2.828427125);
    this->wheel_speed[2] = (INT8) (this->wheel_speed[0]);
    this->wheel_speed[3] = (INT8) (this->wheel_speed[1]);


    //vi = (velocidade_angular * RAIO)/4;
    //retorno.v1 += vi;
    //retorno.v2 += vi;
    //retorno.v3 += vi;
    //retorno.v4 += vi;
}
