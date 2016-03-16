
#ifndef vector2d_h
#define vector2d_h
#include <SFML/Graphics.hpp>
/** \brief Reprezentuje wektor swobodny (bez punktu zaczepienia)
 */
class vector2d
{
public:
    float x, /**< \brief Współrzędna X wektora*/
          y; /**< \brief Współrzędna Y wektora */

public:
    vector2d(); /**< \brief Konstruktor domyślny*/
    vector2d(sf::Vector2f vec); /**< \brief Konstruktor z argumentem \param vec Obiekt powstaje na podstawie współrzędnych tego argumentu */
    vector2d(int x, int y); /**< \brief Konstruktor z dwoma argumentami \param x Współrzędna x dla obiektu vector2d \param Współrzędna y dla obiektu vector2d*/
    float getX(); /**< \brief Zwraca współrzędną x*/
    float getY(); /**< \brief Zwraca współrzędna y*/
    void setXY(int x,int y); /**< \brief Ustawia współrzędne wektora*/
    float dlugosc(); /**< \brief Zwraca długość wektora*/
    void normalizuj(); /**< \brief Sprowadza długość wektora do przedzialu [0,1], przy zachowaniu orginalnego kierunku i zwrotu*/
};
#endif
