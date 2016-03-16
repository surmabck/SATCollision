#ifndef menus_h
#define menus_h
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "button.h"
class menus : public sf::Drawable
{
private:

    button *buttons;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (int i=0;i<5;i++)
        {
            target.draw(buttons[i]);
        }
    }

public:
    menus(std::string *s,int x);
    void isCollid(sf::Vector2f mouse);
};
#endif
