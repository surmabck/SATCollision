#ifndef box_h
#define box_h
#include <SFML/Graphics.hpp>
#include "vector2d.h"
/** \brief Struktura reprezentująca wierzcholek*/
struct wierzcholek
{
    float x, /**< \brief Współrzędna x wierzchołka*/
          y; /**< \brief Współrzędna y wierzchołka*/
};
/** \brief Reprezentuje figure wypukłą i zaopatrzona jest w niezbędne funkcje dla algorytmu SAT. Używa następujących klas: vector2d*/
class box
{
private:
  wierzcholek tw[8]; /**< \brief Tablica wierzchołków */
  int iw; /**< \brief Ilosc wierzcholkow */

public:
box(); /**< \brief Konstruktor */
void setPoint(int nr,int x, int y); /**< \brief Dodaje wierzchołek do figury */
void setPointCount(int x); /**< \brief Ustawia ilość wierzchołków */
vector2d getVect2d(int nr); /**< \brief Zwraca bok okreslony parametrem nr jako kierunek i zwrot w postaci wektora swobodnego */
int getIw(); /**< \brief Zwraca ilość wierzchołków */
float dotProduct(vector2d vect,int x); /**< \brief Zwraca iloczyn skalarny wektora vect i wektora swobodnego zakończonego w wierzchołku o nr x*/
};
#endif
