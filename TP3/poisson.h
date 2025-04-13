
#include "ocean.h"
#include "Liste.h"
//#include "ocean.h"


/******************************************************************************/
/*  POISSON.H                                                                 */
/*  Module utilitaire qui permet de maintenir la liste des poissons vivants   */
/*  Conception : Lucas Log�                                                   */
/******************************************************************************/
#if !defined (LIB_POISSON)
#define LIB_POISSON 1

#define MAX_POISSON 1000 //nombre maximal de poissons avant la surpopulation
#define MAX_AGE_POISSON 150 //�ge maximal du poisson
#define NB_JRS_PUB_POISSON 30 //nombre de jours avant la pubert�
#define NB_JRS_GEST_POISSON 15 //nombre de jours de gestation
#define ENERGIE_INIT_POISSON 3 //valeur initiale d'�nergie



/*
Re�oit la liste de poissons, l'ocean, nb de poissons voulu et g�n�re autant de poissons
que n�cessaire chacun dans une case VIDE
*/

void init_liste_p(t_liste* liste_p, t_ocean ocean, int nb_p_vlu);//ocean

/*
	D�place le poisson vers 1 case vide adjacente de l'oc�an
	Re�oit l'ocean & le pointeur du noeud du poisson concern� & modifie les donn�es px & py de celui-ci vers la nouvelle case
	Retourne 1 si l'op�ration foncitonne sinon retourne 0
*/

int deplace_poisson(t_noeud* poisson, t_ocean ocean);

/*
	Ajoute un nouveau b�b�-poisson � la liste dans une case vide de l'oc�an
	Re�oit la liste des poissons, l'oc�an et le pointeur attribu� au poisson-parent
*/
int ajout_bb_p(t_liste* liste, t_ocean ocean, t_noeud* p_parent);

/*
	Retire un poisson de la liste_poisson & vide sa case attribu�e de l'oc�an
*/
void retirer_poisson(t_liste* liste, t_ocean ocean);



#endif