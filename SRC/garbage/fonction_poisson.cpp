void pixel_N_y(int nb_pixel,int position_x_ajust, int position_y_ajust, int col)
{
  for ( int i = position_y_ajust - nb_pixel/2 ; i < position_y_ajust + nb_pixel/2 ; i++)
    {
      this->draw_point(position_x_ajust, i, col);
    }
}
	
void pixel_N_x(int nb_pixel,int position_x_ajust, int position_y_ajust, int col)
	{
		for ( int i = position_x_ajust - nb_pixel/2 ; i < position_x_ajust + nb_pixel/2 ; i++)
			{
				this->draw_point(i, position_y_ajust, col);
			}
	}
void dessiner_poisson(double position_x,double position_y,double vitesse_x,double vitesse_y,int couleur)
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
	  fenetre->draw_point(position_x, i, col);
	}
    }
  		
  else if (orientation_poisson == -1)
    {
      for (int i=0; i<=12; i++)
	{
	  pixel_N_y(model[i],position_x-i*pas_x,position_y+i*pas_y,col);
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
					pixel_N_x(model[i],position_x,position_y+i,col,fenetre);
				}
		}
			
	
	
	
}
