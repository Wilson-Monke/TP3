#pragma once

/******************************************************************************/
/*  requin.H                                                                 */
/*  Module utilitaire qui permet de maintenir la liste des requins vivants   */
/*  Conception : Lucas Log�                                                   */
/******************************************************************************/
#include "ocean.h"
#include "Liste.h"
#include "SimParam.h" // Paramètres de simulations


/*
Re�oit la liste de requins, l'ocean, nb de requins voulu et g�n�re autant de requins
que n�cessaire chacun dans une case VIDE
*/

void init_liste_r(t_liste* liste_p, t_ocean ocean, int nb_r_vlu);//ocean

/*
	D�place le requin vers 1 case vide adjacente de l'oc�an
	Re�oit l'ocean & le pointeur du noeud du requin concern� & modifie les donn�es px & py de celui-ci vers la nouvelle case
	Retourne 1 si l'op�ration foncitonne sinon retourne 0
*/

int deplace_requin(t_noeud* requin, t_ocean ocean, int mode);

/*
	Ajoute un nouveau b�b�-requin � la liste dans une case vide de l'oc�an
	Re�oit la liste des requins, l'oc�an et le pointeur attribu� au requin-parent
*/
int ajout_bb_requin(t_liste* liste, t_ocean ocean, t_noeud* r_parent);

/*
	Retire un requin de la liste_requin & vide sa case attribu�e de l'oc�an
*/
void retirer_requin(t_liste* liste, t_ocean ocean, int mode);


