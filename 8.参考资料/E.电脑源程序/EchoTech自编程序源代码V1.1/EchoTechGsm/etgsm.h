#ifndef ETGSM_H
#define ETGSM_H

#include <QWidget>
#include <QtGui>
#include <QtCore>

#include "win_qextserialport.h"

#define free    0
#define callin  1
#define callout 2

namespace Ui {
    class EtGsm;
}

class EtGsm : public QWidget
{
    Q_OBJECT

public:
    explicit EtGsm(QWidget *parent = 0);
    ~EtGsm();

private:
    Ui::EtGsm *ui;

public:
    QLabel  labServer;
    QLabel  labText;
    QLabel  labCenter;
    QLabel  labNumber;
    QLabel  labPort;
    QComboBox   combServer;
    QComboBox   combText;
    QLineEdit   editCenter;
    QLineEdit   editNumber;
    QLineEdit   editPort;
    QListWidget listLog;
    QTextEdit   editMessage;
    QPushButton butMessage;
    QPushButton butTelephone;
    QPushButton butStart;
    QPushButton butClose;
    QHBoxLayout *heardLayout;
    QHBoxLayout *butLayout;
    QVBoxLayout *vLayout;
    QGridLayout *gridLayout;

    QString strMessage;
    QString strReceive;
    uint    intReceive;
    int     time1s;
    bool    ucs2gsm;
    bool    gsm2ucs;

    Win_QextSerialPort  *gsmPort;
    QString              gsmStr;
    int                  gsmStep;
    int     gsmCallStatus;
public:
    void    timerEvent(QTimerEvent* event);
public slots:
    void    startGsm();
    void    closeGsm();
    void    onButMessage();
    void    onButTelephone();
    void    onCombText();
};

#endif // ETGSM_H
