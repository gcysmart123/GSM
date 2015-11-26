#include "etgps.h"
#include "ui_etgps.h"

EtGps::EtGps(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EtGps)
{
    ui->setupUi(this);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("System"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("System"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("System"));
    labProtocol.setText(tr("GPS��ʽ��"));
    labTime.setText(tr("ʱ�䣺"));
    labLatitude.setText(tr("ά�ȣ�"));
    labLongitude.setText(tr("���ȣ�"));
    labAltitude.setText(tr("���θ߶ȣ�"));
    labSeparation.setText(tr("ˮ׼��ߣ�"));
    labSpeed.setText(tr("�ٶȣ�"));
    labCourse.setText((tr("����")));
    combProtocol.addItem("GPGGA");
    combProtocol.addItem("GPRMC");
    gridLayout = new QGridLayout;
    gridLayout->addWidget(&labProtocol,0,0,1,1);
    gridLayout->addWidget(&combProtocol,0,1,1,3);
    gridLayout->addWidget(&labTime,1,0,1,1);
    gridLayout->addWidget(&editTime,1,1,1,3);
    gridLayout->addWidget(&labLatitude,2,0,1,1);
    gridLayout->addWidget(&editLatitude,2,1,1,3);
    gridLayout->addWidget(&labLongitude,3,0,1,1);
    gridLayout->addWidget(&editLongitude,3,1,1,3);
    gridLayout->addWidget(&labAltitude,4,0,1,1);
    gridLayout->addWidget(&editAltitude,4,1,1,3);
    gridLayout->addWidget(&labSeparation,5,0,1,1);
    gridLayout->addWidget(&editSeparation,5,1,1,3);
    gridLayout->addWidget(&labSpeed,6,0,1,1);
    gridLayout->addWidget(&editSpeed,6,1,1,3);
    gridLayout->addWidget(&labCourse,7,0,1,1);
    gridLayout->addWidget(&editCourse,7,1,1,3);
    setLayout(gridLayout);
}

EtGps::~EtGps()
{
    delete ui;
}


void    EtGps::startGps(QString commuPort,QString commuOther)
{
    gpsStr.clear();
    gpsPort = new Win_QextSerialPort(commuPort,QextSerialBase::Polling);
    gpsPort->open(QIODevice::ReadWrite);
    if(commuOther=="BAUD9600")  {gpsPort->setBaudRate(BAUD9600);}
    if(commuOther=="BAUD19200") {gpsPort->setBaudRate(BAUD19200);}
    gpsPort->setDataBits(DATA_8);
    gpsPort->setParity(PAR_NONE);
    gpsPort->setStopBits(STOP_1);
    gpsPort->setFlowControl(FLOW_OFF);
    gpsPort->setTimeout(10);

    time1s      =   startTimer(1000);
}
void    EtGps::closeGps()
{
    gpsPort->close();
    killTimer(time1s);
}
void    EtGps::timerEvent(QTimerEvent* event)
{
    int i = 0;
    QString tempStr;
    tempStr.clear();
    if(event->timerId() == time1s)
    {
        gpsStr = gpsPort->readAll();
        for(i=0;i<gpsStr.length();i++)
        {
            if(gpsStr[i] == '$')
            {
                if(tempStr.startsWith(combProtocol.currentText(),Qt::CaseSensitive))
                {
                    getSubStr(tempStr);
                }
                tempStr.clear();
            }
            else
            {
                tempStr += gpsStr[i];
            }
        }
        i = 0;
        gpsStr.clear();
    }
    else
    {
        EtGps::timerEvent(event);
    }
}
void    EtGps::getSubStr(QString strGps)
{
    QString strSubGps[20];
    int j   =   0;
    int k   =   0;
    for(j=0;j<20;j++)   strSubGps[j].clear();
    j=0;

    for(j=0;j<strGps.length();j++)
    {
        if(strGps[j]==',')  {k++;}
        else                {strSubGps[k] += strGps[j];}
    }
    strGps.clear();
    j = 0;
    k = 0;

    if(strSubGps[0]=="GPGGA")
    {
        //[1]   ʱ��
        //[2]   ά��
        //[3]   �ϣ���
        //[4]   ����
        //[5]   ������
        //[6]   ��λ����
        //[7]   ������
        //[8]   ˮƽ����ϵ��
        //[9]   ���θ߶�
        //[10]   ��
        //[11]  ˮƽ��׼���
        //[12]  ��
        //[13]  ��
        //[14]  У��
        getTime(strSubGps[1]);
        getLatitude(strSubGps[2],strSubGps[3]);
        getLongitude(strSubGps[4],strSubGps[5]);
        getAltitude(strSubGps[9]);
        getSeparation(strSubGps[11]);
    }
    else if(strSubGps[0]=="GPRMC")
    {
        //[1]   ʱ��
        //[2]   ״̬λ
        //[3]   ά��
        //[4]   �ϣ���
        //[5]   ����
        //[6]   ������
        //[7]   �ٶ�
        //[8]   ����
        //[9]   ����
        //[10]   ��
        //[11]  ��
        //[12]  У��
        getTime(strSubGps[1]);
        getLatitude(strSubGps[3],strSubGps[4]);
        getLongitude(strSubGps[5],strSubGps[6]);
        getSpeed(strSubGps[7]);
        getCourse(strSubGps[8]);
    }

    for(j=0;j<20;j++)   strSubGps[j].clear();
    j=0;
}

void    EtGps::getTime(QString strTime)
{
    int tempInt         =   0;
    int tempIntDegrees  =   0;     //�ȣ�ʱ
    int tempIntMinutes  =   0;     //��
    int tempIntSeconds  =   0;     //��
    //ʱ��
    tempInt           =   (int)(strTime.toFloat());
    strTime.clear();
    tempIntDegrees    =   tempInt  / 10000;
    tempInt           =   tempInt  % 10000;
    tempIntMinutes    =   tempInt  /   100;
    tempIntSeconds    =   tempInt  %   100;
    strTime = QString::number(tempIntDegrees) +   ":" +   QString::number(tempIntMinutes) +   ":" + QString::number(tempIntSeconds);
    editTime.setText(strTime);
}

void    EtGps::getLatitude(QString strLatitude, QString strNS)
{
    int     tempIntDegrees  =   0;     //�ȣ�ʱ
    int     tempIntMinutes  =   0;     //��
    float   tempFloatSeconds=   0;   //��
    //ά��
    if(strNS=="N")    strNS = tr("��γ:");
    if(strNS=="S")    strNS = tr("��γ:");
    //����Ϊ�ȷ���
    tempFloatSeconds = strLatitude.toFloat();
    strLatitude.clear();
    tempIntDegrees   = tempFloatSeconds;
    tempIntMinutes   = tempFloatSeconds;
    tempFloatSeconds = tempFloatSeconds - tempIntMinutes;
    tempFloatSeconds = tempFloatSeconds * 60;
    tempIntMinutes   = tempIntMinutes   % 100;
    tempIntDegrees   = tempIntDegrees   / 100;
    //��ʾ
    strLatitude = QString::number(tempIntDegrees) + tr("��") + QString::number(tempIntMinutes) + "'" + QString::number(tempFloatSeconds);
    editLatitude.setText(strNS+strLatitude);
}

void    EtGps::getLongitude(QString strLongitude, QString strEW)
{
    int     tempIntDegrees  =   0;     //�ȣ�ʱ
    int     tempIntMinutes  =   0;     //��
    float   tempFloatSeconds=   0;   //��
    //����
    if(strEW=="E")    strEW = tr("����:");
    if(strEW=="W")    strEW = tr("����:");
    //����Ϊ�ȷ���
    tempFloatSeconds = strLongitude.toFloat();
    strLongitude.clear();
    tempIntDegrees   = tempFloatSeconds;
    tempIntMinutes   = tempFloatSeconds;
    tempFloatSeconds = tempFloatSeconds - tempIntMinutes;
    tempFloatSeconds = tempFloatSeconds * 60;
    tempIntMinutes   = tempIntMinutes   % 100;
    tempIntDegrees   = tempIntDegrees   / 100;
    //��ʾ
    strLongitude = QString::number(tempIntDegrees) + tr("��") + QString::number(tempIntMinutes) + "'" + QString::number(tempFloatSeconds);
    editLongitude.setText(strEW+strLongitude);
}

void    EtGps::getAltitude(QString strAltitude)
{
    editAltitude.setText(strAltitude+tr("��"));   //���θ߶�
}

void    EtGps::getSeparation(QString strSeparation)
{
    editSeparation.setText(strSeparation+tr("��"));  //ˮƽ��׼���
}

void    EtGps::getSpeed(QString strSpeed)
{
    editSpeed.setText(strSpeed);
}

void    EtGps::getCourse(QString strCourse)
{
    editCourse.setText(strCourse);
}
