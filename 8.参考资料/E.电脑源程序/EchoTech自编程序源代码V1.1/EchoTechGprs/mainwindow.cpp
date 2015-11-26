#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("System"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("System"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("System"));
    setWindowTitle(tr("忆科技术-GSM/GPRS测试程序-V1.1"));
    gprsWidget  =   new EtGprs;
    setCentralWidget(gprsWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

