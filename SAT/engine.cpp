 #include "engine.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
//konstruktor
engine::engine(sf::RenderWindow &win,std::string s,config *_cfg)
{
    window=&win;
    mouseBounding.setWindow(window);
    cfg=_cfg;
    loop=true;
    if(!textura.loadFromFile("grafika/Backg.png")) std::cout<<"Blad wczytania grafiki"<<std::endl;
    if (!font.loadFromFile("LemonMilk.otf")) std::cout<<"Blad wczytania fontu"<<std::endl;
    textura.setSmooth(true);
    textura.setRepeated(true);
    sprite.setTexture(textura);
    sprite.setScale(float(cfg->width)/float(textura.getSize().x),float(cfg->height)/float(textura.getSize().y));
    obiekt::activePolygon=0;
         std::string str[] = {"showBBoxes on","showBBoxes off","rotate","drawQT on","drawQT off","bruteforce","QT","ADD"};
          for(int i=0;i<8;i++)
             {
              tekst[i].setFont(font);
              tekst[i].setCharacterSize(15);

              tekst[i].setString(str[i]);
              tekst[i].setPosition(cfg->screenWidth-cfg->menuWidth,20+i*20);
             }
            tekst[8].setFont(font);
            tekst[8].setCharacterSize(cfg->fontsize);
            tekst[8].setColor(sf::Color::Red);
            tekst[8].setPosition(10,cfg->screenHeight-cfg->menuHeight);
            tekst[9].setFont(font);
            tekst[9].setCharacterSize(cfg->fontsize);
            tekst[9].setColor(sf::Color::Red);
            tekst[9].setPosition(200,cfg->screenHeight-cfg->menuHeight);
            tekst[10].setFont(font);
            tekst[10].setCharacterSize(cfg->fontsize);
            tekst[10].setColor(sf::Color::Red);
            tekst[10].setPosition(500,cfg->screenHeight-cfg->menuHeight);

            quadTree = new quadtree(0,sf::FloatRect(0,0,cfg->width,cfg->height));

    if (s=="QT")
    {
        scale=10;
        isDynamic=true;
        quadtreeState=true;
        drawquadtree=true;
        st=false;
    }
    if (s=="SAT")
    {
        scale=30;
        isDynamic=false;
        quadtreeState=false;
        drawquadtree=false;
        st=true;
    }
    addPolygon((rand()%5)+3);

}
engine::~engine()
{
    polygons.clear();
    delete quadTree;
}

 //rysuj
void engine::draw (float fps)
{
window->clear();

window->draw(sprite);


if (drawquadtree==true)
for (int i=0;i<b.size();i++)
{
    sf::RectangleShape bounding_box;
    bounding_box.setFillColor( sf::Color::Transparent );
    bounding_box.setOutlineColor( sf::Color::Black );
    bounding_box.setOutlineThickness( -2 );
    bounding_box.setSize(sf::Vector2f(b[i].width,b[i].height));
    bounding_box.setPosition( b[i].left, b[i].top);
    window->draw(bounding_box);
}
std::ostringstream ss;
ss << round(fps);
std::string s(ss.str());
s="FPS:"+s;
tekst[8].setString(s);

std::ostringstream sse ;
sse<<polygons.size();
std::string se(sse.str());
se="Objects: "+se;
tekst[9].setString(se);

std::ostringstream ssx ;
ssx<<ct;
std::string sx(ssx.str());
sx="Comparisons: "+sx;
tekst[10].setString(sx);
    for (int i=0; i<polygons.size();i++)
        {
            window->draw(*polygons[i]);
        }
    for (int i=0;i<11;i++)
    {
        window->draw(tekst[i]);
    }

window->display();
}




void engine::checkEvents()
{
sf::Event event;
sf::Vector2f mouse ( sf::Mouse::getPosition(*window));
    while (window->pollEvent(event))
    {

        if (event.type == sf::Event::Closed)    window->close();
        if(event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Escape) loop=false;

    }
bool mysz = sf::Mouse::isButtonPressed(sf::Mouse::Left);
if ((tekst[0].getGlobalBounds().contains(mouse)) && mysz)
        {
            obiekt::showBBox=true;

        }
        if ((tekst[1].getGlobalBounds().contains(mouse)) && mysz)
        {
            obiekt::showBBox=false;

        }
        if ((tekst[2].getGlobalBounds().contains(mouse)) && mysz)
        {
            polygons[obiekt::activePolygon]->rotate();
        }
        if ((tekst[3].getGlobalBounds().contains(mouse)) && mysz)
        {
            drawquadtree=true;
        }
        if ((tekst[4].getGlobalBounds().contains(mouse)) && mysz)
        {
            drawquadtree=false;
        }
        if ((tekst[5].getGlobalBounds().contains(mouse)) && mysz)
        {
            quadtreeState=false;
        }
        if ((tekst[6].getGlobalBounds().contains(mouse)) && mysz)
        {
            quadtreeState=true;
        }
        if ((tekst[7].getGlobalBounds().contains(mouse)) && mysz)
        {
            addPolygon((rand()%5)+3);
        }



for(int i=0;i<8;i++)
   if(tekst[i].getGlobalBounds().contains(mouse))
    tekst[i].setColor(sf::Color::Cyan);
   else tekst[i].setColor(sf::Color::White);
}




void engine::addPolygon(int x)
{
    obiekt *obj;
    if (isDynamic==true )  obj= new obiekt(x,scale,isDynamic,cfg->width/2,cfg->height/2);
    else obj = new obiekt(x,scale,isDynamic,(rand()% cfg->width/2)+cfg->width/2-200,(rand() % cfg->height/2)+cfg->height/2-200);
    polygons.push_back(obj);
}




void engine::movement()
{
   if(polygons[obiekt::activePolygon]->isAttached()) polygons[obiekt::activePolygon]->move(mouseBounding.deltaX(),mouseBounding.deltaY());
}


void engine::checkColision(kolizje kol)
{
    ct=kol.start(polygons,quadtreeState,quadTree);
}



void engine::update(kolizje kol,sf::Time el)
{
b.clear();
quadTree->bounds(b);
quadTree->clear();

    sf::Vector2f mouse ( sf::Mouse::getPosition(*window));

    if( !sf::Mouse::isButtonPressed( sf::Mouse::Left ) ) mouseBounding.stateFree();
        for (int i=0;i<polygons.size();i++)
        {
               if (polygons[i]->isCollid()==false) polygons[i]->setColor(sf::Color::White);
                    else polygons[i]->setColor(sf::Color::Red);
                polygons[i]->setCollid(false);
                quadTree->insert(polygons[i]);
              if (!isDynamic)
              {
                    if( !sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
                    polygons[i]->setAttachment(false);
                    if (mouseBounding.getState())
                    if (kol.kolizja(polygons[i]->getShape(),mouseBounding.getShape(),res)==true)
                    {
                        if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
                        {
                                obiekt::activePolygon=i;
                                polygons[i]->setAttachment(true);
                                mouseBounding.stateBusy();
                        }

                    }
              }
                polygons[i]->update(el,cfg->width,cfg->height);
        }
mouseBounding.update();
}




void engine::runEngine()
{
sf::Clock clock;
float lastTime = 0;
float lastfps=0;
    while (loop)
    {
        sf::Time elapsed = clock.restart();
        float currentTime = elapsed.asSeconds();
        float fps=1.f/(currentTime);
        lastTime=currentTime;
        update(kol,elapsed);
        checkEvents();
        movement();
        checkColision(kol);

        draw(fps);
        //elapsed=clock.getElapsedTime();




    }

}

