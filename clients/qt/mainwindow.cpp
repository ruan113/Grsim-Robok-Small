#include "mainwindow.h"
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent),
    udpsocket(this)
{
    //Titulo da tela
    this->setWindowTitle(QString("Robok Small Simulator - v1.0"));

    //----------------Inicialização dos componentes---------//

    //Tipo de Layout da tela(MainWindow)
    QGridLayout* layout = new QGridLayout(this);

    //Caixas de text para edição
    edtIp = new QLineEdit("127.0.0.1", this);
    edtPort = new QLineEdit("20011", this);
    edtId = new QLineEdit("0", this);
    edtVx = new QLineEdit("0", this);
    edtVy = new QLineEdit("0", this);
    edtW  = new QLineEdit("0", this);
    edtV1 = new QLineEdit("0", this);
    edtV2 = new QLineEdit("0", this);
    edtV3 = new QLineEdit("0", this);
    edtV4 = new QLineEdit("0", this);
    edtChip = new QLineEdit("0", this);
    edtKick = new QLineEdit("0", this);

    //Labels
    lblIp = new QLabel("Simulator Address", this);
    lblPort = new QLabel("Simulator Port", this);
    lblId = new QLabel("Id", this);
    lblVx = new QLabel("Velocity X (m/s)", this);
    lblVy = new QLabel("Velocity Y (m/s)", this);
    lblW  = new QLabel("Velocity W (rad/s)", this);
    lblV1 = new QLabel("Wheel1 (rad/s)", this);
    lblV2 = new QLabel("Wheel2 (rad/s)", this);
    lblV3 = new QLabel("Wheel3 (rad/s)", this);
    lblV4 = new QLabel("Wheel4 (rad/s)", this);
    lblChip = new QLabel("Chip (m/s)", this);
    lblKick = new QLabel("Kick (m/s)", this);

    //ComboBox
    cmbTeam = new QComboBox(this);
    cmbTeam->addItem("Yellow");
    cmbTeam->addItem("Blue");

    //TextArea
    txtInfo = new QTextEdit(this);

    //CheckBox
    chkVel = new QCheckBox("Send Velocity? (or wheels)", this);
    chkSpin = new QCheckBox("Spin", this);

    //Botões
    btnSend = new QPushButton("Send", this);
    btnReset = new QPushButton("Reset", this);
    btnConnect = new QPushButton("Connect", this);

    //Mostra as informações dos robos na tela do cliente (debug mode)
    txtInfo->setReadOnly(true);//Seta permissão semente para leitura
    txtInfo->setHtml("Robo 1: 0\nRobo 2: 0\nRobo 3: 0\nRobo 4: 0\nRobo 5: 0\nRobo 6: 0");
    txtInfo->setFixedHeight(300);

    //FieldState
    field = new Fieldstate();
    //Movimentação
    moviment = new Movement();

    //Aloca Socket para pegar informações dos robos
    this->SSL_Client = new RoboCupSSLClient(10020,"224.5.23.2","");

    //Estabelece a conexão com o servidor
    if(!this->SSL_Client->open()){
        std::printf("Falha ao abrir a conexão com o servidor!\n");
        return;
    }

    //---------------------Adição dos componentes na tela---------------------//

    //obs: Ao meu ver ele funciona assim:
    //layout->addWidget(componente, linha, coluna, tamanho(y), comprimento(x));

    layout->addWidget(lblIp, 1, 1, 1, 1);layout->addWidget(edtIp, 1, 2, 1, 1);
    layout->addWidget(lblPort, 1, 3, 1, 1);layout->addWidget(edtPort, 1, 4, 1, 1);
    layout->addWidget(lblId, 2, 1, 1, 1);layout->addWidget(edtId, 2, 2, 1, 1);
    layout->addWidget(cmbTeam, 2, 3, 1, 2);
    layout->addWidget(lblVx, 3, 1, 1, 1);layout->addWidget(edtVx, 3, 2, 1, 1);
    layout->addWidget(lblVy, 4, 1, 1, 1);layout->addWidget(edtVy, 4, 2, 1, 1);
    layout->addWidget(lblW, 5, 1, 1, 1);layout->addWidget(edtW, 5, 2, 1, 1);
    layout->addWidget(chkVel, 6, 1, 1, 1);layout->addWidget(edtKick, 6, 2, 1, 1);
    layout->addWidget(lblV1, 3, 3, 1, 1);layout->addWidget(edtV1, 3, 4, 1, 1);
    layout->addWidget(lblV2, 4, 3, 1, 1);layout->addWidget(edtV2, 4, 4, 1, 1);
    layout->addWidget(lblV3, 5, 3, 1, 1);layout->addWidget(edtV3, 5, 4, 1, 1);
    layout->addWidget(lblV4, 6, 3, 1, 1);layout->addWidget(edtV4, 6, 4, 1, 1);
    layout->addWidget(lblChip, 7, 1, 1, 1);layout->addWidget(edtChip, 7, 2, 1, 1);
    layout->addWidget(lblKick, 7, 3, 1, 1);layout->addWidget(edtKick, 7, 4, 1, 1);
    layout->addWidget(chkSpin, 8, 1, 1, 4);layout->addWidget(btnConnect, 9, 1, 1, 2);
    layout->addWidget(btnSend, 9, 3, 1, 1);layout->addWidget(btnReset, 9, 4, 1, 1);
    layout->addWidget(txtInfo, 10, 1, 4, 4);

    //Inicializa Timer
    timer = new QTimer (this);
    timer->setInterval(20);//Seta seu intervalo = 20 milesegundos

    //---------------Conecção dos Slots com seus respectivos Sinais----------//

    connect(edtIp, SIGNAL(textChanged(QString)), this, SLOT(disconnectUdp()));
    connect(edtPort, SIGNAL(textChanged(QString)), this, SLOT(disconnectUdp()));
    connect(timer, SIGNAL(timeout()), this, SLOT(sendPacket()));
    connect(btnConnect, SIGNAL(clicked()), this, SLOT(reconnectUdp()));
    connect(btnSend, SIGNAL(clicked()), this, SLOT(sendBtnClicked()));
    connect(btnReset, SIGNAL(clicked()), this, SLOT(resetBtnClicked()));

    btnSend->setDisabled(true);//Estado inicial do botão como desativado
    chkVel->setChecked(true);//Estado inicial como "Marcado/Selecionado"
    sending = false;//Estado inicial é falso
    reseting = false;//Estado inicial é falso
}

MainWindow::~MainWindow()
{
    this->SSL_Client->close();
}

void MainWindow::disconnectUdp()
{
    udpsocket.close();
    sending = false;
    btnSend->setText("Send");
    btnSend->setDisabled(true);
}

void MainWindow::sendBtnClicked()
{
    sending = !sending;
    if (!sending)
    {
        timer->stop();
        btnSend->setText("Send");
    }
    else {
        timer->start();
        btnSend->setText("Pause");
    }
}

void MainWindow::resetBtnClicked()
{
    reseting = true;
    edtVx->setText("0");
    edtVy->setText("0");
    edtW->setText("0");
    edtV1->setText("0");
    edtV2->setText("0");
    edtV3->setText("0");
    edtV4->setText("0");
    edtChip->setText("0");
    edtKick->setText("0");
    chkVel->setChecked(true);
    chkSpin->setChecked(false);
}


void MainWindow::reconnectUdp()
{
    _addr = edtIp->text();
    _port = edtPort->text().toUShort();
    btnSend->setDisabled(false);
}

void MainWindow::sendPacket()
{
    //Se o programa esta resentando
    if (reseting)
    {
        sendBtnClicked();//Atualiza o botão send
        reseting = false;//Seta como falso o estado de reset
    }

    grSim_Packet packet;//Cria uma variavel para armazenar os valores do pacote
    bool yellow = false;//Variavel que verificará se o robo é do time amarelo ou não
    if (cmbTeam->currentText()=="Yellow") yellow = true;
    packet.mutable_commands()->set_isteamyellow(yellow);
    packet.mutable_commands()->set_timestamp(0.0);
    grSim_Robot_Command* command = packet.mutable_commands()->add_robot_commands();
    command->set_id(edtId->text().toInt());

    command->set_wheelsspeed(!chkVel->isChecked());
    command->set_wheel1(edtV1->text().toDouble());
    command->set_wheel2(edtV2->text().toDouble());
    command->set_wheel3(edtV3->text().toDouble());
    command->set_wheel4(edtV4->text().toDouble());
    command->set_veltangent(edtVx->text().toDouble());
    command->set_velnormal(edtVy->text().toDouble());
    command->set_velangular(edtW->text().toDouble());

    command->set_kickspeedx(edtKick->text().toDouble());
    command->set_kickspeedz(edtChip->text().toDouble());
    command->set_spinner(chkSpin->isChecked());

    QByteArray dgram;
    dgram.resize(packet.ByteSize());
    packet.SerializeToArray(dgram.data(), dgram.size());
    udpsocket.writeDatagram(dgram, _addr, _port);

}

void MainWindow::updateFieldState(){

    int numBlue,numYellow;//Variaveis que armazenam o tamanho dos vetores de robos no diagrama

    this->SSL_Client->changePort(30011);//Muda a porta para a leitura dos dados dos robos Azuis

    //A classe wrapper é responsável por englobar todas as outras classes em uma só,
    //por isso usamos ela aqui!
    SSL_WrapperPacket robotPacket;//Aloca uma variavel para receber um pacote com as informações

    //Checamos se o pacote conseguiu ser lido e transferido para a variavel
    if(!this->SSL_Client->receive(robotPacket)){
        std::printf("Erro ao ler o datagrama!\n");
        return;
    }

    //Checa se este pacote possui uma classe Detection que é responsável por ter os dados
    //em relação a robos e a bola!
    if(robotPacket.has_detection()){
        SSL_DetectionFrame detection = robotPacket.detection();
        numBlue = detection.robots_blue_size();
        field->fieldUpdate(&detection, 0);//Atualiza o field com base nos robos azuis
    }

    this->SSL_Client->changePort(30012);//Muda a porta para a leitura dos dados dos robos Amarelos

    //Checamos se o pacote conseguiu ser lido e transferido para a variavel
    if(!this->SSL_Client->receive(robotPacket)){
        std::printf("Erro ao ler o datagrama!\n");
        return;
    }

    //Checa se este pacote possui uma classe Detection que é responsável por ter os dados
    //em relação a robos e a bola!
    if(robotPacket.has_detection()){
        SSL_DetectionFrame detection = robotPacket.detection();
        numYellow = detection.robots_yellow_size();
        field->fieldUpdate(&detection, 1);//Atualiza o field com base nos robos Amarelos
    }


    //Esta parte é referente a printar os valores na tela!
    QString output = "Confidence\tX\tY\n";

    output += QString::number(field->ball.mensure_confidence)+QString("\t")
            +QString::number(field->ball.position.x)+QString("\t")
            +QString::number(field->ball.position.y)+QString("\n\n");

    output += "ID\tOrientation\tX\tY\n";

    output += "Yellow Team: \n";
    for(int i = 0;i < numYellow;i++){

        output += QString::number(field->yellow[i].id)+QString("\t")
                +QString::number(field->yellow[i].orientation)+QString("\t")
                +QString::number(field->yellow[i].position.x)+QString("\t")
                +QString::number(field->yellow[i].position.y)+QString("\n");

    }
    output += "Blue Team: \n";
    for(int i = 0;i < numBlue;i++){

        output += QString::number(field->blue[i].id)+QString("\t")
                +QString::number(field->blue[i].orientation)+QString("\t")
                +QString::number(field->blue[i].position.x)+QString("\t")
                +QString::number(field->blue[i].position.y)+QString("\n");

    }

    txtInfo->setText(output);

    this->executarPrograma();
}

void MainWindow::executarPrograma(){
    for(int i=0; i<6; i++) {
        field->blue[i].calculateMovement(field);
        field->blue[i].calculateWheels();
    }

    moviment->sendCommands(this->field);
}
