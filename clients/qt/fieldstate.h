#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <QtNetwork>
#include "grSim_Packet.pb.h"
#include "messages_robocup_ssl_detection.pb.h"

struct Position{
    float x;
    float y;
};

struct Robot{
    unsigned int id;
    Position position;
    float orientation;
};

struct Ball{
    float confidence;
    Position position;
};

class Fieldstate{

public:   
    Fieldstate();
    ~Fieldstate();
    void fieldUpdate(SSL_DetectionFrame*, int);

public:
    Robot blue[6];
    Robot yellow[6];
    Ball ball;

};

typedef struct Position Position;
typedef struct Robot Robot;
typedef struct Ball Ball;
class Fieldstate;
