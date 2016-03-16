#include "mouse.h"
mouse::mouse()
{

    this->state=FREE;
    this->shape.setPointCount(4);
    this->shape.setScale(0.2,0.2);


}
void mouse::setWindow(sf::RenderWindow *&win)
{
    window=win;
    sf::Vector2f v2f (sf::Mouse::getPosition(*window));
    this->shape.setPosition(v2f);
    actualPosition[0]=v2f.x;
    actualPosition[1]=v2f.y;
}
void mouse::stateBusy()
{
    this->state=BUSY;
}
void mouse::stateFree()
{
    this->state=FREE;
}
bool mouse::getState()
{
    if (this->state==BUSY) return false;
    else return true;
}
int mouse::deltaY()
{
    return actualPosition[1]-pastPosition[1];
}
int mouse::deltaX()
{
    return actualPosition[0]-pastPosition[0];
}
void mouse::update()
{
    sf::Vector2f v2f (sf::Mouse::getPosition(*window));
    pastPosition[0]=actualPosition[0];
    pastPosition[1]=actualPosition[1];
    actualPosition[0]=v2f.x;
    actualPosition[1]=v2f.y;


    this->shape.setPosition(v2f);
}
