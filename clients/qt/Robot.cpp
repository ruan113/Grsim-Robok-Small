#include "Robot.h"

Robot::Robot() {
	this->id = 0;
	this->position.x = 0;
	this->position.y = 0;
	this->orientation = 0;
}

void Robot::calculateMovement(void *fs_i) {
	Fieldstate *fs = (Fieldstate *) fs_i;
	
	VectorR final_vector = {50,0};

	/*VectorR Distance2Pivo = this->position.PointDistance(this->pivot);
	Distance2Pivo = Distance2Pivo.mpow(this->e_pivot);
	Distance2Pivo = Distance2Pivo * this->Q_pivot;
	final_vector  = final_vector + Distance2Pivo;

	for(int i = 0; i < 6; i++){
		VectorR Distance2robot = this->position.PointDistance(fs->blue[i].position);
		Distance2robot = Distance2robot.mpow(this->e_robot);
		Distance2robot = Distance2robot * this->Q_robot;
		final_vector   = final_vector + Distance2robot;
	}

	printf("Final %f %f\n", final_vector.x, final_vector.y);

	VectorR Distance2ball = this->position.PointDistance(fs->ball.position);
	Distance2ball = Distance2ball.mpow(this->e_ball);
	Distance2ball = Distance2ball * this->Q_ball;
	final_vector  = final_vector + Distance2ball;	
	
	for(int i = 0; i < 6; i++){
		VectorR Distance2robot = this->position.PointDistance(fs->yellow[i].position);
		Distance2robot = Distance2robot.mpow(this->e_robot);
		Distance2robot = Distance2robot * this->Q_robot;
		final_vector   = final_vector + Distance2robot;
	}*/

	this->speed = final_vector;
}

void Robot::calculateWheels() {
	this->wheel_speed[0] = (INT8) (-(this->speed.x - this->speed.y)/2.828427125);
	this->wheel_speed[1] = (INT8) ((this->speed.x + this->speed.y)/2.828427125);
	this->wheel_speed[2] = (INT8) (this->wheel_speed[0]);
	this->wheel_speed[3] = (INT8) (this->wheel_speed[1]);

	printf("%d %d %d %d\n", wheel_speed[0], wheel_speed[1], wheel_speed[2], wheel_speed[3]);
    
 	//vi = (velocidade_angular * RAIO)/4;
	//retorno.v1 += vi;
	//retorno.v2 += vi;
	//retorno.v3 += vi;
	//retorno.v4 += vi;
}
