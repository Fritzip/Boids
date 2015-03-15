//***********************************************************************
//
//
//
//***********************************************************************



#ifndef __POPULATION_H__ //évite la double inclusion "if not define" au second passage c'est définit... on ne le réinclut pas. SAUV
#define __POPULATION_H__ //tu le définis

// ======================================================================
//                                 Bibliothèques
// ======================================================================
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

// ======================================================================
//                                Fichiers Projets
// ======================================================================

#include "Agent.h"
//forward declarations
class Gaia;

// ======================================================================
//                             Déclarations des classes
// ======================================================================


class Population
{
public:
		
	// ==================================================================
	//                                Enums
	// ==================================================================
	
	// ==================================================================
	//                               Constructeurs
	// ==================================================================
	Population(Gaia* ga);//Créé une population de 10 agents de couleur aléatoire
	/*Permet d'indiquer le nombre d'agent désiré et la couleur de la population
		au moment de la construction*/
	Population(Gaia* ga, int nombre_agent, int _taille, int _couleur);
	

	// ==================================================================
	//                                Destructeurs
	// ==================================================================
	virtual ~Population( void );
	
	// ==================================================================
	//                            Accesseurs: getters
	// ==================================================================
	inline int get_nombre_agents(void);
	
	inline Agent* get_agent(int i);
 
	inline Population* get_proie(int i); // Renvoie un pointeur vers la population d'indice i dans le vecteur "proies"
	inline int get_nombre_population_proies(); // Renvoie le nombre de population de proies
	inline Agent* get_proie_agent(int i, int j); //Renvoie un pointeur vers l'agent j d'une population proie i 
	inline int get_nombre_agent_population_proies(int i); //Renvoie le nombre d'agents dans la population de proie i
 
	/*Ces quatres fonctions ont un fonctionnement similaire aux quatres précédentes, mais permettent d'accéder aux
		informations sur les prédateurs de la population actuelle plutôt qu'à leur proies*/
	inline Population* get_predateur(int i);
	inline int get_nombre_population_predateurs();
	inline Agent* get_predateur_agent(int i, int j);
	inline int get_nombre_agent_population_predateurs(int i);
 
	inline int get_taille(void);
	inline int get_couleur(void);
	inline double get_rayon_perception(void);
	inline double get_rayon_contact(void);
	// ==================================================================
	//                            Accesseurs: setters
	// ==================================================================
 
	void ajouter_proies(Population * nouvelles_proies);
	
	// ==================================================================
	//                                Opérateurs
	// ==================================================================

	// ==================================================================
	//                             Methodes Publiques
	// ==================================================================
	/*Déplace tous les agents de la population*/
	void deplacer(void);
	/*Affiche tous les agents de la population*/
	void afficher(void);
	//Ces trois méthodes permettent de mesurer différentes variables propres à la population:
	//La vitesse moyenne des agents
	double calculer_vitesse_moyenne(void);
	//Le nombre de sous-groupes
	int calculer_nombre_groupes(void);
	//Le nombre d'agents qui viennent de capturer une proie
	int nombre_mangeant(void);
	// ==================================================================
	//                            Attributs Publiques
	// ==================================================================





protected:

	// ==================================================================
	//                           Constructeurs Interdits
	// ==================================================================
	Population( void )
	{
		printf( "%s:%d: erreur: appel au constructeur interdit.\n", __FILE__, __LINE__ );
		exit( EXIT_FAILURE );
	};

	Population( const Population &model )
	{
		printf( "%s:%d: erreur: appel au constructeur interdit.\n", __FILE__, __LINE__ );
		exit( EXIT_FAILURE );
	};


	// ==================================================================
	//                              Methodes Protégées
	// ==================================================================

	// ==================================================================
	//                             Attributs Protégés
	// ==================================================================
	
	Gaia* mon_gaia;
	vector<Agent*> agents; //Tous les agents de la population
	vector<Population*> proies; //Toutes les populations proies de la population
	vector<Population*> predateurs; //Toutes les populations prédateur de la population
	
	int taille;
	int couleur; 
	double rayon_perception;
	double rayon_contact;
	
};


// ======================================================================
//                              Définitions Getters
// ======================================================================

/***AGENTS***/

inline int Population::get_nombre_agents(void)
{
	return agents.size();
}

inline Agent* Population::get_agent(int i)
{
	return agents[i];
}

/***PROIES***/
	
inline Population* Population::get_proie(int i)
{
	return proies[i];
}

inline int Population::get_nombre_population_proies()
{
	return proies.size();
}

inline Agent* Population::get_proie_agent(int i,int j)
{
	return proies[i]->agents[j];
}
	
inline int Population::get_nombre_agent_population_proies(int i)
{
	if (i < proies.size() )
	{
		return proies[i]->get_nombre_agents();
	}	
}
	
/***PREDATEURS***/

inline Population* Population::get_predateur(int i)
{
	return predateurs[i];
}
	
inline int Population::get_nombre_population_predateurs()
{
	return predateurs.size();
}
	
inline Agent* Population::get_predateur_agent(int i, int j)
{
	return predateurs[i]->agents[j];
}

inline int Population::get_nombre_agent_population_predateurs(int i)
{
	if (i < predateurs.size() )
	{
		return predateurs[i]->get_nombre_agents();
	}	
}
	
	
/***ATTRIBUTS***/
inline int Population::get_taille(void)
{
	return taille;
}

inline int Population::get_couleur(void)
{
	return couleur;
}

inline double Population::get_rayon_perception(void)
{
	return rayon_perception;
}

inline double Population::get_rayon_contact(void)
{
	return rayon_contact;
}

// ======================================================================
//                              Définitions Setters
// ======================================================================

// ======================================================================
//                          Définitions des Opérateurs
// ======================================================================

// ======================================================================
//                          Définitions des fonctions Inline
// ======================================================================


#endif // __POPULATION__H__
