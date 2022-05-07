#ifndef TRAMWAY_H
#define TRAMWAY_H
#include"position.h"
#include"arret.h"
#include<QTimer>
#include<QDebug>
class Ligne;
class tramway :  public QObject
{
public:
    tramway(arret* stop,float safetyDistance);
    ~tramway();
    tramway* GetPreviousTramway();
    tramway* GetNextTramway();
    void SetPreviousTramway(tramway* t);
    void SetNextTramway(tramway* t);
    void SetPosition(position p);
    position GetPosition();
    arret* GetCurrentStop();
    void StartMovingLogic();
    bool GetDefaultDirection();
    bool isMoving();
private:
    Ligne* line;
    position location;
    float maxSpeed;
    float currentSpeed;
    bool defaultDirection;
    void ReverseDirection();
    void Stop();
    void Move();
    void Wait();
    bool SafeToMove();
    float safeDistance;
    arret* currentStop;
    tramway* previousTramway;
    tramway* nextTramway;
    QTimer* stopTimer;
};

#endif // TRAMWAY_H
