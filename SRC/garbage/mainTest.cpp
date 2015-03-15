#include <iostream>
#include <cstdlib>
#include <ctime>


#include "bwindow.h"

using namespace std;


int main(int argc, char **argv)
{
  static const int width  = 500;
  static const int height = 500;

  static const int size = 10;
  static const unsigned int colorBg = 0xFFFFFF;
  static const unsigned int color = 0xFFAA00;

  bwindow *win = new bwindow(width, height, "Nom de fenetre");

  srand(time(NULL));
  
  int x = 0;
  int y = 0;
  if (win->init() == 0)
    {
      win->map();


      
      // Affichage
      for (;;)
	{
	  //Afficher des point qui recouvre l'écran
      x=(int)((rand()/(RAND_MAX+1.0))*500);
      y=(int)((rand()/(RAND_MAX+1.0))*500);
      win->draw_text(x, y, color, "poulet",6);
      

      // win->draw_fsquare(x,y,x+5,y+5,color);


	  // x = ++x % width;
	  // y = ++y % height;

	  usleep(1000);

	  // win->draw_fsquare(0, 0, 2*width, 2*height, colorBg);
	  // win->draw_fsquare(x, y, x + size, y + size, color);



	  if(win->parse_event() == BKPRESS)
	    {
	      std::cout << win->get_lastkey() << std::endl;
	    }
	}
    }

}

