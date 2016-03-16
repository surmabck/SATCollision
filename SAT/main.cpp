#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "box.h"
#include "vector2d.h"
#include "environment.h"
#include "engine.h"
#include "kolizje.h"
using namespace sf;




int main()
{
    srand(time(NULL));
    environment app;
    app.main_loop();

    return 0;
}
