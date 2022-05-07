#include "ligne.h"

Ligne::Ligne(float distanceStops):distanceBetweenStops(distanceStops),firstStop(nullptr),firstTramway(nullptr)
{

}
Ligne::~Ligne()
{
    tramway* crtTram=firstTramway;
    arret* crtStop=firstStop;
    while(crtStop!=nullptr)
    {
        arret* as=crtStop;
        if(crtStop->GetNextStop()!=nullptr)
        {
            crtStop->GetNextStop()->previousStop=nullptr;
        }
        crtStop=crtStop->GetNextStop();
        delete as;
        as=nullptr;
    }
    while(crtTram!=nullptr)
    {
        tramway* as=crtTram;
        if(crtTram->GetPreviousTramway()!=nullptr)
        {
            crtTram->GetPreviousTramway()->SetNextTramway(nullptr);
        }
        crtTram=crtTram->GetPreviousTramway();
        delete as;
        as=nullptr;
    }
}
float Ligne::GetDistanceBetweenStops()
{
    return distanceBetweenStops;
}
tramway* Ligne::GetFirstTramway()
{
    return firstTramway;
}
arret* Ligne::GetfirstStop()
{
    return firstStop;
}
void Ligne::AddTramway(tramway* t)
{
    if(!firstTramway)
    {
        firstTramway=t;
        return;
    }
    if(!firstTramway->GetPreviousTramway())
    {
        t->SetNextTramway(firstTramway);
        firstTramway->SetPreviousTramway(t);
        return;
    }
    tramway* crt=firstTramway;
    while(crt->GetPreviousTramway())
        crt=crt->GetPreviousTramway();
     crt->SetPreviousTramway(t);
     t->SetNextTramway(crt);
}
void Ligne::AddStop(arret *s)
{
    if(!firstStop)
    {
        firstStop=s;
        return;
    }
    if(!firstStop->nextStop)
    {
        s->previousStop=firstStop;
        firstStop->nextStop=s;
        return;
    }

    arret* crt=firstStop;
    while(crt->nextStop)
        crt=crt->nextStop;
     crt->nextStop=s;
     s->previousStop=crt;
}

void Ligne::SetLocationOfStops()
{
    if(!firstStop)
        return;
    firstStop->SetPosition(position(50,50));
    arret* currentStop=firstStop->nextStop;
    while(currentStop)
    {
        position wantedPosition(currentStop->previousStop->GetPosition().getX()+distanceBetweenStops,
                           currentStop->previousStop->GetPosition().getY());
        currentStop->SetPosition(wantedPosition);
        currentStop=currentStop->nextStop;
    }
}

void Ligne::InitializeTramways()
{
    if(!firstStop || !firstTramway)
        return;
    tramway* currentTramway=firstTramway;
    while(currentTramway)
    {
        currentTramway->SetPosition(firstStop->GetPosition());
        currentTramway=currentTramway->GetPreviousTramway();
    }
}

