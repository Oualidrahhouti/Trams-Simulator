#include "arret.h"

arret::arret(QString n,float stopTime):name(n),timeToStop(stopTime),previousStop(nullptr),nextStop(nullptr)
{

}

arret::~arret()
{

}

QString arret::GetName()
{
    return name;
}

float arret::GetTimeToStop()
{
    return timeToStop;
}

position arret::GetPosition()
{
    return location;
}

void arret::SetPosition(position p)
{
    location=p;
}

arret* arret::GetPreviousStop()
{
    return previousStop;
}

arret* arret::GetNextStop()
{
    return nextStop;
}
