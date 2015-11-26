#include "etgprs.h"
#include "ui_etgprs.h"

EtGprs::EtGprs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EtGprs)
{
    QString tempStr;
    tempStr.clear();

    ui->setupUi(this);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("System"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("System"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("System"));
    labProtocol.setText(tr("连接方式："));
    combProtocol.addItem(tr("TCP"));
    combProtocol.addItem(tr("UDP"));
    labMode.setText(tr("工作模式："));
    combMode.addItem(tr("双端SC"));
    combMode.addItem(tr("双端CS"));
    combMode.addItem(tr("单端S"));
    combMode.addItem(tr("单端C"));
    labPcIP.setText(tr("PC端IP："));
    labEtIP.setText(tr("ET端IP："));

    QList   <QNetworkInterface>     tempInterfaceList   =   QNetworkInterface::allInterfaces();
    QNetworkInterface               tempInterface       =   tempInterfaceList.at(0);
    QList   <QNetworkAddressEntry>  tempEntryList       =   tempInterface.addressEntries();
    QNetworkAddressEntry            tempEntry           =   tempEntryList.at(0);
    strPcIp   =   tempEntry.ip().toString();
    strPcPort =   "8080";
    tempStr   =   strPcIp   +   ":"  +   strPcPort;
    editPcIP.setText(tempStr);
    strPcIp.clear();
    strPcPort.clear();
    tempStr.clear();

    strEtIp     =   "x.x.x.x";
    strEtPort   =   "8080";
    tempStr     =   strEtIp +   ":" +   strEtPort;
    editEtIP.setText(tempStr);
    strEtIp.clear();
    strEtPort.clear();
    tempStr.clear();

    butConnect.setText(tr("连接"));
    butSend.setText(tr("发送"));
    connect(&combProtocol,SIGNAL(currentIndexChanged(QString)),this,SLOT(onCombProtocol()));
    connect(&combMode,SIGNAL(currentIndexChanged(QString)),this,SLOT(onCombMode()));
    connect(&butConnect,SIGNAL(clicked()),this,SLOT(onButConnect()));
    connect(&butSend,SIGNAL(clicked()),this,SLOT(onButSend()));
    hLayout             =   new QHBoxLayout;
    vLayout             =   new QVBoxLayout;
    gridConfigLayout    =   new QGridLayout;
    gridPcLayout        =   new QGridLayout;
    gridEtLayout        =   new QGridLayout;
    gridConfigLayout->addWidget(&labProtocol,0,0,1,1);
    gridConfigLayout->addWidget(&combProtocol,0,1,1,1);
    gridConfigLayout->addWidget(&labMode,0,2,1,1);
    gridConfigLayout->addWidget(&combMode,0,3,1,1);
    gridPcLayout->addWidget(&labPcIP,0,0,1,1);
    gridPcLayout->addWidget(&editPcIP,0,1,1,1);
    gridEtLayout->addWidget(&labEtIP,0,0,1,1);
    gridEtLayout->addWidget(&editEtIP,0,1,1,1);
    hLayout->addWidget(&butConnect);
    hLayout->addWidget(&butSend);
    vLayout->addLayout(gridConfigLayout);
    vLayout->addLayout(gridPcLayout);
    vLayout->addWidget(&textPcMsg);
    vLayout->addLayout(gridEtLayout);
    vLayout->addWidget(&textEtMsg);
    vLayout->addLayout(hLayout);
    setLayout(vLayout);

    gprsStep    =   0;
    strProtocol.clear();
    strMode.clear();
}

EtGprs::~EtGprs()
{
    delete ui;
}

void    EtGprs::startGprs(QString commuPort,QString commuOther)
{
    gprsStr.clear();
    gprsPort = new Win_QextSerialPort(commuPort,QextSerialBase::Polling);
    gprsPort->open(QIODevice::ReadWrite);
    if(commuOther=="BAUD9600")  {gprsPort->setBaudRate(BAUD9600);}
    if(commuOther=="BAUD19200") {gprsPort->setBaudRate(BAUD19200);}
    gprsPort->setDataBits(DATA_8);
    gprsPort->setParity(PAR_NONE);
    gprsPort->setStopBits(STOP_1);
    gprsPort->setFlowControl(FLOW_OFF);
    gprsPort->setTimeout(10);
    time1s      =   startTimer(1000);
}

void    EtGprs::closeGprs()
{
    gprsPort->close();
    killTimer(time1s);
}

void    EtGprs::timerEvent(QTimerEvent* event)
{
    QString tempStr;
    tempStr.clear();
    gprsStr.clear();
    if(event->timerId() == time1s)
    {
        gprsStr = gprsPort->readAll();
        qDebug()<<gprsStr;
        if(gprsStep == 0)
        {
            initGprs();
        }
        if(gprsStr.contains("OK",Qt::CaseSensitive))
        {
            initGprs();
        }
        if(gprsStr.contains("AT+CIFSR",Qt::CaseSensitive))
        {
            gprsStr.remove("AT+CIFSR",Qt::CaseSensitive);
            gprsStr = gprsStr.simplified();
            getTcpIp();
            strEtIp =   gprsStr;
            tempStr =   strEtIp +   ":"  +   strEtPort;
            editEtIP.setText(tempStr);
            strEtIp.clear();
            strEtPort.clear();
            tempStr.clear();
            initGprs();
        }
        if(gprsStr.contains("SHUT OK",Qt::CaseSensitive))
        {
            gprsStep = 0;
            initGprs();
        }
        if(gprsStr.contains(">",Qt::CaseSensitive))
        {
            gprsPort->write(strEtMessage.toAscii());
            strEtMessage.clear();
        }
        gprsStr.clear();
    }
    else
    {
        EtGprs::timerEvent(event);
    }
}

void    EtGprs::initGprs()
{
    QString tempStr;
    tempStr.clear();
    switch(gprsStep)
    {
        case    0:  gprsPort->write("AT+CIPMUX=0\r");       break;
        case    1:  gprsPort->write("AT+CIPMODE=0\r");      break;
        case    2:  gprsPort->write("AT+CGATT=1\r");        break;
        case    10: gprsPort->write("AT+CSTT=\"CMNET\"\r"); break;
        case    11: gprsPort->write("AT+CIICR\r");          break;
        case    12: gprsPort->write("AT+CIFSR\r");          break;
        case    13:
        {
            getTcpIp();
            tempStr="AT+CIPSTART=\"" + strProtocol + "\",\"" + strPcIp + "\",\"" + strPcPort + "\"\r";
            gprsPort->write(tempStr.toAscii());
            strPcIp.clear();
            strPcPort.clear();
            tempStr.clear();
        }
        break;
        case    20:
        {
            getTcpIp();
            tempStr="AT+CIPSERVER=1,"   +   strEtPort   +   "\r";
            gprsPort->write(tempStr.toAscii());
            strEtPort.clear();
            tempStr.clear();
        }
        break;
        case    21: gprsPort->write("AT+CIFSR\r");          break;
        default:
        break;
    }
    gprsStep++;
}
void    EtGprs::getTcpIp()
{
    QString tempStr;
    tempStr.clear();
    unsigned    int i;
    i = 0;
    strPcIp.clear();
    strPcPort.clear();
    tempStr =   editPcIP.text();
    for(i=0;i<tempStr.length();i++)
    {
        if(tempStr[i]==':')
        {
            strPcIp    = strPcPort;
            strPcPort.clear();
        }
        else
        {
            strPcPort += tempStr[i];
        }
    }
    tempStr.clear();
    strEtIp.clear();
    strEtPort.clear();
    tempStr =   editEtIP.text();
    for(i=0;i<tempStr.length();i++)
    {
        if(tempStr[i]==':')
        {
            strEtIp    = strEtPort;
            strEtPort.clear();
        }
        else
        {
            strEtPort += tempStr[i];
        }
    }
    tempStr.clear();
}

void    EtGprs::onCombProtocol()
{
    strProtocol =   combProtocol.currentText();
}

void    EtGprs::onCombMode()
{
    strMode     =   combMode.currentText();
}

void    EtGprs::onButConnect()
{
    onCombProtocol();
    onCombMode();
    if(butConnect.text()==tr("连接"))
    {
        if(strMode  ==  tr("双端SC"))
        {
            if(strProtocol == "TCP")
            {
                createTcpServer();
            }
            if(strProtocol == "UDP")
            {
                createUdpConnect();
            }
            gprsStep=10;
        }
        if(strMode  ==  tr("双端CS"))
        {
            if(strProtocol == "TCP")
            {
                createTcpClient();
            }
            if(strProtocol == "UDP")
            {
                createUdpConnect();
            }
            gprsStep=20;
        }
        if(strMode  ==  tr("单端S"))
        {
            textPcMsg.setText(tr("请使用第三方Client程序"));
            gprsStep=20;
        }
        if(strMode  ==  tr("单端C"))
        {
            textPcMsg.setText(tr("请使用第三方Server程序"));
            gprsStep=10;
        }
        initGprs();
        butConnect.setText(tr("断开"));
    }
    else if(butConnect.text()==tr("断开"))
    {
        tcpSocket->disconnectFromHost();
        gprsPort->write("AT+CIPSHUT\r");
        textPcMsg.clear();
        textEtMsg.clear();
        butConnect.setText(tr("连接"));
    }
}

void    EtGprs::onButSend()
{
    strPcMessage.clear();
    strEtMessage.clear();
    strPcMessage    =   textPcMsg.toPlainText();
    strEtMessage    =   textEtMsg.toPlainText();
    if(!strPcMessage.isEmpty())
    {
        if(strProtocol=="TCP")
        {
            tcpWrite();
        }
        if(strProtocol=="UDP")
        {
            udpWrite();
        }
        textPcMsg.clear();
    }
    if(!strEtMessage.isEmpty())
    {
        strEtMessage    =   strEtMessage    +   "\x1A\r";
        gprsPort->write("AT+CIPSEND\r");
        textEtMsg.clear();
    }
}

void    EtGprs::createTcpServer()
{
    tcpServer   =   new QTcpServer(this);
    tcpSocket   =   new QTcpSocket(this);
    getTcpIp();
    tcpServer->listen(QHostAddress::Any,strPcPort.toUInt(0,10));
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(tcpConnect()));
    strPcIp.clear();
    strPcPort.clear();
}

void    EtGprs::tcpConnect()
{
    tcpSocket   =   tcpServer->nextPendingConnection();
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(tcpRead()));
    tcpServer->close();
}

void    EtGprs::createTcpClient()
{
    QHostAddress    *hostIp;
    hostIp  =   new QHostAddress();
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(tcpRead()));
    getTcpIp();
    hostIp->setAddress(strEtIp);
    tcpSocket->connectToHost(*hostIp,strEtPort.toUInt(0,10));
    strEtIp.clear();
    strEtPort.clear();
}

void    EtGprs::createUdpConnect()
{
    udpSocket = new QUdpSocket(this);
    getTcpIp();
    udpSocket->bind(strPcPort.toUInt(0,10));
    strPcIp.clear();
    strPcPort.clear();
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(udpRead()));
}

void    EtGprs::udpRead()
{
    QByteArray  tempByte;
    QString     tempStr;
    while(udpSocket->hasPendingDatagrams())
    {
        tempByte.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(tempByte.data(),tempByte.size());
        tempStr =   tempByte.data();
        textPcMsg.clear();
        textPcMsg.setText(tempStr);
    }
}

void    EtGprs::udpWrite()
{
    QByteArray  tempByte;
    tempByte    =   strPcMessage.toLatin1();
    getTcpIp();
    udpSocket->writeDatagram(tempByte.data(),tempByte.size(),QHostAddress::Broadcast,strEtPort.toUInt(0,10));
    strPcMessage.clear();
}

void    EtGprs::tcpRead()
{
    QByteArray  tempByte;
    QString     tempStr;
    while(tcpSocket->bytesAvailable()>0)
    {
        tempByte.resize(tcpSocket->bytesAvailable());
        tcpSocket->read(tempByte.data(),tempByte.size());
        tempStr =   tempByte.data();
        textPcMsg.clear();
        textPcMsg.setText(tempStr);
    }
}

void    EtGprs::tcpWrite()
{
    QByteArray  tempByte;
    tempByte    =   strPcMessage.toLatin1();
    tcpSocket->write(tempByte.data(),tempByte.size());
    strPcMessage.clear();
}

