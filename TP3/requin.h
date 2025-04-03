#pragma once

#include "ocean.h"
#include "Liste.h"
//#include "ocean.h"


/******************************************************************************/
/*  requin.H                                                                 */
/*  Module utilitaire qui permet de maintenir la liste des requins vivants   */
/*  Conception : Lucas Logé                                                   */
/******************************************************************************/
#if !defined (LIB_REQUIN)
#define LIB_REQUIN 1


#define MAX_AGE_REQUIN 1500 //âge maximal du requin
#define NB_JRS_PUB_REQUIN 90 //nombre de jours avant la puberté
#define NB_JRS_GEST_REQUIN 30 //nombre de jours de gestation
#define ENERGIE_DIGESTION 10 //valeur ajoutée à l'indice d’énergie après un repas

/*
Reçoit la liste de requins, l'ocean, nb de requins voulu et génère autant de requins
que nécessaire chacun dans une case VIDE
*/

void init_liste_r(t_liste* liste_p, t_ocean ocean, int nb_r_vlu);//ocean

/*
	Déplace le requin vers 1 case vide adjacente de l'océan
	Reçoit l'ocean & le pointeur du noeud du requin concerné & modifie les données px & py de celui-ci vers la nouvelle case
	Retourne 1 si l'opération foncitonne sinon retourne 0
*/

int deplace_requin(t_noeud* requin, t_ocean ocean);

/*
	Ajoute un nouveau bébé-requin à la liste dans une case vide de l'océan
	Reçoit la liste des requins, l'océan et le pointeur attribué au requin-parent
*/
int ajout_bb_r(t_liste* liste, t_ocean ocean, t_noeud* r_parent);

/*
	Retire un requin de la liste_requin & vide sa case attribuée de l'océan
*/
void retirer_requin(t_liste* liste, t_ocean ocean);


/*
	Structure speciale pour transmettre les informations autour d'un requin & la direction disponible choisie
*/
typedef struct {
	t_contenu case_adj[3][3];	//etat des cases autout d'une coordonnee de l'ocean
	int plein;					//indique si toutes les cases sont pleines(1) ou non(0)
	int bordx;					//indique si l'emplacement se trouve completement a gauche(1) ou a droite(2) ou normal(0)
	int bordy;					//indique si l'emplacement se trouve completement en haut(1) ou en bas(2) ou normal(0)
	t_direction dir_dispo;		//indique une direction disponible vide ou envoyer un element
	int n_y;					//indique le y de la nouvelle case
	int n_x;					//indique le x de la nouvelle case
}t_info_adj;

/*
	Fonction fourre-tout qui retourne une structure avec:
		le tableau de cases adj
		si toutes les cases sont pleines (int 1 ou 0)
		si on se trouve sur un des bords de l'ocean
		quelle direction a ete selectionnee comme nouvelle position
		les coordonnees de la nouvelle case
*/
t_info_adj* case_adj_vides(t_noeud* requin, t_ocean ocean);


#endif