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
    setWindowTitle(tr("����Ŀ������"));
    tableTerget.setColumnCount(4);
    tableTerget.setRowCount(0);
    QStringList tableHeader;
    tableHeader.append(tr("Ӳ��Ŀ��"));
    tableHeader.append(tr("���ӷ�ʽ"));
    tableHeader.append(tr("�������ص�"));
    tableHeader.append(tr("��������"));
    tableTerget.setHorizontalHeaderLabels(tableHeader);
    tableTerget.setCurrentCell(-1,0);
    butAdd.setText(QObject::tr("���"));
    butDel.setText(QObject::tr("ɾ��"));
    butOk.setText(QObject::tr("ȷ��"));
    butCel.setText(QObject::tr("ȡ��"));
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
       QMessageBox::warning(this,tr("����"),tr("������������Ӳ������"));
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
        QMessageBox::warning(this,tr("����"),tr("������������Ӳ������"));
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
        QMessageBox::warning(this,tr("����"),tr("��ѡ����Ҫɾ����Ŀ��"),QMessageBox::Yes);
        return;
    }
    tableTerget.removeRow(tempIndex);
    tableTerget.setCurrentCell(-1,0);
}

void    DialogTerget::accept()
{
    QDialog::accept();
}
