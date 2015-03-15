//***********************************************************************
//
//
//
//
//***********************************************************************



#ifndef __GAIA_H__ //évite la double inclusion "if not define" au second passage c'est définit... on ne le réinclut pas. SAUV
#define __GAIA_H__ //tu le définis

// ======================================================================
//                                 Bibliothèques
// ======================================================================
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include "bwindow.h"
using namespace std;



// ======================================================================
//                                Fichiers Projet
// ======================================================================
#include "Population.h"
#include "Caillou.h"


// ======================================================================
//                             Déclarations des classes
// ======================================================================


class Gaia
{
public:
    
    // ==================================================================
    //                                 Enums
    // ==================================================================
  
    // ==================================================================
    //                               Constructeurs
    // ==================================================================
    /*Constructeur par défaut de la simulation. Utilise les paramètre décrits
      dans le fichier "pop_défaut"*/
	Gaia( void );
	/*Constructeur permettant de charger ou d'enregistrer une partie,
	  dans le fichier indiqué par nom_fic*/
	Gaia(char save_or_load, string nom_fic);
	Gaia(string nom_save, string nom_load);

    // ==================================================================
    //                                Destructeurs
    // ==================================================================
    
  	virtual ~Gaia( void );

    // ==================================================================
    //                            Accesseurs: getters
    // ==================================================================
    
	inline int get_largeur_fenetre(void);
	inline int get_hauteur_fenetre(void);
	inline bwindow* get_fenetre(void);
	inline Caillou* get_caillou(int i);//Renvoie un pointeur vers le caillou d'indice i du vecteur "cailloux"
	inline int get_nb_cailloux(void);
	inline double get_dt(void); 
	inline double get_gamma(int i);//Renvoie le paramètre d'indice i. La correspondance entre les indices et l'utilisation des paramètre est visible dans le fichier "pop_defaut"
  
   // ==================================================================
    //                            Accesseurs: setters
    // ==================================================================

    // ==================================================================
    //                                Operateurs
    // ==================================================================

    // ==================================================================
    //                             Methodes Publiques
    // ==================================================================
	/*Place aléatoirement des cailloux dans l'espace en respectant
	  le nombre de groupes de cailloux (récifs) indiqué*/
	void generer_cailloux(int nb_cailloux, int nb_recifs); 

	void commencer(void); //affiche la fenêtre et lance l'animation

	/*Calcul les positions et vitesses de tous les agents en fonction de leurs positions relatives*/
	void calculer(void);

	/*Affiche l'ensemble des éléments (agents et obstacles)*/
	void afficher(void);

	/*Enregistre les paramètres de la simulation en cours ainsi que 
	  les positions et vitesses des agents*/
	void enregistrer(string nom_du_fichier_dans_lequel_enregistrer);

	/*Permet de lancer une simulation au point où on l'avait 
	  enregistrée auparavant. La fonction charger prend en paramètre
un fichier de paramètre, construit avec la même syntaxe que "pop_defaut",
tandis que la fonction charger_position assigne les positions et vitesses 
inscrites dans un second fichier au agents construits à l'aide de la
fonction "charger". "charger" est aussi la fonction utilisée pour charger
la simulation par défaut*/
	void charger(string nom_du_fichier_a_charger);
	void charger_position(string nom_du_fichier_a_charger);

	/*Ces trois fonctions permettent de mesurer certaines variables au cours
de la simulation. Les fichiers ainsi créés (respectivement "vitesses.moyennes","nombre.groupes" 
et "nombres.mangeant") doivent être détruits manuellement avant chaque nouvelle simulation.
Ces fichiers sont compatible avec un traitement R ou gnuplot.*/
	/*Fonction enregistrant la vitesses moyennes des agents de chaque population
au cours du temps.*/
	void vitesses_moyennes(int j);
	/*Fonction enregistrant le nombre de sous-groupes de chaque population au cours
	  du temps*/
  	void nb_grp(int f);
	/*Fonction enregistrant le nombre d'agent de chaque population ayant récemment réussi la
	  capture d'une proie*/
  	void nb_mangeant(int f);

    // ==================================================================
    //                            Attributs Publiques
    // ==================================================================
	/*La largeur et la hauteur de l'univers fermé dans lequel évolue les agents*/
	static const int largeur_gaia=17;
	static const int hauteur_gaia=14;
  
protected:

    // ==================================================================
    //                           Constructeurs Interdits
    // ==================================================================
  
 
    Gaia( const Gaia &model )
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
    /*La largeur et la hauteur de la fenêtre où s'affichent les agents et obstacles.
Ces nombres sont reliés par des coefficients à la hauteur et la largeur de l'espace
de la simulation*/
	int largeur_fenetre;
	int hauteur_fenetre;
	int nb_populations;
	int nb_cailloux;
	int nb_recifs;//nombre de groupe de cailloux
	
	Agent* joueur;//pointeur vers le poisson directible par l'utilisateur à travers le clavier
	bwindow* fenetre;
	
	vector<Population*> populations;
	vector<Caillou*> cailloux;
	
	double dt;//Pas de temps utilisé pour la modélisation
	double gamma[7];//Paramètres de déplacement des agents. La correspondance entre les indices et l'utilisation des paramètre est visible dans le fichier "pop_defaut"
	
		/*nom du fichier dans lequel sera enregistrée la simulation à 
l'appel de la fonction "enregistrer"*/
	string fic_save;
};


// ======================================================================
//                              Définitions Getters
// ======================================================================

inline int Gaia::get_largeur_fenetre(void)
{
	return largeur_fenetre;
}

inline int Gaia::get_hauteur_fenetre(void)
{
	return hauteur_fenetre;
}

inline bwindow* Gaia::get_fenetre(void)
{
	return fenetre;
}

inline Caillou* Gaia::get_caillou(int i)
{
	return cailloux[i];
}

inline int Gaia::get_nb_cailloux(void)
{
	return cailloux.size();
}

inline double Gaia::get_dt(void)
{
	return dt;
}

inline double Gaia::get_gamma(int i)
{
	return gamma[i];
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


#endif // __GAIA_H__
