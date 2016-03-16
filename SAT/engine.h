#ifndef engine_h
#define engine_h
#include <SFML/Graphics.hpp>
#include "environment.h"
#include "kolizje.h"
#include "obiekt.h"
#include "mouse.h"
class config;
class vector2d;
class quadtree;
/** \brief Silnik zarządzający ruchem obiektów, sprawdzaniem kolizji, rysowaniem itd.
 * Używa następujących klas:
 * config,vector2d,quadtree,kolizje,environment,obiekt,mouse
 */
class engine
{
private:
    quadtree *quadTree; /**< \brief Wskaznik na quadtree */
    sf::RenderWindow *window; /**< \brief Wskaznik na okno, uzyskane z klasy environment*/
    config *cfg; /**< \brief Wskaznik na config, uzyskany z klasy environment*/
    sf::Texture textura; /**< \brief Tekstura dla sprite*/
    sf::Sprite sprite; /**< \brief Sprite background*/
    sf::Text tekst[11]; /**< \brief Tekst wyswietlany, nasze gui*/
    sf::Font font; /**< \brief Font uzywany do wyswietlania menu*/
    long ct; /**< \brief Zmienna trzymajaca liczbe porownan dla danego sposobu sprawdzania kolizji*/
    bool quadtreeState; /**< \brief True uzywamy quadtree do sprawdzania kolizji. False uzywamy bruteforce do sprawdzania kolizji*/
    bool drawquadtree; /**< \brief True rysujemy quadtree. false nie rysujemy quadtree*/
    bool st; /**< \brief Określa co updatować w danym trybie (tryby: QUADTREE TEST, SAT COLLISION)*/
    bool loop; /**< \brief True wykonujemy program. False wracamy do menu*/
    bool isDynamic; /**< \brief Tworzy: True obiekty dynamiczne. False obiekty statyczne. W zasadzie true dla opcji 1 w menu, false dla 2 opcji*/
    float scale; /**< \brief Okresla wielkosc obiektow.*/
    std::vector<obiekt*> polygons; /**< \brief Kontener poligonów*/
    std::vector<sf::FloatRect> b; /**< \brief Kontener krawędzi quadtree*/
    mouse mouseBounding; /**< \brief Obiekt klasy mouse, reprezentuje mysz*/
    vector2d res; /**< \brief MTV. Nie zaimplementowana obsługa*/
    kolizje kol; /**< \brief Obiekt klasy kolizje */;
public:
    engine (sf::RenderWindow &win,std::string,config *_cfg); /**< \brief Konstruktor z 3 argumentami */
    ~engine(); /**< \brief Destruktor*/


    void draw (float fps); /**< \brief Rysuje grafike*/
    void update(kolizje kol,sf::Time el); /**< \brief Aktualizuje obiekty*/
    void checkEvents(); /**< \brief Sprawdza eventy okna, takie jak klikniecie w X, klikniecie esc itd.*/
    void addPolygon(int x); /**< \brief Dodaje poligon do kontenera objektów*/
    void movement(); /**< \brief Obsluga ruchu przyczepionego obiektu do myszki. Obiekt podaza za myszka*/
    void checkColision(kolizje kol); /**< \brief Sprawdza kolizje*/
    void runEngine(); /**< \brief Główna pętla*/
};
#endif
