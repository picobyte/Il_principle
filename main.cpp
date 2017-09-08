/*
 * (c) Picobyte 2017, GPL2
 */
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //seed random number
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
