#ifndef POSITION_H
#define POSITION_H
#include"cmath"

class position
{
public:
    position();
    position(float newX,float newY);
    ~position();
    float getX();
    float getY();
    void setX(float newX);
    void setY(float newY);
    bool operator==(const position& p);
    float operator-(const position& p);
private:
    float x;
    float y;
    //the value to ignore while comparing two positions
    float acceptedMargin;
};

#endif // POSITION_H
