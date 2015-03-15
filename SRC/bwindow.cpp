#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "bwindow.h"

using namespace std;


bwindow::bwindow()
{
  width = MIN_WIDTH;
  height =  MIN_HEIGHT;
  strcpy(window_name,"Default Window");
  strcpy(icon_name,"Defwin");
  line_width = 1;
  border_width = 4;
  strcpy(fontname,"9x15");
}

bwindow::bwindow(int w,int h)
{
  width = w > MIN_WIDTH ? w : MIN_WIDTH;
  height = h > MIN_HEIGHT ? h : MIN_HEIGHT;
  strcpy(window_name,"Default Window");
  strcpy(icon_name,"Defwin");
  line_width = 1;
  border_width = 4;
  strcpy(fontname,"9x15");
}

bwindow::bwindow(int w,int h, const char * name)
{

  width = w > MIN_WIDTH ? w : MIN_WIDTH;
  height = h > MIN_HEIGHT ? h : MIN_HEIGHT;
  strcpy(window_name,name);
  strcpy(icon_name,name);
  line_width = 1;
  border_width = 4;
  strcpy(fontname,"9x15");
}

bwindow::bwindow(int w,int h, char * name,char * font)
{

  width = w > MIN_WIDTH ? w : MIN_WIDTH;
  height = h > MIN_HEIGHT ? h : MIN_HEIGHT;
  strcpy(window_name,name);
  strcpy(icon_name,name);
  strcpy(fontname,font);
  line_width = 1;
  border_width = 4;
}

bwindow::~bwindow()
{
  clean_up();
}
int bwindow::init()
{
  Pixmap icon_pixmap;
  if ((display=XOpenDisplay(0x0)) == NULL)
    {
      return ERR_BAD_DISPLAY;
    }
  screen = DefaultScreen(display);
  display_width = DisplayWidth(display,screen);
  display_height = DisplayHeight(display,screen);
  
  win = XCreateSimpleWindow(display, RootWindow(display,screen),
			    x, y, width, height, border_width,
			    BlackPixel(display,screen),
			    WhitePixel(display,screen));
  size_hints.flags = PPosition | PSize | PMinSize;
  size_hints.x = x;
  size_hints.y = y;
  size_hints.width = width;
  size_hints.height = height;
  size_hints.min_width = MIN_WIDTH;
  size_hints.min_height = MIN_HEIGHT;

  XSetStandardProperties(display, win, window_name, icon_name,0 ,0, icon_pixmap, &size_hints);

  XSelectInput(display, win, ExposureMask |
	       KeyPressMask |
	       ButtonPressMask |
	       StructureNotifyMask);
  if (load_font()!=0)
    return ERR_BAD_FONT;
  get_gc();
  return 0;
}
int bwindow::load_font()
{
  if ((font_info=XLoadQueryFont(display,fontname)) == NULL)
    {
      return -1;
    }
  else
    return 0;
}

int bwindow::reload_font(char * font_name)
{
  strcpy(fontname,font_name);
  return load_font();
}

void bwindow::clean_up()
{
	
  XUnloadFont(display, font_info->fid);
  XFreeGC(display, gc);
  XCloseDisplay(display);
}

void bwindow::map()
{
  XMapWindow(display,win);
}
int bwindow::get_gc()
{
  unsigned long valuemask = 0;
  XGCValues values;
  gc = XCreateGC(display, win, valuemask, &values);
  XSetFont(display, gc, font_info->fid);
  XSetForeground(display, gc, 0x0 /* BlackPixel(display,screen) */);
  XSetLineAttributes(display, gc, line_width, LineSolid, CapButt, JoinMiter);
  return 0;
}


int bwindow::parse_event()
{

  while((XPending(display) > 0))
    {
    
      XNextEvent(display, &report);
      
      switch (report.type)
	{
	case Expose:
	  return BEXPOSE;
	case ConfigureNotify:
	      
	  width = report.xconfigure.width;
	  height = report.xconfigure.height;
	  if (width < size_hints.min_width) 
	    width = size_hints.min_width;
	  if (height < size_hints.min_height)
	    height = size_hints.min_height;
	  return BCONFIGURE;
	  break;
	      
	case ButtonPress:
	  return BBPRESS;
	  break;
	case KeyPress:
	  strcpy(lastkey,XKeysymToString(XKeycodeToKeysym(display,report.xkey.keycode,0)));
	  if (!strcmp(lastkey,"Escape"))
	    exit(0);
	  return BKPRESS;
	  break;    		
	default:
	  break;
	}
    }
}

void bwindow::draw_text(int x, int y, unsigned int color,char * text, int len)
{
  XSetForeground(display, gc,color);
  XDrawString(display, win, gc, x, y, text, len);
  XSetForeground(display, gc,0x0);
}
 

void bwindow::draw_square(int x1,int y1,int x2,int y2,unsigned int color)
{
  XSetForeground(display, gc,color);
  XDrawRectangle(display, win, gc, x1, y1,x2-x1, y2-y1);
  XSetForeground(display, gc,0x0);
}

void bwindow::draw_line(int x1,int y1,int x2,int y2,unsigned int color)
{
  XSetForeground(display, gc,color);
  XDrawLine(display, win, gc, x1, y1, x2,y2);
  XSetForeground(display, gc,0x0);
}



void bwindow::draw_point(int x, int y, unsigned int color)
{
  XSetForeground(display, gc,color);
  XDrawPoint(display, win, gc, x, y);
  XSetForeground(display, gc,0x0);
}

void bwindow::draw_fsquare(int x1,int y1,int x2,int y2,unsigned int color)
{
  XSetForeground(display, gc,color);
  XFillRectangle(display, win, gc, x1, y1, x2-x1, y2-y1);
  XSetForeground(display, gc,0x0);
}

void bwindow::draw_circle(int x, int y, int r, unsigned int color)
{
  XSetForeground(display, gc,color);
  XDrawArc(display, win, gc, x, y, 2 * r, 2 * r, 0, 100);
  XSetForeground(display, gc,0x0);
}

char * bwindow::get_lastkey()
{
  return lastkey;
}

unsigned int bwindow::get_width()
{
  return width;
}

unsigned int bwindow::get_height()
{
  return height;
}

void bwindow::pixel_N_y(int nb_pixel,int position_x_ajust, int position_y_ajust, int col)
{
  for ( int i = position_y_ajust - nb_pixel/2 ; i < position_y_ajust + nb_pixel/2 ; i++)
    {
      this->draw_point(position_x_ajust, i, col);
    }
}
	
void bwindow::pixel_N_x(int nb_pixel,int position_x_ajust, int position_y_ajust, int col)
	{
		for ( int i = position_x_ajust - nb_pixel/2 ; i < position_x_ajust + nb_pixel/2 ; i++)
			{
				this->draw_point(i, position_y_ajust, col);
			}
	}
	
void bwindow::dessiner_poisson(double position_x,double position_y,double vitesse_x,double vitesse_y,int couleur)
{
  // Orientation poisson : 0 = verticale ; 1 = vitesse positive ; -1 = vitesse négative ; 2 = mange
  int orientation_poisson; 
  int col = couleur;
  float r;
  int  model[13] = {8,6,4,2,4,6,8,8,8,8,6,4,2};
  double pas_x;
  double pas_y;
  int taille = 13;
	
  // Contrôle du coefficient directeur r 
	
  if (vitesse_x !=0)
    {
      r = vitesse_y / vitesse_x;
				
      pas_x = sqrt(taille*taille/(r*r+1))/taille;
      pas_y = r*pas_x;
			
      if ( vitesse_x > 0) { orientation_poisson = 1;}
      else { orientation_poisson = -1;}
    }
	
	else if ( vitesse_x == 0 && vitesse_y == 0) { orientation_poisson = 2;}
	
  else { orientation_poisson = 0; }
		
  if (orientation_poisson == 0)
    {
      for ( int i = position_y - 6 ; i < position_y + 7 ; i++)
	{
	  this->draw_point(position_x, i, col);
	}
    }
  		
  else if (orientation_poisson == -1)
    {
      for (int i=0; i<=12; i++)
	{
	  pixel_N_y(model[i],position_x-i*pas_x,position_y-i*pas_y,col);
	}
    }
  		
  else if (orientation_poisson == 1)
    {
      for (int i=0; i<=12; i++)
	{
	  pixel_N_y(model[i],position_x+i*pas_x,position_y+i*pas_y,col);
	}
    }
	
	else 
		{
			for (int i=0; i<=12; i++)
				{
					pixel_N_x(model[i],position_x,position_y-i,col);
				}
		}
			
	
	
	
}

void bwindow::dessiner_algue(double position_x,double position_y,int couleur1, int couleur2)
	{
  		int model[12][37] = 
   {{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0},//,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0},//,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},//,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
		{2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},//,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},//,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
		{2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},//,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},//,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},//,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{2,2,2,2,2,2,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},//,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},//,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},//,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0}};//,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0}};
		
		for (int i=0; i<12; i++)
			{
				for (int j=0; j<37; j++)
					{
						if ( model[i][j]==1 )
							{
								this->draw_point(position_x-6+i, position_y+3-j, couleur1);
							}
							
						else if ( model[i][j]==2 )
							{
								this->draw_point(position_x-6+i, position_y+3-j, couleur2);
							}
			
					}
			}
	}
