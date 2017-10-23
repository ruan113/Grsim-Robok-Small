#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Classes/config.h"
#include "Classes/Fieldstate.h"
#include "Classes/Geometrics.h"

#include "grSim_Packet.pb.h"
#include "grSim_Commands.pb.h"
#include "grSim_Replacement.pb.h"

#include <string>
#include <cmath>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

using namespace std;

class Movement {
public:
    Movement();
    void sendCommands(Fieldstate *fs);

protected:
    QUdpSocket * _socket;
    quint16 _port;
    QHostAddress * _net_address;
    QNetworkInterface * _net_interface;
};

#endif
