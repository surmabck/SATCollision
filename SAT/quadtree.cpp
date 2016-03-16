#include "quadtree.h"
  quadtree::quadtree(int pLevel, sf::FloatRect _quad)
{
   level = pLevel;
   qquad.width=_quad.width;
    qquad.height=_quad.height;
     qquad.top=_quad.top;
      qquad.left=_quad.left;
   nodes[0]=NULL;
   nodes[1]=NULL;
   nodes[2]=NULL;
   nodes[3]=NULL;
   parent=NULL;
}
quadtree::~quadtree()
{
    clear();
}
/*
@
@czyszczenie calego drzewa
@
*/
void quadtree::clear() {
  objects.clear();

    for (int i = 0; i < 4; i++) {
    if (nodes[i] != NULL) {
        delete nodes[i];
       nodes[i]=NULL;

     }
   }
 }
/*
@
@dzielimy wezel na 4 podwezly
@
*/
void quadtree::split() {
   int subWidth = (int)(qquad.width/ 2);
   int subHeight = (int)(qquad.height / 2);
   int x = (int)qquad.left;
   int y = (int)qquad.top;

   nodes[0] = new quadtree(level+1,sf::FloatRect(x + subWidth, y, subWidth, subHeight));
   nodes[1] = new quadtree(level+1,sf::FloatRect(x, y, subWidth, subHeight));
   nodes[2] = new quadtree(level+1,sf::FloatRect(x, y + subHeight, subWidth, subHeight));
   nodes[3] = new quadtree(level+1,sf::FloatRect(x + subWidth, y + subHeight, subWidth, subHeight));
   for (int i=0;i<4;i++)
    nodes[i]->parent=this;
 }
/*
@update ma w przyszlosci rebuildowac drzewo, jesli jakis obiekt wyszedl poza quadre w ktorej sie znajdowal
@to nalezy go usunac z niej i wlozyc do odpowiedniej
@reszty nie tykamy
*/

/*
@ zwraca wektor z wartosciami, gdzie nalezy wstawic obiekt
@ 0,1,2,3 zaczynajac od prawego gornego roku, w przeciwnym do zegarka kierunku
@
*/
std::vector<int> quadtree::getIndex(sf::FloatRect pRect) {

double verticalMidpoint = qquad.left+ (qquad.width / 2);
double horizontalMidpoint = qquad.top+ (qquad.height / 2);
std::vector<int> indexes;
bool topQuadrant = (pRect.top < horizontalMidpoint && pRect.top + pRect.height < horizontalMidpoint);
bool bottomQuadrant = (pRect.top > horizontalMidpoint);
bool topAndBottomQuadrant = pRect.top <= horizontalMidpoint && pRect.top +pRect.height >= horizontalMidpoint;

		if(topAndBottomQuadrant)
		{
			topQuadrant = false;
			bottomQuadrant = false;
		}

		//sprawdzamy czy obiekt jest na lewo lub prawo
		if(pRect.left + pRect.width >= verticalMidpoint && pRect.left <= verticalMidpoint)
		{
			if(topQuadrant)
			{
				indexes.push_back(0);
				indexes.push_back(1);
			}
			else if(bottomQuadrant)
			{
				indexes.push_back(2);
				indexes.push_back(3);
			}
			else if(topAndBottomQuadrant)
			{
				indexes.push_back(0);
				indexes.push_back(1);
				indexes.push_back(2);
				indexes.push_back(3);
			}
		}

		// czy jest tylko na prawo
		else if(pRect.left > verticalMidpoint)
		{
			if(topQuadrant)
			{
				indexes.push_back(0);
			}
			else if(bottomQuadrant)
			{
				indexes.push_back(3);
			}
			else if(topAndBottomQuadrant)
			{
				indexes.push_back(3);
				indexes.push_back(0);
			}
		}
		// czy jest tylko na lewo
		else if(pRect.left < verticalMidpoint && pRect.left + pRect.width < verticalMidpoint)
		{
			if(topQuadrant)
			{
				indexes.push_back(1);
			}
			else if(bottomQuadrant)
			{
				indexes.push_back(2);
			}
			else if(topAndBottomQuadrant)
			{
				indexes.push_back(2);
				indexes.push_back(1);
			}
		}
		return indexes;


 }

/*
@
@wstawiamy obiekt we wlasciwe miejsce
@
*/
void quadtree::insert(obiekt *&pObiekt) {
sf::FloatRect pRect=pObiekt->getBoundingBox();
   if (nodes[0] != NULL)
    {
        std::vector<int> index = getIndex(pRect);
        for (int i=0;i<index.size();i++)
        {
        nodes[index[i]]->insert(pObiekt);
        return;
        }

   }
  objects.push_back(pObiekt);
   if (objects.size() > MAX_ELEMENTS && level < MAX_NODES)
    {
          if (nodes[0] == NULL)
          {
             split();
          }

         int i = 0;
         while (i < objects.size())
         {
               std::vector<int> index = getIndex(objects[i]->getBoundingBox());
                for (int j=0;j<index.size();j++)
                {
                    nodes[index[j]]->insert(objects[i]);
                }
               objects.erase(objects.begin()+i);
         }
   }

 }



std::vector<obiekt*> quadtree::retrieve(std::vector <obiekt*> &returnObjects, sf::FloatRect pRect) {


		std::vector<int> indexes = getIndex(pRect);
        if(nodes[0] != NULL)
        {
            for(int ii = 0; ii < indexes.size(); ii++)
            {
                int index = indexes[ii];
                nodes[index]->retrieve(returnObjects, pRect);
            }
        }
        returnObjects.insert(returnObjects.begin(),objects.begin(),objects.end());
		return returnObjects;
}

std::vector <sf::FloatRect> quadtree::bounds(std::vector <sf::FloatRect> &b)
 {
     b.push_back(qquad);
        for (int i=0; i<4; i++)
        {
            if (nodes[i]!=NULL) nodes[i]->bounds(b);
        }
 return b;
 }

