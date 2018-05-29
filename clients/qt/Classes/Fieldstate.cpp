#include "Fieldstate.h"
#include <iostream>
using namespace std;

#define BlueTeamStatusPort 30011
#define YellowTeamStatusPort 30012
#define MessageCount 4


Fieldstate::Fieldstate(){

    client = new RoboCupSSLClient(10007,"224.5.23.2","");

    if(!client->open()){
        printf("Erro ao se conectar com a visao\n");
    }else{
        printf("Sucesso ao se conectar com a visao\n");
    }

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
void Fieldstate::fieldUpdate(){

    SSL_DetectionFrame detection;
    SSL_WrapperPacket package;

    //Checamos se o pacote conseguiu ser lido e transferido para a variavel
    if(!client->receive(package)){
        std::printf("Erro ao ler o datagrama!\n");
        return;
    }

    if(package.has_detection()){
        detection = package.detection();

        this->blue_n = detection.robots_blue_size();
        this->yellow_n = detection.robots_yellow_size();

        //Atualiza a posição da bola
        for(int i = 0;i < detection.balls_size();i++){
            SSL_DetectionBall auxBall = detection.balls(i);
            this->ball.mensure_confidence = auxBall.confidence();
            this->ball.position.x = auxBall.pixel_x();
            this->ball.position.y = auxBall.pixel_y();
        }

        //Atualiza a posição dos robos do time Amarelo
        for(int i = 0;i < detection.robots_yellow_size();i++){
            SSL_DetectionRobot yellow = detection.robots_yellow(i);

            this->yellow[yellow.robot_id()].id = yellow.robot_id();
            this->yellow[yellow.robot_id()].orientation = yellow.orientation();
            this->yellow[yellow.robot_id()].position.x = yellow.pixel_x();
            this->yellow[yellow.robot_id()].position.y = yellow.pixel_y();
        }

        //Atualiza a posição dos robos do time Azul
        for(int i = 0;i < detection.robots_blue_size();i++){
            SSL_DetectionRobot blue = detection.robots_blue(i);

            this->blue[blue.robot_id()].id = blue.robot_id();
            this->blue[blue.robot_id()].orientation = blue.orientation();
            this->blue[blue.robot_id()].position.x = blue.pixel_x();
            this->blue[blue.robot_id()].position.y = blue.pixel_y();
        }
    }
}
