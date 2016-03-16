#include "config.h"
config::config(const char *s)
{
        fontsize = 25;
        menuHeight = 50;
        menuWidth = 150;
    std::fstream plik;
    std::string data;
    plik.open( s, std::ios::in );
    if( plik.good() == true )
    {
        std::cout << "Uzyskano dostep do pliku!" << std::endl;
            while (!plik.eof())
            {
                getline(plik,data);
                int tmp=parse(data);
                input(tmp,data);
            }
    }
    else
    {
     plik.close();
     plik.open( s, std::ios::out );
     plik<<"screenWidth:800"<<std::endl;
     plik<<"screenHeight:600"<<std::endl;
     plik.close();
    }


        height=screenHeight-menuHeight;
        width=screenWidth-menuWidth;
}
void config::input(int value,std::string str)
 {
    if (str=="screenWidth") screenWidth=value;
    else if (str=="screenHeight") screenHeight=value;
    else if (str=="menuWidth") menuWidth=value;
    else if (str=="menuHeight") menuHeight=value;
 }
int config::strToInt(std::string s)
{
     int tmp = 0, i = 0;
     bool m = false;
     if(s[0] == '-') {
      m = true;
      i++;
     }
     for(; i < s.size(); i++)
      tmp = 10 * tmp + s[i] - 48;
     return m ? -tmp : tmp;
}
int config::parse(std::string &s)
{
    std::string tmp=s.substr(s.find(':')+1);
    s=s.substr(0,s.find(':'));
    return strToInt(tmp);
}
