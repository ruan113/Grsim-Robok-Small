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

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
  //  void executarPrograma();
    void printRobotInfo(const SSL_DetectionRobot & robot);
    void command(bool yellow, int id, double wheel1, double wheel2, double wheel3, double wheel4, double kickspeedx, double kickspeedz);
    void MoverPara(double x, double y, float rRotation, double rX, double rY,bool rColor, int rId);
    void updateFieldState();//Atualiza o fieldState

public slots:
    void reconnectUdp();//Reconecta o socket
    //void sendPacket();//Envia Pacote
    void sendBtnClicked();//Botão send foi clicado
    void resetBtnClicked();//Botão reset foi clicado
    void disconnectUdp();//Disconecta o socket
    void startProgram();

private:
    bool sending, reseting,connected;
    QLineEdit* edtIp;
    QLineEdit* edtPort;
    QLineEdit* edtId;
    QLineEdit* edtObjx, *edtObjy, *edtW;
    QLineEdit* edtV1, *edtV2, *edtV3, *edtV4;
    QLineEdit* edtKick, *edtChip;
    QLabel* lblIp;
    QLabel* lblPort;
    QLabel* lblId;
    QComboBox* cmbTeam;
    QLabel* lblObjx, *lblObjy, *lblW;
    QLabel* lblV1, *lblV2, *lblV3, *lblV4;
    QLabel* lblKick, *lblChip;
    QTextEdit* txtInfo;
    QCheckBox* chkVel, *chkSpin;
    QPushButton* btnSend;
    QPushButton* btnReset;
    QPushButton* btnConnect;
    QTimer* timer;
    Fieldstate *field;
};

#endif // MAINWINDOW_H
