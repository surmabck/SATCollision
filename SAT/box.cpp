
#include "box.h"

 box::box()
  {
     iw=0 ;
  }
 void box::setPoint(int nr,int x, int y)
  {
      tw[nr].x=x;
      tw[nr].y=y;
        iw++;
  }
    void box::setPointCount(int x)
    {
        iw=x;
    }
    vector2d box::getVect2d(int nr)
    {
        vector2d ret((tw[(nr+1) % iw].x-tw[nr].x )   ,   (tw[(nr+1)%iw].y-tw[nr].y));

        return( ret );
    }
    int box::getIw()
    {
        return iw;
    }
  float box::dotProduct(vector2d vect,int x)
  {
      return (vect.getX()*tw[x].x+vect.getY()*tw[x].y);
  }
