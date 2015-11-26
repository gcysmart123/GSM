#include "dialogsource.h"
#include "ui_dialogsource.h"

DialogSource::DialogSource(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSource)
{
    ui->setupUi(this);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("System"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("System"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("System"));
    labHard.setText(QObject::tr("��ѡ������Ӳ������"));
    labSys.setText(QObject::tr("��ѡ�����Ĳ���ϵͳ"));
    butOk.setText(QObject::tr("ȷ��"));
    butCel.setText(QObject::tr("ȡ��"));
    connect(&butOk,SIGNAL(clicked()),this,SLOT(accept()));
    connect(&butCel,SIGNAL(clicked()),this,SLOT(reject()));
    hLayout = new QHBoxLayout;      //���ֹ�����
    vLayout = new QVBoxLayout;
    hLayout->addWidget(&butOk);
    hLayout->addWidget(&butCel);
    vLayout->addWidget(&labHard);
    vLayout->addWidget(&combHard);
    vLayout->addWidget(&labSys);
    vLayout->addWidget(&combSys);
    vLayout->addLayout(hLayout);
    setLayout(vLayout);             //��������ʾ����
}

DialogSource::~DialogSource()
{
    delete ui;
}

void DialogSource::accept()
{
    QDialog::accept();
}
