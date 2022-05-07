#include "simulationwindow.h"
simulationwindow::simulationwindow(Ligne* ligne,QWidget *parent)
    : QWidget{parent},firstLine(ligne)
{
    resize(width(),height()/4);
    firstLine->SetLocationOfStops();
    firstLine->InitializeTramways();
    //Set Simulation Time
    simulationTimer=new QTimer(this);
    connect(simulationTimer,&QTimer::timeout,this,&simulationwindow::close);
    //Set refresh positions time
    QTimer* timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&simulationwindow::UpdateTramsPositions);
    timer->start(1);
}

simulationwindow::~simulationwindow()
{
    qDebug()<<"simulation";
    delete firstLine;
    firstLine=nullptr;
}
void simulationwindow::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    DrawStops(p);
    LinkBetweenStops(p);
    DrawTrams(p);
}

void simulationwindow::DrawStops(QPainter& p)
{
    arret* currentStop=firstLine->GetfirstStop();
    while(currentStop)
    {
        QPoint centerOfCircle(currentStop->GetPosition().getX(),currentStop->GetPosition().getY());
        p.drawEllipse(centerOfCircle,5,5);
        currentStop=currentStop->GetNextStop();
    }
}

void simulationwindow::LinkBetweenStops(QPainter& p)
{
    arret* currentStop=firstLine->GetfirstStop();
    while(currentStop->GetNextStop())
    {
        arret* nextStop=currentStop->GetNextStop();
        QPainterPath path;
        QPoint currentStopPosition=QPoint(currentStop->GetPosition().getX(),currentStop->GetPosition().getY());
        QPoint nextStopPosition=QPoint(nextStop->GetPosition().getX(),nextStop->GetPosition().getY());
        path.moveTo(currentStopPosition);
        path.lineTo(nextStopPosition);
        p.drawPath(path);
        currentStop=nextStop;
    }
}

void simulationwindow::DrawTrams(QPainter &p)
{
    //assign colors depends on direction and speed of tram
    QColor red=QColor(255,0,0);
    QColor green=QColor(0,255,0);
    QColor blue=QColor(0,0,255);
    QSize tramwaysDimensions=QSize(7,7);
    tramway* currentTramway=firstLine->GetFirstTramway();
    while(currentTramway)
    {
        QColor tramwayColor;
        if(!currentTramway->isMoving())
            tramwayColor=red;
        else if(currentTramway->GetDefaultDirection())
            tramwayColor=green;
        else
            tramwayColor=blue;
        //draw tram in the center of the fist stop
        QPoint currentTramwayPosition=QPoint(currentTramway->GetPosition().getX()-7/2,currentTramway->GetPosition().getY()-7/2);
        QRect drawedTramway=QRect(currentTramwayPosition,tramwaysDimensions);
        p.fillRect(drawedTramway,tramwayColor);
        currentTramway=currentTramway->GetPreviousTramway();
    }
}

void simulationwindow::UpdateTramsPositions()
{
    tramway* currentTramway=firstLine->GetFirstTramway();
    while(currentTramway)
    {
        currentTramway->StartMovingLogic();
        currentTramway=currentTramway->GetPreviousTramway();
    }
    update();
}

