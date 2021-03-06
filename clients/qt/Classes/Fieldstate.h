#ifndef FIELDSTATE_H
#define FIELDSTATE_H

#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include "Ball.h"
#include "Robot.h"

#include "messages_robocup_ssl_wrapper.pb.h"
#include "messages_robocup_ssl_geometry.pb.h"
#include "messages_robocup_ssl_detection.pb.h"

#include "../../../include/net/robocup_ssl_client.h"

//Possiveis estados
enum State {
    STOP,/*Parar*/
    KICKOFF,/*Chutar*/
    RUN/*Correr*/
};

class Fieldstate{

public:
    Fieldstate();
    ~Fieldstate();

    void fieldUpdate();

    RoboCupSSLClient *client;

    int blue_n;
    Robot blue[6];//Vetor de robos azuis
    int yellow_n;
    Robot yellow[6];//Vetor de robos Amarelos

    Ball ball;//Bola

    Point enemy_goal;//Coordenadas do gol inimigo
    Point ally_goal;//Coordenadas do gol aliado

    State match_state;//Estado da partida
};

#endif
