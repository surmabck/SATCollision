#include "obiekt.h"
int obiekt::activePolygon=0;
bool obiekt::showBBox=true;

obiekt::obiekt()
{
    attachment=false;
    polygonCollid=false;
    shape.setFillColor(sf::Color(255,255,255,255));


    vx=(sin((rand()%360)*3.14/180))*3;
    vy=(cos((rand()%360)*3.14/180))*3;
}

obiekt::~obiekt()
{

}

bool obiekt::isAttached()
{
    return attachment;
}

void obiekt::setAttachment(bool i)
{
    attachment=i;
}
void obiekt::setPosition(sf::Vector2f mouse)
{
    shape.setPosition(mouse);
}
obiekt::obiekt(int x,float r,bool iD,int xs,int ys)
    {
        attachment=false;
        polygonCollid=false;
        shape.setFillColor(sf::Color(255,255,255,255));
        vx=(sin((rand()%360)*3.14/180))*3;
        vy=(cos((rand()%360)*3.14/180))*3;
        shape.setOutlineThickness(-3);
        shape.setOutlineColor(sf::Color::Black);
        shape.setPointCount(x);
        shape.setRadius(r);
        shape.setPosition(xs,ys);
        shape.setFillColor(sf::Color(225,217,172,0));
        sf::FloatRect spriteSize = shape.getLocalBounds();
        shape.setOrigin(spriteSize.width/2,spriteSize.height/2);
        bounding_box=make_bounding_box(shape.getGlobalBounds());
        polygonCollid=false;
        isDynamic=iD;

    }

void obiekt::setColor(sf::Color cl)
    {
        shape.setFillColor(cl);
    }
void obiekt::setBBoxColor(sf::Color cl)
    {
        bounding_box.setOutlineColor(cl);
    }
void obiekt::setOutlineColor(sf::Color cl)
{
    shape.setOutlineColor(cl);
}
void obiekt::setCollid(bool i)
    {
        polygonCollid=i;
    }
bool obiekt::isCollid()
    {
        return polygonCollid;
    }
sf::CircleShape obiekt::getShape()
    {
        return shape;
    }
void obiekt::move(float pvx,float pvy)
    {
        shape.move(pvx,pvy);
    }
void obiekt::rotate()
{

    this->shape.rotate(2);
     bounding_box=make_bounding_box(shape.getGlobalBounds());
}
void obiekt::update(sf::Time el,int width,int height)
{
    if (isDynamic==true)
    {
        move(vx,vy);
    }
    sf::FloatRect bb = shape.getGlobalBounds();
    if ((bb.left!=bounding_box.getGlobalBounds().left)||(bb.top!=bounding_box.getGlobalBounds().top)){

        bounding_box.move(bb.left-bounding_box.getGlobalBounds().left,bb.top-bounding_box.getGlobalBounds().top);
    }
      if((bb.left<=0) || (bb.left+bb.width>=width))
      {
          if (bb.left<0) shape.move(-bb.left,0);
          else if (bb.left+bb.width>width) shape.move(width-(bb.left+bb.width),0);
          vx=vx*(-1);
      }
      if(bb.top<=0 || (bb.top+bb.height>=height))
      {
          if (bb.top<0) shape.move(0,-bb.top);
          else if (bb.top+bb.height>height) shape.move(0,height-(bb.top+bb.height));
        vy=vy*(-1);
      }

}
sf::FloatRect obiekt::getBoundingBox()
{
    return shape.getGlobalBounds();
}
sf::RectangleShape obiekt::make_bounding_box(sf::FloatRect rect)
{
    sf::RectangleShape bounding_box( sf::Vector2f( rect.width, rect.height ) );
    bounding_box.setFillColor( sf::Color::Transparent );
    bounding_box.setOutlineColor( sf::Color::Black );
    bounding_box.setOutlineThickness( -2 );
    bounding_box.setPosition( rect.left, rect.top );

   return bounding_box;
}
