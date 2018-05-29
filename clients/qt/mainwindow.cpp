#include "mainwindow.h"
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
{
    //Titulo da tela
    this->setWindowTitle(QString("Robok Small Simulator - v1.2"));

    //----------------Inicialização dos componentes---------//

    //Tipo de Layout da tela(MainWindow)
    QGridLayout* layout = new QGridLayout(this);

    //Caixas de text para edição
    edtIp = new QLineEdit("224.5.23.2", this);
    edtPort = new QLineEdit("10020", this);
    edtId = new QLineEdit("0", this);
    edtObjx = new QLineEdit("0", this);
    edtObjy = new QLineEdit("0", this);
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
    lblObjx = new QLabel("Objetivo X", this);
    lblObjy = new QLabel("Objetivo Y", this);
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

    //---------------------Adição dos componentes na tela---------------------//

    //obs: Ao meu ver ele funciona assim:
    //layout->addWidget(componente, linha, coluna, tamanho(y), comprimento(x));

    layout->addWidget(lblIp, 1, 1, 1, 1);layout->addWidget(edtIp, 1, 2, 1, 1);
    layout->addWidget(lblPort, 1, 3, 1, 1);layout->addWidget(edtPort, 1, 4, 1, 1);
    layout->addWidget(lblId, 2, 1, 1, 1);layout->addWidget(edtId, 2, 2, 1, 1);
    layout->addWidget(cmbTeam, 2, 3, 1, 2);
    layout->addWidget(lblObjx, 3, 1, 1, 1);layout->addWidget(edtObjx, 3, 2, 1, 1);
    layout->addWidget(lblObjy, 4, 1, 1, 1);layout->addWidget(edtObjy, 4, 2, 1, 1);
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
    timer->setInterval(120);//Seta seu intervalo = 20 milesegundos

    //---------------Conecção dos Slots com seus respectivos Sinais----------//

    connect(edtIp, SIGNAL(textChanged(QString)), this, SLOT(disconnectUdp()));
    connect(edtPort, SIGNAL(textChanged(QString)), this, SLOT(disconnectUdp()));
    connect(timer, SIGNAL(timeout()), this, SLOT(startProgram()));
    connect(btnConnect, SIGNAL(clicked()), this, SLOT(reconnectUdp()));
    connect(btnSend, SIGNAL(clicked()), this, SLOT(sendBtnClicked()));
    connect(btnReset, SIGNAL(clicked()), this, SLOT(resetBtnClicked()));

    btnSend->setDisabled(true);//Estado inicial do botão como desativado
    chkVel->setChecked(true);//Estado inicial como "Marcado/Selecionado"
    sending = false;//Estado inicial é falso
    reseting = false;//Estado inicial é falso
    connected = false;
}

MainWindow::~MainWindow()
{
    //SSL_Client->close();
}

void MainWindow::disconnectUdp()
{
    //SSL_Client->close();
    connected = false;
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
    if(!connected){
      btnConnect->setText("Disconnect");
      btnSend->setDisabled(false);
      connected = true;
    }else{
      disconnectUdp();
      btnConnect->setText("Connect");
    }
}

//********************************APAGAR ESTA FUNCAO QUANDO IMPLEMENTAR INTERFACE NOVA ***********************************************
void MainWindow::updateFieldState(){

    //ESTA FUNCAO TEM QUE SER POSTA NO START PROGRAM ABAIXO
    field->fieldUpdate();//Pede para que o field se atualize

    //Esta parte é referente a printar os valores na tela!
    QString output = "Confidence\tX\tY\n";

    output += QString::number(field->ball.mensure_confidence)+QString("\t")
            +QString::number(field->ball.position.x)+QString("\t")
            +QString::number(field->ball.position.y)+QString("\n\n");

    output += "ID\tOrientation\tX\tY\n";

    output += "Yellow Team: \n";
    for(int i = 0;i < 6;i++){
        output += QString::number(field->yellow[i].id)+QString("\t")
                +QString::number(field->yellow[i].orientation)+QString("\t")
                +QString::number(field->yellow[i].position.x)+QString("\t")
                +QString::number(field->yellow[i].position.y)+QString("\n");
    }
    output += "Blue Team: \n";
    for(int i = 0;i < 6;i++){
        output += QString::number(field->blue[i].id)+QString("\t")
                +QString::number(field->blue[i].orientation)+QString("\t")
                +QString::number(field->blue[i].position.x)+QString("\t")
                +QString::number(field->blue[i].position.y)+QString("\n");
    }

    txtInfo->setText(output);
}

void MainWindow::startProgram() {

    Movement rCommand;

    if(sending) {
        printf("enviar\n");

        updateFieldState();//Apagar quando apagar a funcao acima (INTERFACE NOVA)
        //field->fieldUpdate();

        printf("checando time\n");
        if(cmbTeam->currentText() == "Yellow"){
            for (int i = 0; i < 6; i++) {
                printf("ACHOU AMARELO\n");
                rCommand.MoverPara(field->ball.position.x,field->ball.position.y,field->yellow[i].orientation, field->yellow[i].position.x, field->yellow[i].position.y,true,i);
            }
        }else{
            for (int i = 0; i < 6; i++) {
                printf("ACHOU AZUL\n");
                rCommand.MoverPara(field->ball.position.x,field->ball.position.y, field->blue[i].orientation, field->blue[i].position.x, field->blue	[i].position.y,false,i);

            }

        }

    }

}

        /*
        if (SSL_Client->receive(packet)) {
            printf("-----Received Wrapper Packet---------------------------------------------\n");
            //see if the packet contains a robot detection frame:
            if (packet.has_detection()) {
                SSL_DetectionFrame detection = packet.detection();

                int balls_n = detection.balls_size();
                int robots_blue_n = detection.robots_blue_size();
                int robots_yellow_n = detection.robots_yellow_size();

                //Ball info:
                for (int i = 0; i < balls_n; i++) {
                    SSL_DetectionBall ball = detection.balls(i);
                }
                /*
                //Blue robot info:
                for (int i = 0; i < robots_blue_n; i++) {
                    SSL_DetectionRobot robot = detection.robots_blue(i);
                    printf("-Robot(B) (%2d/%2d): ", i + 1, robots_blue_n);
                    printRobotInfo(robot);
                    //robot.x(), robot.y(), robot.orientation()
                    //ball.pixel_x(),ball.pixel_y()
                }

                //Yellow robot info:
                for (int i = 0; i < robots_yellow_n; i++) {
                    SSL_DetectionRobot robot = detection.robots_yellow(i);
                    printf("-Robot(Y) (%2d/%2d): ", i + 1, robots_yellow_n);
                    printRobotInfo(robot);
                    if (i == 2) {
                        MoverPara(detection.balls(0).pixel_x(), detection.balls(0).pixel_y(), robot.orientation(), robot.pixel_x(), robot.pixel_y());
                    }
                }
            }
            //see if packet contains geometry data:
            if (packet.has_geometry()) {
                const SSL_GeometryData & geom = packet.geometry();
                printf("-[Geometry Data]-------\n");

                const SSL_GeometryFieldSize & field = geom.field();
                printf("Field Dimensions:\n");
                printf("  -line_width=%d (mm)\n", field.line_width());
                printf("  -field_length=%d (mm)\n", field.field_length());
                printf("  -field_width=%d (mm)\n", field.field_width());
                printf("  -boundary_width=%d (mm)\n", field.boundary_width());
                printf("  -referee_width=%d (mm)\n", field.referee_width());
                printf("  -goal_width=%d (mm)\n", field.goal_width());
                printf("  -goal_depth=%d (mm)\n", field.goal_depth());
                printf("  -goal_wall_width=%d (mm)\n", field.goal_wall_width());
                printf("  -center_circle_radius=%d (mm)\n", field.center_circle_radius());
                printf("  -defense_radius=%d (mm)\n", field.defense_radius());
                printf("  -defense_stretch=%d (mm)\n", field.defense_stretch());
                printf("  -free_kick_from_defense_dist=%d (mm)\n", field.free_kick_from_defense_dist());
                printf("  -penalty_spot_from_field_line_dist=%d (mm)\n", field.penalty_spot_from_field_line_dist());
                printf("  -penalty_line_from_spot_dist=%d (mm)\n", field.penalty_line_from_spot_dist());

                int calib_n = geom.calib_size();
                for (int i = 0; i < calib_n; i++) {
                    const SSL_GeometryCameraCalibration & calib = geom.calib(i);
                    printf("Camera Geometry for Camera ID %d:\n", calib.camera_id());
                    printf("  -focal_length=%.2f\n", calib.focal_length());
                    printf("  -principal_point_x=%.2f\n", calib.principal_point_x());
                    printf("  -principal_point_y=%.2f\n", calib.principal_point_y());
                    printf("  -distortion=%.2f\n", calib.distortion());
                    printf("  -q0=%.2f\n", calib.q0());
                    printf("  -q1=%.2f\n", calib.q1());
                    printf("  -q2=%.2f\n", calib.q2());
                    printf("  -q3=%.2f\n", calib.q3());
                    printf("  -tx=%.2f\n", calib.tx());
                    printf("  -ty=%.2f\n", calib.ty());
                    printf("  -tz=%.2f\n", calib.tz());

                    if (calib.has_derived_camera_world_tx() && calib.has_derived_camera_world_ty() && calib.has_derived_camera_world_tz()) {
                        printf("  -derived_camera_world_tx=%.f\n", calib.derived_camera_world_tx());
                        printf("  -derived_camera_world_ty=%.f\n", calib.derived_camera_world_ty());
                        printf("  -derived_camera_world_tz=%.f\n", calib.derived_camera_world_tz());
                    }

                }
            }
        }*/
