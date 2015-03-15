//***********************************************************************
//
// Classe principale qui gère l'ensemble de la simulation
//
//***********************************************************************

// ======================================================================
//                                   Bibliothèques
// ======================================================================

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include <time.h>
#include <cstring>
#include "bwindow.h"

// ======================================================================
//                                 Fichiers Projets
// ======================================================================

#include "Gaia.h"
#include "Population.h"
#include "Caillou.h"

//#######################################################################
//                                                                      #
//                                 Classe Gaia                          #
//                                                                      #
//#######################################################################

// ======================================================================
//                         Définitions des attributs statiques
// ======================================================================

// ======================================================================
//                                  Constructeurs
// ======================================================================

Gaia::Gaia( void )
	{
		// Constructeur par défaut
		
		charger("pop_defaut");
	 
		fenetre=new bwindow(largeur_fenetre,hauteur_fenetre,"Des poissons volants !");
		
		joueur=populations[0]->get_agent(0);
	}
	
Gaia::Gaia(char save_or_load, string nom_fic)
	{
		// Constructeur à partir d'un fichier
	
		if(save_or_load==0) // save_or_load=0 : On charge mais on n'enregistre pas
		  {
		    charger(nom_fic + "_parametre"); 
		    charger_position(nom_fic + "_position");
		    
		    fenetre=new bwindow(largeur_fenetre,hauteur_fenetre,"Des poissons volants !");
		    joueur=populations[0]->get_agent(0);
		  }
		  
		else // save_or_load=1 : On lance une partie par défaut avec la possibilité d'enregistrer
		 {
				charger("pop_defaut");
				 
				fenetre=new bwindow(largeur_fenetre,hauteur_fenetre,"Des poissons volants !");
				
				joueur=populations[0]->get_agent(0);
			
				fic_save=nom_fic;
			}	
	}

Gaia::Gaia(string nom_save,string nom_load)
	{
		// Constructeur à partir d'un fichier avec la possiblité de sauvegarder la partie dans un autre
		
		charger(nom_load+"_parametre"); 
		charger_position(nom_load+"_position");
		
		fenetre=new bwindow(largeur_fenetre,hauteur_fenetre,"Des poissons volants !");
		
		joueur=populations[0]->get_agent(0);
		
		fic_save=nom_save;
	}

// ======================================================================
//                                  Destructeurs
// ======================================================================

Gaia::~Gaia( void )
	{ 
		// Destructeur (en chaine)
		
		size_t i;
		
		for(i=0;i<populations.size();i++)
		  {    
		    delete populations[i];
		  }
	}

// ======================================================================
//                                 Methodes Publiques
// ======================================================================

void Gaia::generer_cailloux(int nombre_cailloux, int nombre_recifs) 
	{
		// Méthode qui permet de générer des cailloux et de constituer les récifs
		
		for (int j = 0; j < nombre_recifs; ++j)
		  {
		    cailloux.push_back( new Caillou(this));
		  }  

		int a = nombre_recifs + 1;
		
		for (int i=nombre_recifs; i<nombre_cailloux; i++)
		  {
		    if (a <= 0)
					{
						a = nombre_recifs+1;
					}
		    a--;
		    
		    cailloux.push_back( new Caillou(this,cailloux[nombre_recifs-a]) );
		  }
	}
	
void Gaia::commencer(void)
	{
		// Méthode qui gère le déroulement de la simulation (affiche la fenêtre et lance l'animation)
		
		int colfd=0xCCCCFF; // Couleur du fond
		
		if (fenetre->init() == 0)
		  {
		    fenetre->map();
		    
		    generer_cailloux(nb_cailloux,nb_recifs);
		    
		    dt=0.007;
		    
		    Vec2d bkPress;
		    
		    double vitesse_joueur=5;
		    
		    for (int f=1;;f++)
					{
						usleep(dt*1020000);
						
						//vitesses_moyennes(f); // Zone à décommenter pour obtenir les différents graphiques
						//nb_grp(f);
						//nb_mangeant(f);
						
						calculer();
						
						fenetre->draw_fsquare(0,0,largeur_fenetre,hauteur_fenetre,colfd); 
						// On réafiche une carré de la couleur de fond choisit à chaque tour
						
						afficher(); // Permet d'afficher les agents et les obstacles
					

						if(fenetre->parse_event() == BKPRESS) // Pour gérer la saisie clavier
							{
								char* dir=fenetre->get_lastkey();
							
								switch(*dir)
									{
										case 'z':bkPress=Vec2d(0,-vitesse_joueur);
											break;
										case 's':bkPress=Vec2d(0,vitesse_joueur);
											break;
										case 'q':bkPress=Vec2d(-vitesse_joueur,0);
											break;
										case 'd':bkPress=Vec2d(vitesse_joueur,0);
											break;
										case 'm':enregistrer(fic_save);
											break;			
										default:bkPress=Vec2d(0,0);
											break;
									}
								joueur->set_vitesse(joueur->get_vitesse()+bkPress);
							}
					} 
		  }
	} 

void Gaia::calculer(void)
	{
		// Méthode qui permet de calculer le déplacement des agents des populations du monde (en chaine)
		
		int i;
		
		for(i=0;i<nb_populations;i++)
		  {
		    populations[i]->deplacer();
		  } 
	}
	
void Gaia::afficher(void)
	{
		// Méthode qui permet d'afficher les différents agents (en chaine)
		
		int i;
		
		for(i=0;i<nb_populations;i++)
		  {
		    populations[i]->afficher();
		  }
		for (i=0; i<cailloux.size(); i++)
		  {
		    cailloux[i]->afficher();	// Permet d'afficher les obstacles
		  }
	}

void Gaia::enregistrer(string nomfic)
	{
		// Méthode qui permet d'enregistrer les différents paramètres nécessaires à l'exécution d'une partie
		
		string fichier_parametre = nomfic + "_parametre"; // On sauvegarde les paramètres et les positions des agents
		string fichier_position = nomfic + "_position"; // dans deux fichiers différents
		
		ofstream fichier_param(fichier_parametre.c_str(),ios::out | ios::trunc);
		ofstream fichier_posi(fichier_position.c_str(),ios::out | ios::trunc);
		
		if(fichier_param)
			{
				if(fichier_posi)
				{
					ifstream fichier_defaut("pop_defaut",ios::in);
					
					if(fichier_defaut)
						{
							string ligne;
							
							while(getline(fichier_defaut,ligne))
								{
									fichier_param << ligne << endl;
				  			}
					
							fichier_defaut.close();
							fichier_param.close();
					
							for(int i=0;i<nb_populations;i++)
								{
									fichier_posi<<populations[i]->get_taille()<<" "<<populations[i]->get_couleur()<<endl;
									fichier_posi<<populations[i]->get_nombre_agents()<<endl;

									for(int j=0;j<populations[i]->get_nombre_agents();j++)
										{
											Agent* agentTemp=populations[i]->get_agent(j);
											fichier_posi<<agentTemp->get_position().get_x()<<" "<<agentTemp->get_position().get_y()<<" "<<agentTemp->get_vitesse().get_x()<<" "<<agentTemp->get_vitesse().get_y()<<endl;
										} 
								}
						}
				}
			}
		
		fichier_posi.close();
	}

void Gaia::charger_position(string nomfic)
	{
		// Méthode qui permet de lire les positions des agents relatives à une simulation donnée dans un fichier
		
		ifstream fichier(nomfic.c_str(),ios::in);
		
		if(fichier)
			{
				int _taille;
				int _couleur; 
				int _nbAgents;
				
				Population* popTemp;
				Agent* agentTemp;
				
				double _pos_x,_pos_y,_vit_x,_vit_y;
				
				for(int i=0; i < nb_populations; i++)
				  {
						fichier >> _taille >> _couleur >> _nbAgents;
						populations.push_back(new Population(this,_nbAgents,_taille,_couleur));
						popTemp=populations[i];
					
						for(int j=0;j<_nbAgents;j++)
							{
								agentTemp=popTemp->get_agent(j);
								fichier >> _pos_x >> _pos_y >> _vit_x >> _vit_y;
								agentTemp->set_position(Vec2d(_pos_x,_pos_y));
								agentTemp->set_vitesse(Vec2d(_vit_x,_vit_y));
							}
		    	}
			}

		fichier.close();
	}

void Gaia::charger(string nomfic)
	{
		// Méthode qui permet de charger les paramètres d'un fichier passé en paramètre
		
		ifstream fichier(nomfic.c_str(),ios::in);
		
		string etiquette;
		string commentaire;
		
		int _nb_agents;
		int _couleur;
		int _nombre_regles;

		int _coeff;
		
		int mange;
		int est_mange;
		
		if(fichier)
		  {
		    string ligne;
			
				fichier >> etiquette >> _coeff;
				largeur_fenetre = largeur_gaia * _coeff;
			
				fichier >> etiquette >> _coeff;
				hauteur_fenetre = hauteur_gaia * _coeff;
			
				fichier >> etiquette >> dt;

		    fichier >> etiquette >> nb_populations;
		    
		    for(int i=0; i < nb_populations; i++)
		    	{
						fichier >> etiquette >> _nb_agents >>_couleur;
		    
						populations.push_back(new Population(this,_nb_agents,13,_couleur));
					 }
					 
				fichier >> etiquette >> nb_cailloux;
				fichier >> etiquette >> nb_recifs; 
		    
		    fichier >> etiquette >> _nombre_regles;
		    
		    for(int i=0; i<_nombre_regles; i++)
		    	{
						fichier >> etiquette >> mange >> est_mange;
					
						if(mange<nb_populations && est_mange<nb_populations)
							{	 
								populations[mange]->ajouter_proies(populations[est_mange]); 
							}
					}
			
				for (int i=0; i<7; i++)
					{
					  fichier >> etiquette >> gamma[i] >> commentaire;
					}
			}

		fichier.close();
	}

void Gaia::vitesses_moyennes(int f)
	{
		// Méthode permettant de sauvegarder les vitesses moyennes des populations à un moment donné (en chaine)
	 
		ofstream fichier("vitesses.moyennes",ios::out | ios::app);
		
		fichier<<f<<" ";
		
		for(int i=0;i<nb_populations;i++)
		  {
		    fichier<<populations[i]->calculer_vitesse_moyenne()<<" ";
		  }
		  
		fichier<<endl;
		fichier.close();
	}

void Gaia::nb_grp(int f)
	{
		// Méthode permettant de sauvegarder le nombre de groupe par populations à un moment donné (en chaine)
		
		ofstream fichier("nombre.groupes",ios::out | ios::app);
		fichier<<f<<" ";
		for(int i=0;i<nb_populations;i++)
		  {
		    fichier<<populations[i]->calculer_nombre_groupes()<<" ";
		  }
		fichier<<endl;
		fichier.close();
	}
	
void Gaia::nb_mangeant(int f)
	{
		// Méthode permettant de sauvegarder le nombre d'agent mangeant par populations à un moment donné (en chai	ne)
		
		ofstream fichier("nombre.mangeant",ios::out | ios::app);
		fichier<<f<<" ";
		for(int i=0;i<nb_populations;i++)
		  {
		    fichier<<populations[i]->nombre_mangeant()<<" ";
		  }
		fichier<<endl;
		fichier.close();
	}
// ======================================================================
//                                Methodes Protégées
// ======================================================================

// ======================================================================
//                               Accesseurs non-inline
// ======================================================================
