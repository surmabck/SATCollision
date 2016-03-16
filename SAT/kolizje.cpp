#include "kolizje.h"
#include <iostream>
#include <cmath>
using namespace std;
/*
@ wykonujemy iloczyn skalarny dla kazdego boku figury i rzutujemy go na vector normalny (w zasadzie juz prostopadly)
@ wyliczamy najmniejszy i najwiekszy punkt rzutu na wektor, w ten sposob wyliczamy zasieg figury w danym rzucie
@ zwracamy ten zasieg (typ range)
*/
range kolizje::projekcja(box f1,vector2d vect_normal)
{
        float min,max,tmp;
        min=f1.dotProduct(vect_normal,0);
        max=min;
            for (int i=0; i<f1.getIw();i++)
            {
                tmp=f1.dotProduct(vect_normal,i);
                if (tmp>max) max=tmp;
                if(tmp<min) min=tmp;
           }
        range result;
        result.max=max;
        result.min=min;
        return result;

}
/*
@ getIntersection zwraca liczbe float okreslajacą zasieg pokrywania sie dwoch odcinkow na prostej
@
@
*/
float kolizje::getInteresction(range x1,range x2)
{
        float result;
        if (x1.max>x2.max) result=x1.min-x2.max;
        else result=x2.min-x1.max;
        return result;
}
/*
@ funkcja zwraca true jesli wystepuje kolizja, false jesli nie
@ dodatkowo argument res zawiera minimalny wektor o ktory trzeba przesunac figure 1 w razie kolizji
@ aby usunac kolizje
*/
bool kolizje::kolizja(sf::CircleShape s1,sf::CircleShape s2,vector2d &res)
{
        box f1,f2;
        sf::Transform g1,g2;
        g1=s1.getTransform();
        g2=s2.getTransform();
            float intersekcja;
        float wart;
        float najw;
        res.setXY(10000,10000);
       // z podanych figur klasy sf::circleshape tworzymy figury mojej klasy box
        for (int i=0;i<s1.getPointCount();i++)
        {
            f1.setPoint(i,
                        g1.transformPoint(s1.getPoint(i).x,s1.getPoint(i).y).x,
                        g1.transformPoint(s1.getPoint(i).x,s1.getPoint(i).y).y); //punkt po rotacji
        }
        for (int i=0;i<s2.getPointCount();i++)
        {
            f2.setPoint(i,
                        g2.transformPoint(s2.getPoint(i).x,s2.getPoint(i).y).x,
                        g2.transformPoint(s2.getPoint(i).x,s2.getPoint(i).y).y); //punkt po rotacji
        }



        //tworzymy vectory normalne( w zasadzie od razu prostopadle) do bokow pierwszej figury, potem sprawdzamy intersekcje

            for (int i=0;i<f1.getIw();i++)
            {
                vector2d vect_normal=f1.getVect2d(i);
                res1=projekcja(f1,vect_normal);
                res2=projekcja(f2,vect_normal);
                intersekcja=getInteresction(res1,res2);
                if (intersekcja>=0) return false;
                else
                {
                    wart=intersekcja*((res1.min-res2.min)/abs(res1.min-res2.min));
                    if ((wart<res.dlugosc())&&(wart>0))
                    {
                        res.x=vect_normal.x*intersekcja;
                        res.y=vect_normal.y*intersekcja;
                    }
                }
            }
            //tworzymy vectory normalne(w zasadzie od razu prostopadle) do bokow drugiej figury, potem sprawdzamy intersekcje
            for (int i=0;i<f2.getIw();i++)
            {
                vector2d vect_normal=f2.getVect2d(i);
                res1=projekcja(f1,vect_normal);
                res2=projekcja(f2,vect_normal);
                intersekcja=getInteresction(res1,res2);
                if (intersekcja>=0) return false;
                else
                {
                    wart=intersekcja*((res2.min-res1.min)/abs(res2.min-res1.min));
                    if ((wart<res.dlugosc())&&(wart>0))
                    {
                        res.x=vect_normal.x*intersekcja*-1;
                        res.y=vect_normal.y*intersekcja*-1;
                    }
                }
            }

    return true;
}
/*
@ metoda przyjmuje kontener z obiektami do sprawdzenia, zmienna boolowska okreslajaca rodzaj sprawdzania kolizji
@ bruteforce lub quadtree
@ zwraca liczbe long okreslajaca ilosc porownan wykonanych dla calego kontenera
*/
long kolizje::start(std::vector<obiekt*> &polygons,bool state,quadtree *&quadTree)
{
long tmp=0;
//bruteforce
    if (state==false)
    {
        for (int j=0; j<polygons.size(); j++)
            for (int i=0; i<polygons.size() ; i++)
                if (i!=j)
                {
                    tmp++;
                     if (polygons[i]->getBoundingBox().intersects(polygons[j]->getBoundingBox()))
                     if (kolizja(polygons[j]->getShape(),polygons[i]->getShape(),res)==true)
                     {
                        polygons[i]->setCollid(true);
                        polygons[j]->setCollid(true);
                     }

                }
    }
    else
    {
//quadtree
        std::vector <obiekt*> obiekty;
        for (int i=0; i<polygons.size();i++)
        {
            obiekty.clear();
            quadTree->retrieve(obiekty,polygons[i]->getBoundingBox());
                for (int j=0; j<obiekty.size();j++)
                {
                    if (polygons[i]->isCollid())
                    {
                        if(obiekty[j]->isCollid()) break;
                    }
                    if (polygons[i]!=obiekty[j])
                    {
                        tmp++;
                        if (polygons[i]->getBoundingBox().intersects(obiekty[j]->getBoundingBox()))

                        if (kolizja(polygons[i]->getShape(),obiekty[j]->getShape(),res)==true)
                        {
                                polygons[i]->setCollid(true);
                                obiekty[j]->setCollid(true);
                        }
                    }

                }


        }
    }
    return tmp;
}
