#ifndef DIALOGSOURCE_H
#define DIALOGSOURCE_H

#include <QDialog>
#include <QtGui>
#include <QtCore>

namespace Ui {
    class DialogSource;
}

class DialogSource : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSource(QWidget *parent = 0);
    ~DialogSource();

private:
    Ui::DialogSource *ui;

public:
    QLabel      labHard;
    QLabel      labSys;
    QComboBox   combHard;
    QComboBox   combSys;
    QPushButton butOk;
    QPushButton butCel;
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;

public slots:
    virtual void    accept();
};

#endif // DIALOGSOURCE_H
