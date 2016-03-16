# SATCollision
1. Tematyka i analiza tematu
Projekt porusza problem wykrywania kolizji figur wypukłych w układzie
kartezjańskim metodą SAT. W celu zwiększenia wydajności aplikacji w przypadku wielu
obiektów, wykorzystana została struktura drzewa czwórkowego – quadtree.

2. Dane techniczne
Język programowania - C++
Aplikacja multiplatformowa
Aplikacja zorientowania obiektowo – OBB
Biblioteka graficzna SFML ver. 2.1
IDE - Code::Blocks
Kompilacja pod - Ubuntu 14.04 (32 bit)
Analiza programu - Valgrind

3. Kompilacja w systemie LINUX
I. Z wykorzystaniem IDE Code::Blocks - (link do opisu konfiguracji)
http://www.sfml-dev.org/tutorials/2.2/start-cb.php
II. Bez wykorzystania IDE
1. Instalacja biblioteki SFML z repozytorium poleceniem:
sudo apt-get install libsfml-dev
2. Kompilacja poleceniem
g++ -c main.cpp quadtree.cpp [wymieniamy wszystkie pliki projektu zakończone
rozszerzeniem .cpp] -I<sciezka_do_folderu_sfml>/include
3. Linkowanie skompilowanych plików z biblioteką SFML poleceniem
g++ main.o quadtree.o [wymieniamy wszystkie pliki z folderu zakończone
rozszerzeniem .o] -o projektSAT -L<sciezka_do_folderu_sfml>/lib -lsfml-graphics
-lsfml-window -lsfml-system
4. Mianowanie powstałego pliku wykonywalnym poleceniem
chmod 700 projektSAT
5. Uruchomienie projektu poleceniem
./projektSAT

