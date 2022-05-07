#ifndef ARRET_H
#define ARRET_H
#include<QString>
#include"position.h"
class arret
{
public:
    arret(QString n,float stopTime);
    ~arret();
    QString GetName();
    float GetTimeToStop();
    position GetPosition();
    void SetPosition(position p);
    arret* GetPreviousStop();
    arret* GetNextStop();
private:
    QString name;
    float timeToStop;
    position location;
    arret* previousStop;
    arret* nextStop;
    friend class Ligne;
};

#endif // ARRET_H
