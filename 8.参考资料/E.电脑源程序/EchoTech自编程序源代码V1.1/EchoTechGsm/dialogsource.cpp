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
    labHard.setText(QObject::tr("请选择您的硬件环境"));
    labSys.setText(QObject::tr("请选择您的操作系统"));
    butOk.setText(QObject::tr("确定"));
    butCel.setText(QObject::tr("取消"));
    connect(&butOk,SIGNAL(clicked()),this,SLOT(accept()));
    connect(&butCel,SIGNAL(clicked()),this,SLOT(reject()));
    hLayout = new QHBoxLayout;      //布局管理器
    vLayout = new QVBoxLayout;
    hLayout->addWidget(&butOk);
    hLayout->addWidget(&butCel);
    vLayout->addWidget(&labHard);
    vLayout->addWidget(&combHard);
    vLayout->addWidget(&labSys);
    vLayout->addWidget(&combSys);
    vLayout->addLayout(hLayout);
    setLayout(vLayout);             //将布局显示出来
}

DialogSource::~DialogSource()
{
    delete ui;
}

void DialogSource::accept()
{
    QDialog::accept();
}
