#include "dialogterget.h"
#include "ui_dialogterget.h"

DialogTerget::DialogTerget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTerget)
{
    ui->setupUi(this);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("System"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("System"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("System"));
    setWindowTitle(tr("连接目标设置"));
    tableTerget.setColumnCount(4);
    tableTerget.setRowCount(0);
    QStringList tableHeader;
    tableHeader.append(tr("硬件目标"));
    tableHeader.append(tr("连接方式"));
    tableHeader.append(tr("驱动挂载点"));
    tableHeader.append(tr("其他参数"));
    tableTerget.setHorizontalHeaderLabels(tableHeader);
    tableTerget.setCurrentCell(-1,0);
    butAdd.setText(QObject::tr("添加"));
    butDel.setText(QObject::tr("删除"));
    butOk.setText(QObject::tr("确定"));
    butCel.setText(QObject::tr("取消"));
    connect(&butAdd,SIGNAL(clicked()),this,SLOT(addTerget()));
    connect(&butDel,SIGNAL(clicked()),this,SLOT(delTerget()));
    connect(&butOk,SIGNAL(clicked()),this,SLOT(accept()));
    connect(&butCel,SIGNAL(clicked()),this,SLOT(reject()));
    hLayout = new QHBoxLayout;
    vLayout = new QVBoxLayout;
    hLayout->addWidget(&butAdd);
    hLayout->addWidget(&butDel);
    hLayout->addWidget(&butOk);
    hLayout->addWidget(&butCel);
    vLayout->addWidget(&tableTerget);
    vLayout->addLayout(hLayout);
    setLayout(vLayout);
}

DialogTerget::~DialogTerget()
{
    delete ui;
}
void    DialogTerget::addTerget()
{
   unsigned     int tempNewIndex;
   tempNewIndex    =   tableTerget.rowCount();
   if(tempNewIndex > 7)
   {
       QMessageBox::warning(this,tr("警告"),tr("超过最大可连接硬件数！"));
       return;
   }
   tableTerget.insertRow(tempNewIndex);
   tableTerget.setCurrentCell(-1,0);
}

void    DialogTerget::addTerget(QString strTerget,  QString strMethod,
                                QString strPort,    QString strOther)
{
    unsigned     int tempNewIndex;
    tempNewIndex    =   tableTerget.rowCount();
    if(tempNewIndex > 7)
    {
        QMessageBox::warning(this,tr("警告"),tr("超过最大可连接硬件数！"));
        return;
    }
    tableTerget.insertRow(tempNewIndex);
    tableTerget.setItem(tempNewIndex,0,new QTableWidgetItem(strTerget));
    tableTerget.setItem(tempNewIndex,1,new QTableWidgetItem(strMethod));
    tableTerget.setItem(tempNewIndex,2,new QTableWidgetItem(strPort));
    tableTerget.setItem(tempNewIndex,3,new QTableWidgetItem(strOther));
    tableTerget.setCurrentCell(-1,0);
}

void    DialogTerget::delTerget()
{
    int tempIndex;
    tempIndex = tableTerget.currentRow();
    if(tempIndex == -1)
    {
        QMessageBox::warning(this,tr("警告"),tr("请选择需要删除的目标"),QMessageBox::Yes);
        return;
    }
    tableTerget.removeRow(tempIndex);
    tableTerget.setCurrentCell(-1,0);
}

void    DialogTerget::accept()
{
    QDialog::accept();
}
