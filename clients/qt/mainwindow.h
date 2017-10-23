#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Bibliotecas Padrões
#include <QtGui/QMainWindow>
#include <QtGui/QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QTimer>
#include <QCheckBox>
#include <QComboBox>
#include <QTextEdit>
#include <QPushButton>
#include <QtNetwork>
#include <QUdpSocket>
#include <vector>
#include <QGridLayout>
#include <QDebug>
#include <QMessageBox>
#include <string>

//Bibliotecas Grsim
#include "grSim_Packet.pb.h"
#include "grSim_Commands.pb.h"
#include "grSim_Replacement.pb.h"
#include "messages_robocup_ssl_wrapper.pb.h"
#include "messages_robocup_ssl_geometry.pb.h"
#include "messages_robocup_ssl_detection.pb.h"
#include "Classes/Fieldstate.h"
#include "Movement.h"
#include "../../include/net/robocup_ssl_client.h"

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void executarPrograma();

public slots:
    void reconnectUdp();//Reconecta o socket
    void sendPacket();//Envia Pacote
    void sendBtnClicked();//Botão send foi clicado
    void resetBtnClicked();//Botão reset foi clicado
    void disconnectUdp();//Disconecta o socket
    void updateFieldState();//Atualiza o fieldState

private:
    bool sending, reseting;
    QUdpSocket udpsocket;
    QHostAddress _addr;
    quint16 _port;
    QLineEdit* edtIp;
    QLineEdit* edtPort;
    QLineEdit* edtId;
    QLineEdit* edtVx, *edtVy, *edtW;
    QLineEdit* edtV1, *edtV2, *edtV3, *edtV4;
    QLineEdit* edtKick, *edtChip;
    QLabel* lblIp;
    QLabel* lblPort;
    QLabel* lblId;
    QComboBox* cmbTeam;
    QLabel* lblVx, *lblVy, *lblW;
    QLabel* lblV1, *lblV2, *lblV3, *lblV4;
    QLabel* lblKick, *lblChip;
    QTextEdit* txtInfo;
    QCheckBox* chkVel, *chkSpin;
    QPushButton* btnSend;
    QPushButton* btnReset;
    QPushButton* btnConnect;
    QTimer* timer;
    Fieldstate *field;
    Movement *moviment;
    RoboCupSSLClient *SSL_Client;
};

#endif // MAINWINDOW_H
