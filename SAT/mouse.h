#ifndef mouse_h
#define mouse_h
#include <SFML/Graphics.hpp>
#include "obiekt.h"
/** \brief Reprezentuje mysz
 * Używa następujących klas: obiekt
 */

class mouse : public obiekt
{
    /** \brief Określa stany myszy
     */

    enum states
    {
            BUSY, /**< \brief Mysz jest 'zajęta' tzn. że jakiś obiekt jest do niej przyczepiony */
            FREE /**< \brief Mysz jest 'wolna' tzn. że żaden obiekt nie jest do niej przyczepiony */
    };
    states state; /**< \brief Pole typu states*/
    sf::RenderWindow *window; /**< \brief Wskaźnik na główne okno aplikacji*/
    int actualPosition [2]; /**< \brief Aktualna pozycja myszy [0]->x, [1]->y*/
    int pastPosition [2]; /**< \brief Poprzednia pozycja myszy [0]->x, [1]->y*/
public:
    mouse(); /**< \brief Konstruktor */
    void setWindow(sf::RenderWindow *&win); /**< \brief Ustawia wskaźnik window na obiekt przekazany jako argument*/
    int deltaX(); /**< \brief Zwraca odległość jaką mysz pokonała w ostatniej klatce względem osi X*/
    int deltaY();/**< \brief Zwraca odległość jaką mysz pokonała w ostatniej klatce względem osi Y*/
    void stateBusy(); /**< \brief Ustawia stan myszy na BUSY */
    void stateFree(); /**< \brief Ustawia stan myszy na FREE */
    bool getState(); /**< \brief Zwraca aktualny stan myszy */
    void update(); /**< \brief Aktualizuje pozycje parametry myszy */
};
#endif // mouse_h
