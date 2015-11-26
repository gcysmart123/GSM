#ifndef ETGPRS_H
#define ETGPRS_H

#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <QtNetwork>

#include "win_qextserialport.h"

namespace Ui {
    class EtGprs;
}

class EtGprs : public QWidget
{
    Q_OBJECT

public:
    explicit EtGprs(QWidget *parent = 0);
    ~EtGprs();

private:
    Ui::EtGprs *ui;

public:

    QLabel      labProtocol;
    QComboBox   combProtocol;
    QLabel      labMode;
    QComboBox   combMode;
    QLabel      labPcIP;
    QLabel      labEtIP;
    QLineEdit   editPcIP;
    QLineEdit   editEtIP;
    QTextEdit   textPcMsg;
    QTextEdit   textEtMsg;
    QPushButton butConnect;
    QPushButton butSend;
    QPushButton butStart;
    QPushButton butClose;
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
    QGridLayout *gridConfigLayout;
    QGridLayout *gridPcLayout;
    QGridLayout *gridEtLayout;

    int     time1s;

    Win_QextSerialPort  *gprsPort;
    QString              gprsStr;
    int                  gprsStep;
    QUdpSocket          *udpSocket;
    QTcpSocket          *tcpSocket;
    QTcpServer          *tcpServer;

    QString     strProtocol;
    QString     strMode;
    QString     strPcIp;
    QString     strPcPort;
    QString     strEtIp;
    QString     strEtPort;
    QString     strPcMessage;
    QString     strEtMessage;


public:
    void    getTcpIp();
    void    startGprs(QString commuPort,QString commuOther);
    void    closeGprs();
    void    timerEvent(QTimerEvent* event);
    void    initGprs();
    void    createTcpServer();
    void    createTcpClient();
    void    createUdpConnect();
public slots:
    void    onCombProtocol();
    void    onCombMode();
    void    onButConnect();
    void    onButSend();
    void    udpRead();
    void    udpWrite();
    void    tcpRead();
    void    tcpWrite();
    void    tcpConnect();
};

#endif // ETGPRS_H
