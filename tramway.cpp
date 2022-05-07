#include "tramway.h"

tramway::tramway(arret* stop,float safetyDistance):maxSpeed(0.1),currentSpeed(maxSpeed),defaultDirection(true),safeDistance(safetyDistance),currentStop(stop),previousTramway(nullptr),nextTramway(nullptr)
{
    stopTimer=new QTimer();
    stopTimer->setSingleShot(true);
    connect(stopTimer,&QTimer::timeout,this,&tramway::Wait);
}
tramway::~tramway()
{
}
tramway* tramway::GetPreviousTramway()
{
    return previousTramway;
}
tramway* tramway::GetNextTramway()
{
    return nextTramway;
}
void tramway::SetPreviousTramway(tramway *t)
{
    previousTramway=t;
}
void tramway::SetNextTramway(tramway *t)
{
    nextTramway=t;
}
position tramway::GetPosition()
{
    return location;
}
void tramway::SetPosition(position p)
{
    location=p;
}
arret* tramway::GetCurrentStop()
{
    return currentStop;
}

void tramway::Stop()
{
    currentSpeed=0;
    float timeToStop=currentStop->GetTimeToStop();
    stopTimer->start(timeToStop);
}
void tramway::Move()
{
    position p=location;
    bool isSafe;
    if(defaultDirection)
    {
        if(nextTramway!=nullptr)
            isSafe=((defaultDirection!=nextTramway->defaultDirection ) || ((defaultDirection==nextTramway->defaultDirection) && location-nextTramway->location >= safeDistance) );
        if(!nextTramway || isSafe)
            p=position(location.getX()+currentSpeed,location.getY());
    }
    else
    {
         if(previousTramway!=nullptr)
            isSafe=((defaultDirection!=previousTramway->defaultDirection) || ((defaultDirection==previousTramway->defaultDirection) && location-previousTramway->location >= safeDistance ));
         if(previousTramway!=nullptr || isSafe )
            p=position(location.getX()-currentSpeed,location.getY());
    }
    location=p;
}
void tramway::StartMovingLogic()
{
    if(currentSpeed!=0 && location==currentStop->GetPosition())
    {
        Stop();
    }
    else
        Move();
}

void tramway::Wait()
{
    currentSpeed=maxSpeed;
    if(defaultDirection)
    {
        if(currentStop->GetNextStop())
            currentStop=currentStop->GetNextStop();
        else
            ReverseDirection();
    }else
    {
        if(currentStop->GetPreviousStop())
            currentStop=currentStop->GetPreviousStop();
        else
            ReverseDirection();
    }
}

void tramway::ReverseDirection()
{
    defaultDirection=!defaultDirection;
}

bool tramway::SafeToMove()
{
    //find the closest tram
    tramway* currentTram=previousTramway;
    while(currentTram!=nullptr)
    {
        if((defaultDirection == currentTram->defaultDirection) && ((location-currentTram->location) < safeDistance))
            return false;
        currentTram=currentTram->previousTramway;
    }
    currentTram=nextTramway;
    while(currentTram!=nullptr)
    {
        if((defaultDirection == currentTram->defaultDirection) && ((location-currentTram->location) < safeDistance))
            return false;
        currentTram=currentTram->nextTramway;
    }
    return true;
}

bool tramway::isMoving()
{
    return currentSpeed!=0;
}

bool tramway::GetDefaultDirection()
{
    return defaultDirection;
}
