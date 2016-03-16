#ifndef environment_h
#define environment_h
#include <SFML/Graphics.hpp>
#include "engine.h"
#include "config.h"
/** \brief Implementacja głównego menu.
 * Klasa tworzy okno aplikacji na podstawie konfiguracji z pliku config.cfg
 * Następnie uruchamia dany tryb pracy, wybrany przez użytkownika.
 * Używa następujących klas:
 * engine,config
 */

class environment
{
    private:
        /** Typ enum określający stan w którym znajduje się aplikacja.
         *  Przyjmuje cztery stany.
         */

        enum AppState
        {
            MENU, /**<Menu główne */
            QT, /**<QUADTREE TEST*/
            SAT,/**<SAT COLLISION  */
            END/**<Koniec programu  */
        };
        AppState state; /**<Pole typu AppState  */

public:
    config *cfg; /**< \brief Wskaznik na obiekt klasy config  */
    sf::Texture image; /**< \brief Tekstura dla 'sprite' */
    sf::Sprite sprite; /**< \brief Sprite tła */
    sf::RenderWindow window; /**< \brief Obiekt głównego okna aplikacji  */
    sf::Font font; /**< \brief Font*/
environment(); /**< \brief Konstruktor domyślny*/
~environment(); /**< \brief Destruktor*/

void main_loop(); /**< \brief Pętla w której obsługiwana jest zmiana stanu aplikacji*/
void menu(); /**< \brief Wyświetla menu*/
void run(std::string); /**< \brief Uruchamia dany tryb. Obsługuje dwie wartości dla argumentu string: "SAT" oraz "QT"*/
};
#endif // environment_h
