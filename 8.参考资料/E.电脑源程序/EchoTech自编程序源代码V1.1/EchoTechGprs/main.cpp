#include <QtGui>
#include <QtCore>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("System"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("System"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("System"));
    QPixmap splashJpg("EchoTech.jpg");
    QSplashScreen splashScreen(splashJpg);
    splashScreen.show();
    a.processEvents();
    MainWindow w;
    w.show();
    splashScreen.finish(&w);
    return a.exec();
}
