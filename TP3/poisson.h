
#include "ocean.h"
#include "Liste.h"
//#include "ocean.h"


/******************************************************************************/
/*  POISSON.H                                                                 */
/*  Module utilitaire qui permet de maintenir la liste des poissons vivants   */
/*  Conception : Lucas Logé                                                   */
/******************************************************************************/
#if !defined (LIB_POISSON)
#define LIB_POISSON 1

#define MAX_POISSON 1000 //nombre maximal de poissons avant la surpopulation
#define MAX_AGE_POISSON 150 //âge maximal du poisson
#define NB_JRS_PUB_POISSON 30 //nombre de jours avant la puberté
#define NB_JRS_GEST_POISSON 15 //nombre de jours de gestation
#define ENERGIE_INIT_POISSON 3 //valeur initiale d'énergie



/*
Reçoit la liste de poissons, l'ocean, nb de poissons voulu et génère autant de poissons
que nécessaire chacun dans une case VIDE
*/

void init_liste_p(t_liste* liste_p,t_ocean ocean, int nb_p_vlu);//ocean

/*
	Déplace le poisson vers 1 case vide adjacente de l'océan
	Reçoit l'ocean & le pointeur du noeud du poisson concerné & modifie les données px & py de celui-ci vers la nouvelle case
	Retourne 1 si l'opération foncitonne sinon retourne 0
*/

int deplace_poisson(t_noeud* poisson,t_ocean ocean);

/*
	Ajoute un nouveau bébé-poisson à la liste dans une case vide de l'océan
	Reçoit la liste des poissons, l'océan et le pointeur attribué au poisson-parent
*/
int ajout_bb_p(t_liste* liste,t_ocean ocean,t_noeud* p_parent);

/*
	Retire un poisson de la liste_poisson & vide sa case attribuée de l'océan
*/
int retirer_poisson(t_liste* liste_p,t_ocean* ocean);

/*
	Retourne un tableau avec les cases vides autour d'un poisson
*/
t_contenu* case_adj_vides(t_noeud* poisson, t_ocean ocean);


#endif