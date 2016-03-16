#ifndef quadtree_h
#define quadtree_h
#include "obiekt.h"
/** \brief Implementacja drzewa czwórkowego.
 * Używa następujących klas:
 * obiekt
 */

class quadtree
{
private:
        sf::FloatRect qquad;/**< \brief Pole przechowujące wymiary okna*/
        static const int MAX_ELEMENTS=2;/**< \brief Pojemność węzła*/
        static const int MAX_NODES=4; /**< \brief Głębokość drzewa*/
        int level; /**< \brief Poziom wezla*/
        std::vector<obiekt *> objects; /**< \brief Lista obiektów leżących w danej kwarcie*/
        quadtree *parent; /**< \brief Wskaźnik na przodka*/
        quadtree *nodes[4]; /**< \brief Wskaźniki na 4 potomków*/
public:


    quadtree(int pLevel, sf::FloatRect _quad); /**< \brief Konstruktor z 2 argumentami*/
    ~quadtree(); /**< \brief Destruktor. Wywołuje metode clear dla każdego potomka węzła, dla którego metoda clear została już wywołana*/
    void clear(); /**< \brief Czyści całe drzewo*/
    void split(); /**< \brief Dzieli powierzchnię na 4 części.Wywoływana w momencie przepełnienia węzła*/
    std::vector<int> getIndex(sf::FloatRect pRect); /**< \brief Zwraca kwarty w których leży zadany obiekt*/
    void insert(obiekt *&pRect) ; /**< \brief Dodaje obiekt do drzewa*/
    std::vector <sf::FloatRect> bounds(std::vector <sf::FloatRect> &); /**< \brief Zwraca krawędzie kwart w postaci vektora obiektów FloatRect (SFML objects)*/
    std::vector<obiekt*>retrieve(std::vector <obiekt*> &returnObjects, sf::FloatRect pRect); /**< \brief Zwraca obiekty z którymi może kolidować zadany objekt*/

};
#endif
