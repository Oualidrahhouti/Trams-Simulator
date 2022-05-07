#ifndef LIGNE_H
#define LIGNE_H
#include"arret.h"
#include"tramway.h"
#include<QMessageBox>
#include<QtDebug>
class Ligne
{
public:
    Ligne(float distanceStops);
    ~Ligne();
    float GetDistanceBetweenStops();
    tramway* GetFirstTramway();
    arret* GetfirstStop();
    void AddTramway(tramway* t);
    void AddStop(arret* s);
    void SetLocationOfStops();
    void InitializeTramways();

private:
    float distanceBetweenStops;
    tramway* firstTramway;
    arret* firstStop;
};

#endif // LIGNE_H
