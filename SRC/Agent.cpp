//***********************************************************************
//
// Classe permettant la gestion des agents des populations présentent dans le monde.
//
//***********************************************************************
 
// ======================================================================
//                                   Bibliothèques
// ======================================================================
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>
// ======================================================================
//                                 Fichiers Projets
// ======================================================================
#include "Agent.h"
#include "Population.h"
#include "Gaia.h"
#include "Vec2d.h"

using namespace std;

//#######################################################################
//                                                                      #
//                                 Classe Agent                         #
//                                                                      #
//#######################################################################

// ======================================================================
//                         Définitions des attributs statiques
// ======================================================================

// ======================================================================
//                                  Constructeurs
// ======================================================================
 
Agent::Agent(Gaia* ga,Population* const pop)
	{
		// Constructeur par défaut, affectant des valeurs aléatoires à la position et la vitesse de l'agent
	
		ne_mange_pas = 1;
		compteur_mange = 0;
		mon_gaia=ga;
		ma_population=pop;
		position=Vec2d( (rand()/(double)RAND_MAX)*mon_gaia->largeur_gaia, (rand()/(double)RAND_MAX)*mon_gaia->hauteur_gaia);
		vitesse=Vec2d( (rand()/(double)RAND_MAX)*5+1, (rand()/(double)RAND_MAX)*5+1);

	}

// ======================================================================
//                                  Destructeurs
// ======================================================================

Agent::~Agent( void )
	{
	}

// ======================================================================
//                                 Méthodes Publiques
// ======================================================================

void Agent::afficher(void)
	{
		// Permet d'afficher l'agent dans la fenêtre
		
		int x=mon_gaia->get_largeur_fenetre()*position.get_x()/mon_gaia->largeur_gaia;
		int y=mon_gaia->get_hauteur_fenetre()*position.get_y()/mon_gaia->hauteur_gaia;
		
		mon_gaia->get_fenetre()->dessiner_poisson(x,y,vitesse.get_x(),vitesse.get_y(),ma_population->get_couleur());
	}

void Agent::calculer_vitesse(void)
	{
		// Méthode permettant de déterminer les voisins de l'agent en cours, de lui appliquer les règles et d'en déduire sa vitesse
			
		vector<Agent*> voisins; 
		vector<Agent*> agents_proches;
		vector<Caillou*> cailloux_proches;
		vector<Agent*> predateurs_proches;
		Vec2d position_proie_proche;

		for (int i=0; i < ma_population->get_nombre_agents(); i++)
		  {
		  	
		    double distanceAgentI=(ma_population->get_agent(i)->get_position()).distance_carre(position); 

		    /***AGENTS***/
		    							
		    // Agents dans le rayon de perception (voisins)
					
				
		    if ( distanceAgentI < ma_population->get_rayon_perception() && ma_population->get_agent(i)->ne_mange_pas==1) 
					{
						// Si l'agent dans le rayon de perception n'est pas en train de manger
						voisins.push_back(ma_population->get_agent(i));
					}


		    // Agents dans le rayon de contact (agents_proches)
							
		    if ( distanceAgentI < ma_population->get_rayon_contact() && ma_population->get_agent(i)->ne_mange_pas==1)
					{
						// Si l'agent dans le rayon de contact n'est pas en train de manger
						agents_proches.push_back(ma_population->get_agent(i));
					}			
		  }

		    /***CAILLOUX***/
			
		    // Cailloux dans le rayon proche
		for(int i=0;i<mon_gaia->get_nb_cailloux();i++)
		  {
		    if( (mon_gaia->get_caillou(i)->get_position()).distance_carre(position) < ma_population->get_rayon_contact())
					{
						cailloux_proches.push_back(mon_gaia->get_caillou(i));
					}
		  }

				/***PROIES***/
		
		double distance_min=ma_population->get_rayon_perception();      
		double dist;//distance de l'agent à sa proie
		int numero_population;
		int numero_proie;
		
		
		for (int k=0; k < ma_population->get_nombre_population_proies(); k++) // Nombre de populations de proies
		  {
		    for (int l=0; l < ma_population->get_nombre_agent_population_proies(k); l++) // Nombre d'agent par population de proies
					{
			
						// Boucle sur agent k de la population l
		
						dist=(ma_population->get_proie_agent(k,l)->position).distance_carre(position);
						 
						if ( dist < ma_population->get_rayon_perception() && dist<=distance_min && ma_population->get_proie_agent(k,l)->ne_mange_pas==1)
							{
								distance_min=dist;
								position_proie_proche=ma_population->get_proie_agent(k,l)->position;

								numero_population = k;
								numero_proie = l;
							}
					}
		  }

		if(distance_min < 0.035)
		  {
		    compteur_mange = 45;
		    ne_mange_pas = 0;
		    int i = rand()%mon_gaia->get_nb_cailloux(); // un chiffre correspondant à un caillou au hasard
		    
		    ma_population->get_proie_agent(numero_population,numero_proie)->set_vitesse(Vec2d(0,0)); 

		    Vec2d resurection = Vec2d(((mon_gaia->get_caillou(i)->get_position().get_x())),((mon_gaia->get_caillou(i)->get_position().get_y())-0.5)); // l'agent mangé repart d'un recif avec une vitesse nulle
		    
		    ma_population->get_proie_agent(numero_population,numero_proie)->set_position(resurection);	    
		  }

		if(compteur_mange != 0)
		  {
		    compteur_mange--;
		  }
		if(compteur_mange == 0)
		  {
		    ne_mange_pas = 1;
		  }

		    /***PREDATEURS***/
		    	
		for (int k=0; k < ma_population->get_nombre_population_predateurs(); k++) // Nombre de populations de prédateurs
		  {
		    for (int l=0; l < ma_population->get_nombre_agent_population_predateurs(k); l++) // Nombre d'agent par population de prédateurs
					{
			
						// Bouble sur agent k de la population l
			
						if ( (ma_population->get_predateur_agent(k,l)->position).distance_carre(position) < ma_population->get_rayon_perception() && ma_population->get_predateur_agent(k,l)->ne_mange_pas==1)
							{
								predateurs_proches.push_back(ma_population->get_predateur_agent(k,l));
							}
					}	
		  }

		Vec2d a[7];
		  
		//Définition des paramètres des Règles
		
		int K = voisins.size()-1; //On enlève 1 car chaque agent est dans son cercle de perception 
		int Kprime = agents_proches.size()-1;
		int O = cailloux_proches.size();
		int Kpred=predateurs_proches.size(); //nombre de predateurs en vue

		//Règle 1
		
		Vec2d sommeK0;
		
		for (int i = 0; i < K; ++i)
		  {
		    sommeK0 += (voisins[i]->vitesse-vitesse);
		  }
		  
		if(K!=0)
		  {
		    a[0] = sommeK0/K;
		  }
		

		//Règle 2
		
		Vec2d sommeK1;
		
		for (int i = 0; i < K; ++i)
		  {
		    sommeK1 += (voisins[i]->position-position);
		  }
		  
		if(K!=0)
		  {
		    a[1] = sommeK1/K;
		  }
		
		//Règle 3
		
		Vec2d sommeKprime;
		Vec2d sommeO;
		
		for (int i = 0; i < Kprime; ++i)
		  {
		    sommeKprime += (position-agents_proches[i]->position);
		  }

		//Règle 3'
		
		for (int i = 0; i < O; ++i)
		  {
		    sommeO += (position-cailloux_proches[i]->get_position());
		  }
		
		if(Kprime!=0)
		  { 
		    a[2] = (sommeKprime/Kprime);
		  }
		  
		if(O!=0)
		  {
		    a[3] = (sommeO/O);
		  }

		 //Règle 4 - Peur des bords

		Vec2d a41, a42, a43, a44;
		
		if( position.get_x()>(mon_gaia->largeur_gaia)*0.65)
		  {
		    a41 = Vec2d(-1/(mon_gaia->largeur_gaia-position.get_x()),0);
		  }

		if (position.get_x()<(mon_gaia->largeur_gaia)*0.35)
		  {
		    a42 = Vec2d(1/(position.get_x()),0);
		  }

		if (position.get_y()>(mon_gaia->hauteur_gaia)*0.65 )
		  {
		    a43 = Vec2d(0,-1/(mon_gaia->hauteur_gaia-position.get_y()));
		  }

		if (position.get_y()<(mon_gaia->hauteur_gaia)*0.35)
		  {
		    a44 = Vec2d(0,1/(position.get_y()));
		  }
		  
		a[4] = a41+a42+a43+a44;
		
		//Règle 5 
		
		Vec2d sommePred;
		
		//attaque
		
		if(position_proie_proche.get_x()>0)  //Si jamais une proie a été trouvée dans le rayon de perception
		  {
		    a[5]=((position_proie_proche)-position)/sqrt((position_proie_proche).distance_carre(position));
		  }

		//fuite
		
		for (int i = 0; i < Kpred; ++i)
		  {
		    sommePred += (position-predateurs_proches[i]->position);
		  }
		if(Kpred!=0)
		  {
		    a[6]=sommePred/Kpred/sqrt(sommePred.distance_carre(Vec2d(0,0)));
		  }
		
		
		//si l'agent est en dehors de la fenêtre
		
		if( position.get_x()>mon_gaia->largeur_gaia)
		  {
		    position.set_x(mon_gaia->largeur_gaia );
		    vitesse.set_x(-vitesse.get_x());
		  }

		if( position.get_x()<0)
		  {
		    position.set_x(0);
		    vitesse.set_x(-vitesse.get_x());
		  }

		if( position.get_y()>mon_gaia->hauteur_gaia )
		  {
		    position.set_y(mon_gaia->hauteur_gaia);
		    vitesse.set_y(-vitesse.get_y());
		  }

		if( position.get_y()<0)
		  {
		    position.set_y(0);
		    vitesse.set_y(-vitesse.get_y());
		  }
		
		//si l'agent va trop vite
		 
		if( vitesse.get_x()>(mon_gaia->hauteur_gaia)*0.5)
		  {
		    vitesse.set_x((mon_gaia->hauteur_gaia)*0.5); 
		  }

		if( vitesse.get_y()>(mon_gaia->hauteur_gaia)*0.5)
		  { 
		    vitesse.set_y((mon_gaia->hauteur_gaia)*0.5);
		  }

		if( vitesse.get_x()<(mon_gaia->hauteur_gaia)*(-0.5))
		  {
		    vitesse.set_x((mon_gaia->hauteur_gaia)*(-0.5));
		  }

		if( vitesse.get_y()<(mon_gaia->hauteur_gaia)*(-0.5))
		  {
		    vitesse.set_y((mon_gaia->hauteur_gaia)*(-0.5));
		  }

		for (int i = 0; i<7; i++)
		  {
		    this->vitesse += a[i]*mon_gaia->get_dt()*mon_gaia->get_gamma(i);
		  }
		this->vitesse = this->vitesse*ne_mange_pas;
	}

char Agent::est_dans_vector(vector<Agent*> vec)
	{
		// Méthode utile au calcule du nombre de sous groupe par population
	
		char ret=0;
		for(int i=0;i<vec.size();i++)
		  {
		    if(this==vec[i]){
		ret=1;
		    }
		  }
		return ret;
	}

// ======================================================================
//                                Méthodes Protégées
// ======================================================================

// ======================================================================
//                               Accesseurs non-inline
// ======================================================================
