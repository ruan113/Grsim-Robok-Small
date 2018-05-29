#include "Movement.h";

void Movement::command(bool yellow, int id, double wheel1, double wheel2, double wheel3, double wheel4, double kickspeedx, double kickspeedz) {
    printf("Comando\n");

    /** Códigos do mainwindow.cpp do GrSim **/
    grSim_Packet packetGRSim;

    packetGRSim.mutable_commands()->set_isteamyellow(yellow);
    packetGRSim.mutable_commands()->set_timestamp(0.0);
    grSim_Robot_Command* command = packetGRSim.mutable_commands()->add_robot_commands();
    command->set_id(id);

    command->set_wheelsspeed(true);
    command->set_wheel1(wheel1);
    command->set_wheel2(wheel2);
    command->set_wheel3(wheel3);
    command->set_wheel4(wheel4);
    command->set_veltangent(0);
    command->set_velnormal(0);
    command->set_velangular(0);

    command->set_kickspeedx(kickspeedx);
    command->set_kickspeedz(kickspeedz);
    command->set_spinner(false);

    QUdpSocket *_socket = new QUdpSocket();
    quint16 UdpPort = 20011;
    QHostAddress *UdpNet_address = new QHostAddress(QString("224.5.23.2"));
    QNetworkInterface *UdpNet_interface = new QNetworkInterface(QNetworkInterface::interfaceFromName(QString("")));

    QByteArray dgram;
    dgram.resize(packetGRSim.ByteSize());
    packetGRSim.SerializeToArray(dgram.data(), dgram.size());
    _socket->writeDatagram(dgram, *UdpNet_address, UdpPort);
    /** Fim **/
}

void Movement::MoverPara(double x, double y, float rRotation, double rX, double rY, bool rColor, int rId) {
    printf("movendo\n");

    // Declara variáveis.
    float k, Theta, Angulo, Dist, vr, vl, ModTheta;
    // Calcula a distância entre o robo e o ponto desejado.
    Dist = sqrt((x - rX)*(x - rX) + (y - rY)*(y - rY));

    // Calcula quantos graus o robô deve girar para
    // ficar em direção ao ponto desejado.
    Angulo = (180 / M_PI) * atan2(y - rY, x - rX);
    Theta = Angulo - (rRotation * (180 / M_PI));

    // Ajusta o ângulo.
    while (Theta > 180) Theta -= 360;
    while (Theta < -180) Theta += 360;
    // ModTheta = |theta|.
    ModTheta = fabs(Theta);

    // Determina a velocidade de rotação
    // de acordo com o módulo do ângulo
    // que o robô precisa girar.
    // OBS: Esses valores podem ser alterados para
    // alterar a velocidade de rotação
    // do robô enquanto ele vai de encontro ao ponto (x,y).
    if (ModTheta > 100)
        k = 0.50 * VELOCIDADEMAXIMA;
    else if (ModTheta > 90)
        k = 0.35 * VELOCIDADEMAXIMA;
    else if (ModTheta > 50)
        k = 0.20 * VELOCIDADEMAXIMA;
    else if (ModTheta > 20)
        k = 0.15 * VELOCIDADEMAXIMA;
    else if (ModTheta >= 1)
        k = 0.1 * VELOCIDADEMAXIMA;
    else
        k = 0;
    // Define o valor da velocidade para a roda esquerda e direita.
    // A velocidade diminui conforme o jogador se aproxima do alvo e
    // a rotação do robô diminui conforme o ângulo diminui.
    if (Theta > 0) {
        vl = VELOCIDADEMAXIMA * (1.0 - exp(-Dist / 20));
        vr = (VELOCIDADEMAXIMA - 2 * k)*(1.0 - exp(-Dist / 20));
    } else {
        vl = (VELOCIDADEMAXIMA - 2 * k)*(1.0 - exp(-Dist / 20));
        vr = VELOCIDADEMAXIMA * (1.0 - exp(-Dist / 20));
    }

    command(rColor, rId, -vr, -vr, vl, vl, 0, 0);
}
