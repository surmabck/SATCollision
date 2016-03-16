#include "button.h"
button::button()
{
}
void button::setButton(int w,int h,int x,int y,std::string *s)
{
    width=w;
    height=h;
    this->x=x;
    this->y=y;
    //tekst.setString(*s);
    sprite.setTextureRect(sf::IntRect(50,50,100,100));
    sprite.setPosition(x,y);
    sprite.setColor(sf::Color(255,255,255,255));
    font.loadFromFile("LemonMilk.otf");
}
bool button::isCollid(sf::RenderWindow &window)
{
    sf::Vector2f mouse(sf::Mouse::getPosition(window));
        if(sprite.getGlobalBounds().contains(mouse)) return true;
        return false;
}
