#ifndef kolizje_h
#define kolizje_h
#include "box.h"
#include "quadtree.h"
class obiekt;
/** \brief Opisuje przedział [min,max]*/
struct range
{
    float min, /**< \brief Minimalna wartość przedziału */
          max; /**< \brief Maksymalna Wartość przedziału */
};
/** \brief Obsługa kolizji obiektów
 * Używa następujących klas:
 * obiekt,box,quadtree
 */

class kolizje
{
private:
    range res1,/**<Obiekt struktury range. */
        res2; /**<Obiekt struktury range. */
    vector2d res;/**<MTV. Prowizoryczne rozwiązanie, ponieważ każda figura powininna mieć swój mtv.*/

    /** \brief rzutuje figurę f1 na wektor vect_normal
     *
     * \param f1 obiekt sf::CircleShape przekonwertowany na obiekt klasy box
     * \param vect_normal wektor prostopadly (metoda klasy vector2d.getVect2d(int) zwraca wektor prostopadly znormalizowany) znormalizowany
     * \return  rzut figury na wektor prostopadły znormalizowany
     *
     */
    range projekcja(box f1,vector2d vect_normal);
    /** \brief Sprawdza czy przedziały x1 i x2 mają część wspólną
     * \param x1 rzut pierwszej figury na prostą
     * \param x2 rzut drugiej figury na prostą
     * \return Zasieg pokrywania sie dwoch odcinkow na prostej
     */

    float getInteresction(range x1,range x2);
    /** \brief Sprawdza czy pomiedzy s1 i s2 występuje kolizja
     * \param s1 Obiekt sf::Circleshape
     * \param s2 Obiekt sf::CircleShape
     * \param res Wektor w którym zostanie zwrócony MTV
     * \return True Występuje kolizja. False kolizja nie występuje.
     */
    public:
    bool kolizja(sf::CircleShape s1,sf::CircleShape s2,vector2d &res);

    /** \brief Metoda uruchamiana w celu sprawdzenia kolizji wielu obiektów zawartych w kontenerze polygons
     * \param polygons Kontener z obiektami do sprawdzenia
     * \param state Określa rodzaj algorytmu sprawdzania kolizji (Bruteforce lub z użyciem quadtree)
     * \param quadTree Wskaźnik na quadtree, przekazywany z metody wywołującej tą metode.
     * \return ilość porównań wykonanych dla całego kontenera obiektów
     */
    long start(std::vector<obiekt*>&,bool state,quadtree *&quadTree);
};
#endif
