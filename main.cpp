#include "mainwindow.h"
#include "simulationwindow.h"
#include <QApplication>
#include<QPainter>
#include<QLineF>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}