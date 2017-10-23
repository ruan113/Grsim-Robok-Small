#include "Movement.h"

using namespace std;

Movement::Movement(){
    _socket = new QUdpSocket();
    _port = 20011;
    _net_address = new QHostAddress(QString("224.5.23.2"));
    _net_interface = new QNetworkInterface(QNetworkInterface::interfaceFromName(QString("")));
}

void Movement::sendCommands(Fieldstate *fs) {
    VectorR real_speed = fs->blue[0].speed;
    real_speed = real_speed.sum_angle(-fs->blue[0].orientation);

    UFLOAT v1 = - real_speed.x * sin(0.52) - real_speed.y * cos(0.52);
    UFLOAT v2 = - real_speed.x * sin(0.79) + real_speed.y * cos(0.79);
    UFLOAT v3 = - real_speed.x * sin(0.52) + real_speed.y * cos(0.52);
    UFLOAT v4 = - real_speed.x * sin(0.79) - real_speed.y * cos(0.79);

    UINT8 sigv1 = 1;
    UINT8 sigv2 = 1;
    UINT8 sigv3 = 0;
    UINT8 sigv4 = 0;

    if(v1 < 0) { v1 = -v1; sigv1 = 0; }
    if(v2 < 0) { v2 = -v2; sigv2 = 0; }
    if(v3 < 0) { v3 = -v3; sigv3 = 1; }
    if(v4 < 0) { v4 = -v4; sigv4 = 1; }

    char prot[100];
    sprintf(prot, "echo \"<0%d%02d%d%02d%d%02d%d%02d>\" > /dev/ttyACM0", sigv1, (int) v1, sigv2, (int) v2, sigv3, (int) v3, sigv4, (int) v4);
    printf("Prot: %s\n", prot);
    system(prot);

    grSim_Packet packet;
    packet.mutable_commands()->set_isteamyellow(false);
    packet.mutable_commands()->set_timestamp(0.0);

    for(int i=0; i<6; i++) {
        grSim_Robot_Command* command = packet.mutable_commands()->add_robot_commands();
        command->set_id(i);
        command->set_wheelsspeed(0);
        command->set_wheel1(0);
        command->set_wheel2(0);
        command->set_wheel3(0);
        command->set_wheel4(0);

        VectorR real_speed = fs->blue[i].speed;
        real_speed = real_speed.sum_angle(-fs->blue[i].orientation);
        command->set_veltangent(real_speed.x/100);
        command->set_velnormal(real_speed.y/100);

        command->set_velangular(0);
        command->set_kickspeedx(0);
        command->set_kickspeedz(0);
        command->set_spinner(0);
    }

    QByteArray dgram;
    dgram.resize(packet.ByteSize());
    packet.SerializeToArray(dgram.data(), dgram.size());
    _socket->writeDatagram(dgram, *_net_address, _port);
}
