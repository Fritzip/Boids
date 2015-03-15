//***********************************************************************
// 
//
//
//***********************************************************************



#ifndef __VEC2D_H__ //évite la double inclusion "if not define" au second passage c'est définit... on ne le réinclut pas. SAUV
#define __VEC2D_H__ //tu le définis

// ======================================================================
//                                 Bibliothèques
// ======================================================================
#include <cstdio>
#include <cstdlib>


// ======================================================================
//                                Fichiers Projets
// ======================================================================




// ======================================================================
//                             Déclarations des classes
// ======================================================================


class Vec2d
{
  public :
    
    // ==================================================================
    //                                 Enums
    // ==================================================================
  
    // ==================================================================
    //                               Constructeurs
    // ==================================================================
  Vec2d( void );//constructeur par défaut (x=y=0)
  Vec2d(double _x, double _y);//constructeur par valeur
  Vec2d( const Vec2d &modele );//constructeur par copie,utile notamment pour les opérateurs (+,-...)
    // ==================================================================
    //                                Destructeurs
    // ==================================================================
  virtual ~Vec2d( void );

    // ==================================================================
    //                            Accesseurs: getters
    // ==================================================================
  inline double get_x(void);
  inline double get_y(void);
    // ==================================================================
    //                            Accesseurs: setters
    // ==================================================================
  inline void set_x(double a);
  inline void set_y(double a);
    // ==================================================================
    //                                Operateurs
    // ==================================================================
  //Ces opérateurs permettent les sommes vectorielless classiques
  inline Vec2d & operator+=(const Vec2d & a);
  inline Vec2d & operator-=(const Vec2d & a);
  inline Vec2d & operator=(const Vec2d & a);
  inline Vec2d operator-(const Vec2d & a);
  inline Vec2d operator+(const Vec2d & a);
  inline Vec2d operator*(double const & a);
  inline Vec2d operator/(double const & a);

    // ==================================================================
    //                             Methodes Publiques
    // ==================================================================
  //Calcule de la distance entre deux points, au carré, pour éviter d'alourdire le calcul, autrement dit, le produit scalaire du vecteur courant avec celui passé en argument. 
  double distance_carre(const Vec2d & b);
    // ==================================================================
    //                            Attributs Publiques
    // ==================================================================





  protected :

    // ==================================================================
    //                           Constructeurs Interdits
    // ==================================================================
    

    // ==================================================================
    //                              Methodes Protégées
    // ==================================================================

    // ==================================================================
    //                             Attributs Protégés
    // ==================================================================
  double x;
  double y;

};


// ======================================================================
//                              Définitions Getters
// ======================================================================
double Vec2d::get_x(void)
{
  return x;
}
double Vec2d::get_y(void)
{
  return y;
}
// ======================================================================
//                              Définitions Setters
// ======================================================================
void Vec2d::set_x(double a){
  x=a;
}
void Vec2d::set_y(double a){
  y=a;
}
// ======================================================================
//                          Définitions des Opérateurs
// ======================================================================
Vec2d & Vec2d::operator+=(Vec2d const & a)
{
  //Vec2d* ret=new Vec2d(*this);
  x+=a.x;
  y+=a.y;
  return *this;
}
Vec2d & Vec2d::operator-=(Vec2d const & a)
{
  //Vec2d* ret=new Vec2d(*this);
  x-=a.x;
  y-=a.y;
  return *this;
}
Vec2d Vec2d::operator-(Vec2d const & a)
{
  Vec2d ret;
  ret.x=this->x-a.x;
  ret.y=this->y-a.y;
  return ret;
}
Vec2d Vec2d::operator+(Vec2d const & a)
{
  Vec2d ret;
  ret.x=this->x+a.x;
  ret.y=this->y+a.y;
  return ret;
}

Vec2d & Vec2d::operator=(Vec2d const & a)
{
  this->x=a.x;
  this->y=a.y;
  return *this;
}

Vec2d Vec2d::operator*(double const & a)
{
  Vec2d ret;
  ret.x=(this->x)*a;
  ret.y=(this->y)*a;
  return ret;
}

Vec2d Vec2d::operator/(double const & a)
{
  Vec2d ret;
  ret.x=this->x/a;
  ret.y=this->y/a;
  return ret;
}
// ======================================================================
//                          Définitions des fonctions Inline
// ======================================================================


#endif // __VEC2D_H__
