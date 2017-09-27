#include <cstdio>
#include <vector>
#include <fstream>
#include "messages_robocup_ssl_detection.pb.h"
#include "grSim_Commands.pb.h"

typedef struct Robot Robot;
class Fieldstate;

struct Robot{
    unsigned int id;
    float x;
    float y;
    float orientation;
};

class Fieldstate{

public:
    void fieldUpdate(std::vector<Robot>*);

};
