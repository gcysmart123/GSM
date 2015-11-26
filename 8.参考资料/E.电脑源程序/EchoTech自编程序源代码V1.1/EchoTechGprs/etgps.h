#ifndef ETGPS_H
#define ETGPS_H

#include <QWidget>
#include <QtGui>
#include <QtCore>

#include "win_qextserialport.h"

namespace Ui {
    class EtGps;
}

class EtGps : public QWidget
{
    Q_OBJECT

public:
    explicit EtGps(QWidget *parent = 0);
    ~EtGps();

private:
    Ui::EtGps *ui;
public:
    QLabel      labProtocol;
    QLabel      labTime;
    QLabel      labLatitude;
    QLabel      labLongitude;
    QLabel      labAltitude;
    QLabel      labSeparation;
    QLabel      labSpeed;
    QLabel      labCourse;
    QComboBox   combProtocol;
    QLineEdit   editTime;
    QLineEdit   editLatitude;
    QLineEdit   editLongitude;
    QLineEdit   editAltitude;
    QLineEdit   editSeparation;
    QLineEdit   editSpeed;
    QLineEdit   editCourse;
    QGridLayout *gridLayout;

    int         time1s;

    Win_QextSerialPort *gpsPort;
    QString             gpsStr;
public:
    void    startGps(QString commuPort,QString commuOther);
    void    closeGps();
    void    timerEvent(QTimerEvent* event);
    void    getSubStr(QString   strGps);
    void    getTime(QString strTime);
    void    getLatitude(QString strLatitude,QString strNS);
    void    getLongitude(QString strLongitude,QString strEW);
    void    getAltitude(QString strAltitude);
    void    getSeparation(QString strSeparation);
    void    getSpeed(QString strSpeed);
    void    getCourse(QString strCourse);
};

#endif // ETGPS_H
