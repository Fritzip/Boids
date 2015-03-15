//************************************************************************
//
// Classe permettant la gestion et l'affichage des obstacles du monde.
//
//************************************************************************

// =======================================================================
//                                   Bibliothèques
// =======================================================================

#include <cstdlib>
#include <iostream>
#include <ctime>

// =======================================================================
//                                 Fichiers Projets
// =======================================================================

#include "Caillou.h"
#include "bwindow.h"
#include "Gaia.h"
#include "Vec2d.h"

//########################################################################
//                                                                       #
//                            Classe Caillou                             #
//                                                                       #
//########################################################################

// =======================================================================
//                         Définitions des attributs statiques
// =======================================================================

// =======================================================================
//                                  Constructeurs
// =======================================================================

Caillou::Caillou( Gaia * gaia_actuel )
	{
		// Constructeur à partir d'un monde gaia donné
		
		mon_gaia = gaia_actuel;
		couleur_caillou = 0x464343;
		
		position=Vec2d((rand()/(double)RAND_MAX)*((mon_gaia->largeur_gaia)-4)+2,(rand()/(double)RAND_MAX)*((mon_gaia->hauteur_gaia)-4)+2);
	}

Caillou::Caillou(Gaia* gaia_actuel, Caillou* caillou_precedent)
	{
		// Constructeur à partir d'un monde gaia donné et du caillou précédemment généré => formation de récifs
		
		mon_gaia=gaia_actuel;
		couleur_caillou= 0x464343;
		
		position=caillou_precedent->position+Vec2d((rand()/(double)RAND_MAX) - 0.7,(rand()/(double)RAND_MAX) - 0.7);
	}

// =======================================================================
//                                  Destructeurs
// =======================================================================

Caillou::~Caillou( void )
	{
	}

// =======================================================================
//                                 Methodes Publiques
// =======================================================================

void Caillou::afficher( void )
	{
		// Méthode qui permet d'afficher un caillou dans la fenêtre avec les couleurs déclarées dans la fonction
		
		int couleur1 = 0x33CC00;
		int couleur2 = 0x009900;
	
		double position_x = (position.get_x()*mon_gaia->get_largeur_fenetre())/mon_gaia->largeur_gaia;
		double position_y = (position.get_y()*mon_gaia->get_hauteur_fenetre())/mon_gaia->hauteur_gaia;
		mon_gaia->get_fenetre()->dessiner_algue(position_x,position_y,couleur1,couleur2);
	}

// =======================================================================
//                                Methodes Protégées
// =======================================================================

// =======================================================================
//                               Accesseurs non-inline
// =======================================================================
