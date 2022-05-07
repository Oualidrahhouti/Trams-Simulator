#include "position.h"

position::position():x(0),y(0)
{
}

position::position(float newX,float newY):x(newX),y(newY),acceptedMargin(0.05f)
{
}

position::~position()
{
}

float position::getX()
{
    return x;
}

float position::getY()
{
    return y;
}
bool position::operator==(const position &p)
{
    return fabs(x-p.x)<acceptedMargin;
}

float position::operator-(const position& p)
{
    return fabs(x-p.x);
}
