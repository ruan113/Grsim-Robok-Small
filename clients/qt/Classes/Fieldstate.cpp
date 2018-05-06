#include "Fieldstate.h"
#include <iostream>

#define BlueTeamStatusPort 30011
#define YellowTeamStatusPort 30012
#define MessageCount 4

Fieldstate::Fieldstate(){

    this->ball = Ball();//Inicializa bola

    //Seta as posições do gol
    this->ally_goal = {-3200,0};
    this->enemy_goal = {3200,0};

    //Inicializa os robos do time amarelo com os valores iniciais
    for(int i=0; i<6; i++) {
        this->yellow[i] = Robot();
    }

    //Seta as constantes do time azul ao mesmo tempo q inicializa suas constantes
    for(int i=0; i<6; i++) {
        this->blue[i] = Robot();
        this->blue[i].Q_pivot = 0.02;
        this->blue[i].Q_ball_0 = 25;
        this->blue[i].Q_ball_2 = -25;
        this->blue[i].Q_robot = -1;
        this->blue[i].Q_goal = 25;
        this->blue[i].Q_adjust = 2;
        this->blue[i].e_ball_0 = 0;
        this->blue[i].e_ball_2 = 0;
        this->blue[i].e_robot = -0.3;
        this->blue[i].e_goal = 0;
        this->blue[i].e_adjust = 0.5;
        this->blue[i].K_adjust = -500;
    }

    //Seta os pontos pivos dos robos do time azul
    //Pontos pivos são os pontos de sua função, por exemplo:
    //O zagueiro irá ficar em tal posição, esta será seu ponto pivo
    this->blue[0].pivot = {-2580,0};
    this->blue[1].pivot = {-1300,1000};
    this->blue[2].pivot = {-1300,-1000};
    this->blue[3].pivot = {0,0};
    this->blue[4].pivot = {1300,1000};
    this->blue[5].pivot = {1300,-1000};

    //Não faço ideia
    this->blue[0].pivot_stop = {-2000,0};
    this->blue[1].pivot_stop = {0,0};
    this->blue[2].pivot_stop = {0,0};
    this->blue[3].pivot_stop = {0,0};
    this->blue[4].pivot_stop = {0,0};
    this->blue[5].pivot_stop = {0,0};

    //Não faço ideia
    this->blue[0].e_pivot = 0.5;
    this->blue[1].e_pivot = 1.1;
    this->blue[2].e_pivot = 1.1;
    this->blue[3].e_pivot = 1.0;
    this->blue[4].e_pivot = 0.9;
    this->blue[5].e_pivot = 0.9;

}

//Função responsável por atualizar as posições dos robos(TODOS)
void Fieldstate::fieldUpdate(SSL_DetectionFrame* detection, int num){

    //Atualiza a posição da bola
    for(int i = 0;i < detection->balls_size();i++){
        SSL_DetectionBall auxBall = detection->balls(i);

        this->ball.mensure_confidence = auxBall.confidence();
        this->ball.position.x = auxBall.x();
        this->ball.position.y = auxBall.y();
    }

    //Checa se o pacote se refere ao time azul ou amarelo
    if(num == 1){
        //Atualiza a posição dos robos do time Amarelo
        for(int i = 0;i < detection->robots_yellow_size();i++){
            SSL_DetectionRobot yellow = detection->robots_yellow(i);

            this->yellow[i].id = yellow.robot_id();
            this->yellow[i].orientation = yellow.orientation();
            this->yellow[i].position.x = yellow.x();
            this->yellow[i].position.y = yellow.y();
        }
    }else{
        //Atualiza a posição dos robos do time Azul
        for(int i = 0;i < detection->robots_blue_size();i++){
            SSL_DetectionRobot blue = detection->robots_blue(i);

            this->blue[i].id = blue.robot_id();
            this->blue[i].orientation = blue.orientation();
            this->blue[i].position.x = blue.x();
            this->blue[i].position.y = blue.y();
        }
    }
}
	
