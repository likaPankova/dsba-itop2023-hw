#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QTranslator trans;
//    trans.load("trans_ru", a.applicationDirPath());
//    QCoreApplication::installTranslator(&trans);
    MainWindow w;
    w.show();
    return a.exec();
}
