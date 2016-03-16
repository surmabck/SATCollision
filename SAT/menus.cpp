#include "menus.h"
menus::menus(std::string *s,int x)
{
button *buttons = new button[x];
    for (int i=0;i<x;i++)
    {
        buttons[i].setButton(50,50,1200-50,700-50,s); //1200 i 700 to wielkosc okna, nalezy zmienic
    }

}
void menus::isCollid(sf::Vector2f mouse)
{

}
