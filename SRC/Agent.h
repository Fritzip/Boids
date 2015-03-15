//***********************************************************************
//
//
//
//***********************************************************************



#ifndef __AGENT_H__ //évite la double inclusion "if not define" au second passage c'est définit... on ne le réinclut pas. SAUV
#define __AGENT_H__ //tu le définis

// ======================================================================
//                                 Bibliothèques
// ======================================================================
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "Vec2d.h"

// ======================================================================
//                                Fichiers Projets
// ======================================================================

class Population;
class Gaia;

// ======================================================================
//                             Déclarations des classes
// ======================================================================


class Agent
{
public :
    
  // ==================================================================
  //                                 Enums
  // ==================================================================
  
  // ==================================================================
  //                               Constructeurs
  // ==================================================================
  
  Agent(Gaia* ga,Population* pop);

  // ==================================================================
  //                                Destructeurs
  // ==================================================================
  
  virtual ~Agent( void );

  // ==================================================================
  //                            Accesseurs: getters
  // ==================================================================
  
  inline Vec2d get_position(void);
  inline Vec2d get_vitesse(void);

/*ne_mange_pas sert de booléen  pour savoir l'agent vient de capturer une proie,
autrement dit s'il est arrêté. Cet entier est nul si l'agent est arrêté, et égal 
à 1 dans le cas contraire*/
  inline int get_ne_mange_pas(void);

  // ==================================================================
  //                            Accesseurs: setters
  // ==================================================================
  
  inline void set_position(Vec2d v);
  inline void set_vitesse(Vec2d v);
  
  // ==================================================================
  //                                Opérateurs
  // ==================================================================

  // ==================================================================
  //                             Methodes Publiques
  // ==================================================================
  
  
  void afficher(void);

  /*Calcul de la vitesse en fonction de la position relative des autres agents, 
    des proies, des prédateurs, des bords ...*/
  void calculer_vitesse(void);

  /*Vérifie la présence d'un agent dans un vecteur. Renvoie 0 si l'agent n'y est pas
    et 1 s'il y est. Cette méthode est utilisée dans le décompte des sous-groupes de population.*/
  char est_dans_vector(std::vector<Agent*>);
  
  // ==================================================================
  //                            Attributs Publiques
  // ==================================================================

protected :

  // ==================================================================
  //                           Constructeurs Interdits
  // ==================================================================
  Agent( void )
		{
		  printf( "%s:%d: erreur: appel au constructeur interdit.\n", __FILE__, __LINE__ );
		  exit( EXIT_FAILURE );
		};
  
  Agent( const Agent &model )
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
  
  Vec2d position;
  Vec2d vitesse;
  Population*  ma_population;
  Gaia*  mon_gaia;

  /*ne-mange_pas=0 si l'agent vient de capturer une proie et est donc arrêté
    et ne-mange_pas=1 si l'agent est en mouvment*/
  int ne_mange_pas;
  /*compteur permettant la gestion du temps d'arrêt des agent après la capture 
    d'une proie*/
  int compteur_mange;
  

};


// ======================================================================
//                              Définitions Getters
// ======================================================================

Vec2d Agent::get_position(void)
	{
		return position;
	}

Vec2d Agent::get_vitesse(void)
	{
		return vitesse;
	}

int Agent::get_ne_mange_pas(void)
	{
		return ne_mange_pas;
	}
	
// ======================================================================
//                              Définitions Setters
// ======================================================================

void Agent::set_position(Vec2d a)
	{
		position=a;
	}

void Agent::set_vitesse(Vec2d a)
	{
		vitesse=a;;
	}

// ======================================================================
//                          Définitions des Opérateurs
// ======================================================================

// ======================================================================
//                          Définitions des fonctions Inline
// ======================================================================


#endif // __AGENT_H__
