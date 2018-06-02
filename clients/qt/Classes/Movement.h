//Bibliotecas Grsim
#include "grSim_Packet.pb.h"
#include "grSim_Commands.pb.h"
#include "grSim_Replacement.pb.h"
#include "messages_robocup_ssl_wrapper.pb.h"
#include "messages_robocup_ssl_geometry.pb.h"
#include "messages_robocup_ssl_detection.pb.h"

#include <QtNetwork>
#include <QUdpSocket>
#include <math.h>
#include <QThread>

#define VELOCIDADEMAXIMA 50

class Movement{

  public:
    void command(bool yellow, int id, double wheel1, double wheel2, double wheel3, double wheel4, double kickspeedx, double kickspeedz);
    void MoverPara(double x, double y, float rRotation, double rX, double rY, bool rColor, int rId);

};
