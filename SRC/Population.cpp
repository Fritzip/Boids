//***********************************************************************
//
// Classe permettant la gestion des populations présentent dans le monde.
//
//***********************************************************************

// ======================================================================
//                                   Bibliothèques
// ======================================================================
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <math.h>

using namespace std;

// ======================================================================
//                                 Fichiers Projets
// ======================================================================

#include "Gaia.h"
#include "Population.h"
#include "Agent.h"

//#######################################################################
//                                                                       
//                                 Classe Population                     
//                                                                       
//#######################################################################

// ======================================================================
//                         Définitions des attributs statiques
// ======================================================================

// ======================================================================
//                                  Constructeurs
// ======================================================================

Population::Population(Gaia* ga)
	{
		// Constructeur à partir d'un monde gaia donné
	
		mon_gaia=ga;
		int i;
		
		for(i=0;i<10;i++)
		  {
		    agents.push_back(new Agent(mon_gaia,this));
		  } 

		taille=(rand()/(double)RAND_MAX)*6+2;
		couleur=(rand()/(double)RAND_MAX)*0xFFFFFF;
		rayon_perception = 1.5*1.5; // au carré pour calculer plus facilement les distances
		rayon_contact=0.45*0.45;
	}


Population::Population( Gaia* ga,  int nombre_agent, int _taille, int _couleur)
	{
		// Constructeur à partir d'un monde gaia donné et d'un nombre d'agent d'une couleur donnée (permet le chargement de partie)
	
		mon_gaia=ga;
		
		for (int i = 0; i < nombre_agent; ++i)
		  {
		    agents.push_back(new  Agent(mon_gaia,this));
		  }
		  
		rayon_perception = 1.5*1.5;
		rayon_contact = 0.45*0.45;
	 
		couleur = _couleur;
		taille  = _taille;
	}

// ======================================================================
//                                  Destructeurs
// ======================================================================

Population::~Population( void )
	{ 
		// Destructeur
	
		int i;
		
		for(i=0;i<agents.size();i++)
		  {
		    delete agents[i];
		  }
	}

// ======================================================================
//                                 Méthodes Publiques
// ======================================================================

void Population::deplacer(void)
	{
		// Méthode permettant de calculer le déplacement et la vitesse des agents d'une population
	
		int i;
		
		for(i=0;i<agents.size();i++)
		  {
		    // Mouvement
		    agents[i]->set_position(agents[i]->get_position()+(agents[i]->get_vitesse())*(mon_gaia->get_dt()));
		
		    //Vitesse
		    agents[i]->calculer_vitesse();
		  }
	}

void Population::afficher(void)
	{
		// Méthode permettant d'afficher les agents de la population
	
		int i;
		
		for(i=0;i<agents.size();i++)
		  {
		    //Affichage
		    agents[i]->afficher();
		  }
	}

double Population::calculer_vitesse_moyenne(void)
	{
		// Méthode permetant de calculer la vitesse moyenne des agents d'une population à un moment donné
		
		int i;
		double moy=0;
		for(i=0;i<agents.size();i++)
		  {
		    moy+=sqrt(agents[i]->get_position().distance_carre(Vec2d(0,0)));
		  }
		moy=moy/agents.size();
		return moy;
	}

int Population::calculer_nombre_groupes(void)
	{
		// Méthode permetant de calculer le nombre de groupe par population à un moment donné
	
		vector<Agent*> groupe;
		vector<Agent*> deja_vus;
		
		int nombre_groupes=0;
		int k;
		
		for(int j=0;j<agents.size();j++)
		  {
		    if(agents[j]->est_dans_vector(deja_vus)==0)
		    	{
						nombre_groupes++;
						groupe.push_back(agents[j]);
						k=0;
						
						while(k<groupe.size())
							{
								// Détermination des agents voisins
								
								for (int i=0; i < agents.size(); i++)
									{
					  				double distanceAgentI=(agents[i]->get_position()).distance_carre(groupe[k]->get_position());
					  
										// Agents dans le rayon de perception (voisins)	
										      
										if ( distanceAgentI < rayon_perception && agents[i]->est_dans_vector(groupe)==0)
											{ 
												groupe.push_back(agents[i]);
												deja_vus.push_back(agents[i]);
											}
									}
								k++;
							}
		    	}
		   
				groupe.clear();
		    
		  }
		 
		return nombre_groupes;
	}

int Population::nombre_mangeant(void)
	{
		// Méthode permetant de calculer le nombre d'agents mangeant à un moment donné
		
		int nombre_mangeant=0;
		
		for(int i=0;i<agents.size();i++)
		  {
		    if(agents[i]->get_ne_mange_pas()==0)
					{
						nombre_mangeant+=1;
					}
		  }
		
		return nombre_mangeant;
	}

// ======================================================================
//                                Méthodes Protégées
// ======================================================================

// ======================================================================
//                               Accesseurs non-inline
// ======================================================================

void Population::ajouter_proies(Population * nouvelles_proies)
	{
	
		// Méthode permettant d'ajouter une population proie à une population donnée
		
		proies.push_back(nouvelles_proies);
		nouvelles_proies->predateurs.push_back(this);
	}

