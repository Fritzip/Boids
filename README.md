**************************************************************************
*  			                    Projet Boids C++                             *
*			                                                                   *
*				      Abernot Jonas, Prudent Emma & Sainlot Maxime               *
*				                                                                 *
*************************** Des poissons volants**************************


##########################################################################
###                           Description                              ###
##########################################################################
Ce programme permet la simulation de mouvements collectifs au sein d'un groupe d'individus, symbolisés ici par des poissons. 
Il met en évidence l'apparition d'un comportement émergent (formation de groupes qui se déplacent ensemble) à partir de règles appliquées sur les individus. Il permet également de faire quelques mesures sur les variables de la modélisation.
**************************************************************************



##########################################################################
###                       Les fichiers fournis                         ###
##########################################################################
- Gaia_main : Fichier contenant le main.
- Gaia : Classe principale qui gère l'ensemble de la simulation.
- Population : Classe permettant la gestion des populations présentent dans le monde.
- Agent : Classe permettant la gestion des agents des populations présentent dans le monde.
- Caillou : Classe permettant la gestion et l'affichage des obstacles du monde.
- Vec2d : Classe permettant de faciliter l'utilisation de vecteurs (surcharge d'opérateurs).
- bwindow : Classe permettant l'affichage. Modifié pour permettre l'affichage désiré des agents et des obstacles.
- pop_defaut : Fichier texte permettant de modifier les principaux paramètres de la simulation (voir plus loin).
- makefile
**************************************************************************


##########################################################################
###                     Utilisation du programme                       ###
##########################################################################

## par défaut :

# Pour compiler le programme :

	-> Commande : make

# Pour lancer le programme :

	-> Commande : ./poisson_exe
	
	/!\ Cette commande lance une partie "par défaut". Une grande partie des paramètres sont modifiable SANS RECOMPILATION ayant été externalisé dans un fichier "pop_defaut". D'autres paramètres, en revanche, demande une modification dans le code du programme (voir Potentialités d'amélioration).


 ## Pour modifier les paramètres de la simulation par défaut :

# Pour lancer une partie sauvegardée :

	-> Commande : make
	-> Commande : ./poisson_exe -load nom_fichier_a_charger
	
	/?\ Un ensemble de parties sauvegardées présentant des comportements différents est proposé dans le dossier "Parties_sauvegardées"

# Pour lancer une partie avec la possibilité de la sauvegarder :

	-> Commande : make
	-> Commande : ./poisson_exe -save nom_fichier_dans_lequel_sauvegarder

	/!\ Durant l'exécution du programme appuyer sur la touche "m" pour déclencher la sauvegarde.

# Pour mesurer la vitesse moyenne de chaque population au cours du temps, le nombre de sous-groupe de chaque population ou encore le nombre de poissons ayant avalé une proie dans l'instant précédent :
	
	-> Décommenter les lignes de code correspondantes (Gaia.cpp: ligne 156, 157 ou 158) et lancer la simulation
	  
	/!\ Les fichiers ainsi écrits ne sont pas détruits lorsqu'une nouvelle simulation est lancée, les variables mesurées sont simplement ajoutée à la suite des première, ce qui peut le rendre difficile à exploiter.
	    Penser à les supprimer ou à déplacer les fichiers "vitesses.moyennes", "nombre.groupes" et "nombre.mangeant" avant de relancer une simulation.
**************************************************************************


##########################################################################
###                         Fichier pop_defaut                         ###
##########################################################################

Exemple de fichier pop_defaut (les sauts de lignes sont ajoutés pour plus de lisibilité):

homotetie_largeur: 64 <- le monde Gaia a une taille fiche mais on peut modifier ici la taille affichée par proportinalité.
homotetie_hauteur: 64

dt: 0.01 <- Paramètre codé en dur dans le code donc les modifications faîtes ici n'ont aucun effet.

Nombre_pop: 2 <- Nombre de populations souhaitées dans la simulation (doit correspondre au nombre de populations renseignées)
Pop1: 5 10027008 <- Première population avec le nombre d'agents et leur couleur (renseigné en décimal)
Pop2: 5 10030000 <- Deuxième population

Nombre_obstacles: 15 <- Nombre d'obstacles souhaité dans le monde
Nombre_recifs: 3 <- Nombre de récifs souhaité (les obstacles sont rassemblés dans l'espace)

Regles: 1 <- Nombre de règles de proie/prédateur renseignées
Regle1: 0 1 <- Règle 1 avec le premier chiffre qui correspond à la population prédateur et le deuxième à la population proie

gamma[0]: 5.5 //5.5//moyennage_des_vitesses <- Ensemble des paramètres influençant les différentes règles de calcul
gamma[1]: 150 //150//redirection_vers_le_barycentre_du_groupe <- Valeur par défaut renseignée
gamma[2]: 550 //550//repulsion <- Ainsi qu'un commentaire permettant de savoir à quelle règle est rattaché le coefficient
gamma[3]: 750 //750//esquive_algues
gamma[4]: 100 //100//peur_des_bords
gamma[5]: 140 //140//attaque
gamma[6]: 300 //300//fuite

/!\ La syntaxe doit être scrupuleusement respectée.
**************************************************************************


##########################################################################
###            Fonctionnalités additionnelles du programme             ###
##########################################################################
- Le joueur : Le premier agent de la première population est dirigeable par l'utilisateur à l'aide des touches 'z','s','q','d'. Sa maniabilité est perfectible 
- Création de récifs : Les algues s'agglutinent en récifs suivant le nombre défini par l'utilisateur dans le fichier "pop_defaut"
- Mange et réapparition dans les recifs : Les prédateurs au contact de proie les mangent et s'arrètent pour manger. Les proies mangées réaparaissent aléatoirement dans un des récifs avec une vitesse nulle.
- Repulsion des bords : Un agents non poursuivit fera demi tour avant de se heurter au bord.
**************************************************************************


##########################################################################
###               Améliorations possibles envisagées                   ###
##########################################################################

# Améliorer la sauvegarde des parties en incluant la position des obstacles et non plus seulement leur nombre.
# Améliorer la maniabilité de l'agent dirigeable
# Améliorer les fonctions d'affichage (temps d'exécution)
# Permettre la modification de la taille des agents
# Améliorer la sécurité de "pop_defaut" et y inclure TOUT les paramètres (rayon de perception, de contact...)
# Ajouter des fonctions de mesures pour permettre une meilleure analyse des simulations
# Améliorer l'affichage (diminuer le clignotement)
# Attribuer des gammas pour chaque population
**************************************************************************


##########################################################################
###                       Aspect Graphique                             ###
##########################################################################
Afin d'obtenir une représentation plus réel, les agents ont une forme de poisson dont la forme varie avec le vecteur vitesse (sens de déplacement) leur donnant l'illusion d'un mouvement. Les obstacles sont des cailloux sur lesquels poussent des algues. Seul la base repoussent les poissons.
**************************************************************************

