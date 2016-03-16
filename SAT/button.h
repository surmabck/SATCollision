#ifndef button_h
#define button_h
#include <SFML/Graphics.hpp>
#include <string>
#include <boost/bind/bind.hpp>
#include <boost/function.hpp>
class button : public sf::Drawable
{
private:
    sf::Sprite sprite;
    sf::Font font;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(sprite);
    }

    int width;
    int height;
    int x;
    int y;
    sf::Text tekst;
public:
    button ();
    void setButton(int w,int h,int x,int y,std::string *s);
    boost::function<void()> onClick;
    bool isCollid(sf::RenderWindow &window);


};
#endif
