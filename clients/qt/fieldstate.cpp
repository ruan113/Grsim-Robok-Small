#include "fieldstate.h"
#include <iostream>

#define BlueTeamStatusPort 30011
#define YellowTeamStatusPort 30012
#define MessageCount 4

Fieldstate::Fieldstate(){

}

void Fieldstate::fieldUpdate(SSL_DetectionFrame* detection, int num){

    for(int i = 0;i < detection->balls_size();i++){
        SSL_DetectionBall auxBall = detection->balls(i);

        this->ball.confidence = auxBall.confidence();
        this->ball.position.x = auxBall.x();
        this->ball.position.y = auxBall.y();
    }
    //std::printf("Leitura da bola OK\n");
    if(num == 1){
        for(int i = 0;i < detection->robots_yellow_size();i++){
            SSL_DetectionRobot yellow = detection->robots_yellow(i);

            this->yellow[i].id = yellow.robot_id();
            this->yellow[i].orientation = yellow.orientation();
            this->yellow[i].position.x = yellow.x();
            this->yellow[i].position.y = yellow.y();
        }
        //std::printf("Leitura do time Amarelo OK\n");
    }else{
        for(int i = 0;i < detection->robots_blue_size();i++){
            SSL_DetectionRobot blue = detection->robots_blue(i);

            this->blue[i].id = blue.robot_id();
            this->blue[i].orientation = blue.orientation();
            this->blue[i].position.x = blue.x();
            this->blue[i].position.y = blue.y();
        }
        //std::printf("Leitura do time Azul OK\n");
    }
}

