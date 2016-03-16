#ifndef config_h
#define config_h
#include <string>
#include <fstream>
#include <iostream>
/** \brief Odczytuje plik config.cfg i ustawia parametry okna takie jak: wysokosc okna, szerokosc okna, szerokosc prawego menu, wysokosc dolnego menu, rozmiar fontu itd..
 */

class config
{
public:
    int width, /**< \brief Szerokość ekranu wewnętrznego */
        height; /**< \brief Wysokosc ekranu wewnętrznego*/
    int screenWidth, /**< \brief Szerokosc calego okna */
        screenHeight; /**< \brief Wysokosc calego okna */
    int menuWidth, /**< \brief szerokosc prawego menu */
        menuHeight; /**< \brief wysokosc dolnego hud */
    int fontsize; /**< \brief wielkosc fontu*/
    config(const char *); /**< \brief Konstruktor */
    int parse(std::string&); /**< \brief Parsuje tekst, wyluskuje liczbe ze stringa po odnalezieniu ':'  w tekscie */
    int strToInt(std::string s); /**< \brief Konwertuje string na liczbe*/
    void input(int value,std::string str); /**< \brief  Ustawia pola wartosciami uzyskanymi w pliku */
};
#endif // config_h
