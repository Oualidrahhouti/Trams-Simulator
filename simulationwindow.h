#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <QWidget>
#include<QPainter>
#include"ligne.h"
#include<QtGui>
#include<QtCore>
#include<QRect>
#include<QTimer>
#include<QGridLayout>

class MainWindow;
class arret;
class simulationwindow : public QWidget
{
    Q_OBJECT
public:
    explicit simulationwindow(Ligne* ligne,QWidget *parent = nullptr);
    ~simulationwindow();
    QTimer* simulationTimer;
private:
    Ligne* firstLine;
    void DrawStops(QPainter& p);
    void LinkBetweenStops(QPainter& p);
    void DrawTrams(QPainter& p);
    void UpdateTramsPositions();
    friend class MainWindow;
protected:
    void paintEvent(QPaintEvent *e);
};

#endif // SIMULATIONWINDOW_H
