void bwindow::dessiner_algue(double position_x,double position_y,int couleur1, int couleur2)
	{
	
		draw_point(position_x, position_y, couleur2);
		draw_point(position_x+1, position_y, couleur2);
		draw_point(position_x, position_y-1, couleur2);
		draw_point(position_x+1, position_y-1, couleur2);
		
		draw_point(position_x, position_y-2, couleur1);
		draw_point(position_x+1, position_y-2, couleur1);
		draw_point(position_x+1, position_y-3, couleur1);
		
		draw_point(position_x+2, position_y-3, couleur1);
		
		draw_point(position_x+1, position_y-4, couleur1);
		draw_point(position_x, position_y-4, couleur1);
		draw_point(position_x, position_y-5, couleur1);
		
		draw_point(position_x-1, position_y-5, couleur1);
		draw_point(position_x-1, position_y-6, couleur1);
		draw_point(position_x, position_y-6, couleur1);
		
		draw_point(position_x, position_y-7, couleur1);
		draw_point(position_x+1, position_y-7, couleur1);
		
		draw_point(position_x+1, position_y-8, couleur1);
		draw_point(position_x+2, position_y-8, couleur1);
		
		draw_point(position_x+1, position_y-9, couleur1);
		draw_point(position_x+2, position_y-9, couleur1);
		
		draw_point(position_x, position_y-10, couleur1);
		draw_point(position_x+1, position_y-10, couleur1);
		
		draw_point(position_x, position_y-11, couleur1);
		draw_point(position_x-1, position_y-11, couleur1);
		
		draw_point(position_x, position_y-12, couleur1);
		draw_point(position_x-1, position_y-12, couleur1);
		
		draw_point(position_x, position_y-13, couleur1);
		draw_point(position_x+1, position_y-13, couleur1);
	
	
	}
