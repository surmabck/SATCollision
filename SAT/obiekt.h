
#ifndef obiekt_h
#define obiekt_h
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
class vector2d;
/** \brief Reprezentacja figury wypukłej.
 *  Dziedziczy po klasie SFML sf::Drawable
 */

class obiekt: public sf::Drawable
{
protected:
    float vx,vy;  /**< \brief Skladowe wektora predkosci*/
    bool isDynamic; /**< \brief True obiekt dynamiczny.False obiekt statyczny. QT=true, SAT=false*/
    bool attachment; /**< \brief True obiekt jest przyczepiony do myszy. False obiekt nie jest przyczepiony do myszy*/
    bool polygonCollid; /**< \brief True obiekt koliduje z innym obiektem */
    sf::CircleShape shape; /**< \brief Rysowalna reprezentacja kształtu obiektu*/
    sf::RectangleShape bounding_box; /**< \brief Rysowalna reprezentacja bryły brzegowej obiektu*/
    sf::RectangleShape make_bounding_box(sf::FloatRect rect); /**< \brief Tworzy bounding_box obiektu */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const /**< \brief Rysuje obiekt i bounding box. Metoda dziedziczona po sf::Drawable*/
    {
        target.draw(shape);
        if (showBBox==true) target.draw(bounding_box);

    }

public:
    static bool showBBox; /**< \brief True bounding box jest rysowany. False bounding_box nie jest rysowany*/
    static int activePolygon; /**< \brief Index aktywnego obiektu. Obiekt staje sie aktwyny po kliknieciu w niego myszą*/
    obiekt(); /**< \brief Konstruktor domyślny*/
    /** \brief Konstruktor z czterema argumentami
     * \param x Ilość krawędzi
     * \param r Wielkość figury
     * \param iD Typ obiektu: True dynamiczny, False statyczny
     * \param xs Pozycja x
     * \param ys Pozycja y
     */

    obiekt(int x,float r,bool iD,int xs,int ys);
    ~obiekt(); /**< \brief Destruktor */
    bool isAttached(); /**< \brief Zwraca wartość pola attachment*/
    void setAttachment(bool i);  /**< \brief Ustawia pole attachment*/
    void setColor(sf::Color cl); /**< \brief Ustawia kolor wypelnienia obiektu*/
    void setBBoxColor(sf::Color cl);/**< \brief Ustawia kolor bounding_boxa*/
    void setOutlineColor(sf::Color cl); /**< \brief Ustawia kolor obramowania obiektu*/
    void setCollid(bool i); /**< \brief Ustawia zmienna polygonCollid*/
    sf::FloatRect getBoundingBox(); /**< \brief Zwraca bounding box obiektu*/
    bool isCollid(); /**< \brief Zwraca wartosc pola polygonCollid*/
    void rotate(); /**< \brief Obraca obiekt*/
    void setPosition(sf::Vector2f mouse); /**< \brief Ustawia pozycje obiektu*/
    sf::CircleShape getShape(); /**< \brief Zwraca obiekt jako sf::CircleShape*/
    void move(float,float); /**< \brief Przesuwa obiekt o podane wartosci*/
    void update(sf::Time el,int width,int height); /**< \brief Aktualizuje stan obiektu zmienne, bounding_box, przesuniecie obiektu o wektor predkosci etc. */
};
#endif
