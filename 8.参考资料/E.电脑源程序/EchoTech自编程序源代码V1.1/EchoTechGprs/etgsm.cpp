#include "etgsm.h"
#include "ui_etgsm.h"

EtGsm::EtGsm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EtGsm)
{
    ui->setupUi(this);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("System"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("System"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("System"));
    heardLayout = new QHBoxLayout;
    butLayout   = new QHBoxLayout;
    vLayout     = new QVBoxLayout;
    gridLayout  = new QGridLayout;
    labServer.setText(tr("运营商："));
    combServer.addItem(tr("中国联通"));
    combServer.addItem(tr("中国移动"));
    combServer.setCurrentIndex(0);
    labText.setText(tr("文本格式："));
    combText.addItem(tr("中文"));
    combText.addItem(tr("英文"));
    combText.setCurrentIndex(0);
    labCenter.setText(tr("短信中心："));
    labNumber.setText(tr("呼叫号码："));
    labPort.setText(tr("通讯端口"));
    editPort.setText(tr("COM3"));
    //按键
    butMessage.setText(tr("发送"));
    gsmCallStatus = free;
    butTelephone.setText(tr("呼叫"));

    connect(&butMessage,SIGNAL(clicked()),this,SLOT(onButMessage()));
    connect(&butTelephone,SIGNAL(clicked()),this,SLOT(onButTelephone()));
    connect(&combText,SIGNAL(currentIndexChanged(QString)),this,SLOT(onCombText()));
    butStart.setText(tr("开始"));
    butClose.setText(tr("关闭"));
    connect(&butStart,SIGNAL(clicked()),this,SLOT(startGsm()));
    connect(&butStart,SIGNAL(clicked()),this,SLOT(CloseGsm()));
    gridLayout->addWidget(&labCenter,0,0,1,1);
    gridLayout->addWidget(&editCenter,0,1,1,3);
    gridLayout->addWidget(&labNumber,1,0,1,1);
    gridLayout->addWidget(&editNumber,1,1,1,3);
    gridLayout->addWidget(&labPort,2,0,1,1);
    gridLayout->addWidget(&editPort,2,1,1,3);
    heardLayout->addWidget(&labServer);
    heardLayout->addWidget(&combServer);
    heardLayout->addWidget(&labText);
    heardLayout->addWidget(&combText);
    butLayout->addWidget(&butMessage);
    butLayout->addWidget(&butTelephone);
    butLayout->addWidget(&butStart);
    butLayout->addWidget(&butClose);
    vLayout->addLayout(heardLayout);
    vLayout->addLayout(gridLayout);
    vLayout->addWidget(&listLog);
    vLayout->addWidget(&editMessage);
    vLayout->addLayout(butLayout);
    setLayout(vLayout);
    ucs2gsm =   false;
    gsm2ucs =   false;
    gsmStep =   0;
    strReceive.clear();
 }

EtGsm::~EtGsm()
{
    delete ui;
}

void    EtGsm::startGsm()
{
    QString tempStr;
    tempStr =   editPort.text();
    qDebug()<<tempStr;
    gsmStr.clear();
    gsmPort = new Win_QextSerialPort(tempStr,QextSerialBase::Polling);
    gsmPort->open(QIODevice::ReadWrite);
    gsmPort->setBaudRate(BAUD9600);
    gsmPort->setDataBits(DATA_8);
    gsmPort->setParity(PAR_NONE);
    gsmPort->setStopBits(STOP_1);
    gsmPort->setFlowControl(FLOW_OFF);
    gsmPort->setTimeout(10);
    time1s      =   startTimer(1000);
}

void    EtGsm::closeGsm()
{
    gsmPort->close();
    killTimer(time1s);
}

void    EtGsm::timerEvent(QTimerEvent* event)
{
    QString tempStr;
    tempStr.clear();
    int i;
    i   =   0;
    int j;
    j   =   0;
    if(event->timerId() == time1s)
    {
        gsmStr = gsmPort->readAll();
        if(gsmStep == 0)
        {
            gsmStep++;
            gsmPort->write("AT+CLIP=1\r");
        }
        if(gsmStr.contains("RING",Qt::CaseSensitive))
        {
            butTelephone.setText(tr("接听"));
            if(gsmCallStatus != callin)
            {
                gsmCallStatus   =   callin;
                for(i=16;i<gsmStr.count();i++)
                {
                    if(gsmStr[i]==':')
                    {
                        tempStr.clear();
                    }
                    if(gsmStr[i+2]=='\"')
                    {
                        break;
                    }
                    tempStr +=gsmStr[i+2];
                }
                tempStr +=  tr("语音呼入");
                listLog.addItem(tempStr);
                tempStr.clear();
            }
        }
        if(gsmStr.contains("OK",Qt::CaseSensitive))
        {
            if(gsmStep == 1)
            {
                gsmStep++;
                onCombText();
            }
            else if(ucs2gsm  ==   true)
            {
                gsmPort->write("AT+CSCS=\"GSM\"\r");
                ucs2gsm =   false;
            }
            else if(gsm2ucs  ==  true)
            {
                gsmPort->write("AT+CSCS=\"UCS2\"\r");
                gsm2ucs =   false;
            }
        }
        if(gsmStr.contains("NO CARRIER",Qt::CaseSensitive))
        {
            gsmCallStatus = free;
            butTelephone.setText(tr("呼叫"));
        }
        if(gsmStr.contains(">",Qt::CaseSensitive))
        {
            gsmPort->write(strMessage.toAscii());
        }
        if(gsmStr.contains("+CMTI",Qt::CaseSensitive))
        {
            gsmStr.remove("+CMTI: \"SM\",",Qt::CaseSensitive);
            gsmStr = gsmStr.simplified();
            tempStr =   "AT+CMGR="  +   gsmStr  +"\r";
            gsmPort->write(tempStr.toAscii());
            tempStr.clear();
        }
        if(gsmStr.contains("+CMGR",Qt::CaseSensitive))
        {
            for(i=11;i<gsmStr.length();i++)     //111避开返回的AT+CMGR=1语句
            {
                if(gsmStr[i]=='\r')
                    break;
            }
            gsmStr.remove(0,i+1);
            gsmStr = gsmStr.simplified();
            //去消息头
            tempStr += gsmStr[0];
            tempStr += gsmStr[1];
            i   =  2 * tempStr.toInt(0,16) + 2;
            gsmStr.remove(0,i);
            tempStr.clear();
            i   =   0;
            //得到电话号码
            tempStr += gsmStr[2];
            tempStr += gsmStr[3];
            gsmStr.remove(0,6);
            i = tempStr.toInt(0,16);
            if(i%2==1)
            {
                i++;
            }
            tempStr.clear();
            for(j=0;j<i;j=j+2)
            {
                tempStr +=  gsmStr[j+1];
                tempStr +=  gsmStr[j];
            }
            if(tempStr.contains("F",Qt::CaseSensitive))
            {
                tempStr.remove("F",Qt::CaseSensitive);
            }
            tempStr = tempStr + tr("发来短信");
            listLog.addItem(tempStr);
            tempStr.clear();
            gsmStr.remove(0,i);
            i = 0;
            j = 0;
            //信息格式
            gsmStr.remove(0,4);
            //信息时间
            gsmStr.remove(0,14);
            //内容
            tempStr += gsmStr[0];
            tempStr += gsmStr[1];
            i = tempStr.toInt(0,16)/2;
            gsmStr.remove(0,2);
            tempStr.clear();
            strReceive.clear();
            for(j=0;j<i;j++)
            {
                tempStr += gsmStr[4*j];
                tempStr += gsmStr[4*j+1];
                tempStr += gsmStr[4*j+2];
                tempStr += gsmStr[4*j+3];
                intReceive  = tempStr.toUInt(0,16);
                strReceive += QString::fromUcs4(&intReceive,1);
                tempStr.clear();
            }
            editMessage.setText(strReceive);
        }
        gsmStr.clear();
    }
    else
    {
        EtGsm::timerEvent(event);
    }
}

void    EtGsm::onButMessage()
{
    QString tempStr;
    tempStr.clear();
    strMessage = editMessage.toPlainText();
    tempStr =   combText.currentText();
    if(tempStr  ==  tr("中文"))
    {
        QString strCenter,tempCenter;
        QString strNumber,tempNumber;
        int i;
        strCenter   =   "089168";
        strNumber   =   "11000D9168";
        tempCenter  =   editCenter.text() + "F";
        tempNumber  =   editNumber.text() + "F";
        for(i=0;i<6;i++)
        {
            strCenter   +=  tempCenter[2*i+1];
            strCenter   +=  tempCenter[2*i];
            strNumber   +=  tempNumber[2*i+1];
            strNumber   +=  tempNumber[2*i];
        }
        strNumber       +=  "0008AA";
        i   =   2*strMessage.length();
        if(i<16)
        {
            strNumber   +=  "0";
        }
        strNumber       +=  QString::number(i,16);
        i = strNumber.length()/2 + i;
        tempStr = "AT+CMGS="+QString::number(i)+"\r";
        QVector <uint> uintVector;
        uintVector = strMessage.toUcs4();
        strMessage.clear();
        for(i=0;i<uintVector.count();i++)
        {
            strMessage += QString::number(uintVector.at(i),16).toUpper();
        }
        strMessage  =   strCenter   +   strNumber   +   strMessage  +   "\x1A\r";
        //13010731500
    }
    if(tempStr  ==  tr("英文"))
    {
        tempStr = "AT+CMGS=\""+editNumber.text()+"\"\r";
        strMessage +=   "\x1A\r";
    }
    gsmPort->write(tempStr.toAscii());
    editMessage.clear();
    tempStr =   tr("给") + editNumber.text() + tr("发送短信");
    listLog.addItem(tempStr);
    tempStr.clear();
}

void    EtGsm::onButTelephone()
{
    QString tempStr;
    tempStr.clear();
    if(gsmCallStatus == free)
    {
        tempStr = "ATD"+editNumber.text()+";\r";
        gsmPort->write(tempStr.toAscii());
        gsmCallStatus = callout;
        butTelephone.setText(tr("挂机"));
        tempStr =   tr("语音呼叫：")    +   editNumber.text();
        listLog.addItem(tempStr);
        tempStr.clear();
    }
    else if(gsmCallStatus == callin)
    {
        gsmPort->write("ATA\r");
        gsmCallStatus = callout;
        butTelephone.setText(tr("挂机"));
    }
    else if(gsmCallStatus == callout)
    {
        gsmPort->write("ATH\r");
        gsmCallStatus = free;
        butTelephone.setText(tr("呼叫"));
    }
}

void    EtGsm::onCombText()
{
    QString tempStr;
    tempStr = combText.currentText();
    if(tempStr == tr("中文"))
    {
        gsmPort->write("AT+CMGF=0\r");
        gsm2ucs =   true;
        ucs2gsm =   false;
    }
    if(tempStr == tr("英文"))
    {
        gsmPort->write("AT+CMGF=1\r");
        ucs2gsm =   true;
        gsm2ucs =   false;
    }
}
