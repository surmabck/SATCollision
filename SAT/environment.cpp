#include "environment.h"
#include "kolizje.h"
#include <iostream>
using namespace sf;
   environment::environment()
    {
        cfg = new config("config.cfg");
        image.loadFromFile("grafika/Demo.png");
        image.setSmooth(true);
        sprite.setTexture(image,false);

        sprite.scale(float(cfg->screenWidth)/float(sprite.getTexture()->getSize().x),float(cfg->screenHeight)/float(sprite.getTexture()->getSize().y));

        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        window.create(sf::VideoMode(cfg->screenWidth, cfg->screenHeight), "Kolizje SAT",sf::Style::Default, settings);
        font.loadFromFile("LemonMilk.otf");
        window.setFramerateLimit(60);
        window.setVerticalSyncEnabled(false);
        state=MENU;
    }
    environment::~environment()
    {
        delete cfg;
    }

void environment::main_loop()
{
while(state != END)
 {
  switch (state)
  {
  case MENU:
   menu();
   break;
  case QT:
   run("QT");
   break;
  case SAT:
    run("SAT");
    break;
  }
 }
}
void environment::menu()
{
 sf::Text title("Kolizje SAT",font,40);
 title.setStyle(Text::Bold);

 title.setPosition(cfg->screenWidth/2-title.getGlobalBounds().width/2,20);

 const int ile = 3;

 Text tekst[ile];

 std::string str[] = {"QuadTree Test","SAT Collision","Exit"};
 for(int i=0;i<ile;i++)
 {
  tekst[i].setFont(font);
  tekst[i].setCharacterSize(40);

  tekst[i].setString(str[i]);
  tekst[i].setPosition(cfg->screenWidth/2-tekst[i].getGlobalBounds().width/2,cfg->screenHeight/2+50+i*50);
 }

 while(state == MENU)
 {
    Vector2f mouse ( Mouse::getPosition(window));
  Event event;

  while(window.pollEvent(event))
  {
   //Wciśnięcie ESC lub przycisk X
   if(event.type == Event::Closed || event.type == Event::KeyPressed &&
    event.key.code == Keyboard::Escape)
    state = END;
     //kliknięcie EXIT
    if(tekst[2].getGlobalBounds().contains(mouse) &&
    event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
   {
    state = END;
   }
   //Klikniecie QT
   else if(tekst[0].getGlobalBounds().contains(mouse) &&
    event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
   {
    state = QT;
   }
  else if(tekst[1].getGlobalBounds().contains(mouse) &&
    event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
   {
    state = SAT;
   }

  }

  for(int i=0;i<ile;i++)
   if(tekst[i].getGlobalBounds().contains(mouse))
    tekst[i].setColor(Color::Cyan);
   else tekst[i].setColor(Color::White);

  window.clear();
  window.draw(sprite);
  window.draw(title);
  for(int i=0;i<ile;i++)
   window.draw(tekst[i]);
  window.display();
 }
}
void environment::run(std::string str)
{

        engine app(window,str,cfg);
        app.runEngine();
        state=MENU;
};
