#ifndef DIALOGTERGET_H
#define DIALOGTERGET_H

#include <QDialog>
#include    <QtGui>
#include    <QtCore>

namespace Ui {
    class DialogTerget;
}

class DialogTerget : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTerget(QWidget *parent = 0);
    ~DialogTerget();

private:
    Ui::DialogTerget *ui;

public:
    QTableWidget    tableTerget;
    QPushButton butAdd;
    QPushButton butDel;
    QPushButton butOk;
    QPushButton butCel;
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
public slots:
    void    addTerget();
    void    delTerget();
    virtual void    accept();
public:
    void    addTerget(QString   strTerget,  QString strMethod,
                      QString   strPort,    QString strOther);
};

#endif // DIALOGTERGET_H
