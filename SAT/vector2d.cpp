#include "vector2d.h"
#include <math.h>
    vector2d::vector2d()
    {
        x=0;
        y=0;
    }
    vector2d::vector2d(sf::Vector2f vec)
    {
        this->x=vec.x;
        this->y=vec.y;
        normalizuj();
    }
    vector2d::vector2d(int x, int y)
    {

        this->x=x;
        this->y=y;
        normalizuj();
    }
    float vector2d::getX()
    {
        return x;
    }
    float vector2d::getY()
    {
        return y;
    }
    void vector2d::setXY(int x,int y)
    {
        this->x=x;
        this->y=y;
    }
    float vector2d::dlugosc()
    {
        return sqrt(x*x+y*y);
    }
    void vector2d::normalizuj()
    {

        int tmp;
        tmp=this->x;
        this->x=y;
        this->y=-tmp;
        float mag;

        mag=dlugosc();

        x=(x/mag);
        y=(y/mag);



    }
