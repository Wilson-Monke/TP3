﻿#pragma once
/******************************************************************************/
/*  POISSON.H                                                                 */
/*  Module utilitaire qui permet de maintenir la liste des poissons vivants   */
/*  Conception : Lucas Log�                                                   */
/******************************************************************************/
#include "ocean.h"
#include "Liste.h"
#include "SimParam.h"

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

int deplace_poisson(t_noeud* poisson, t_ocean ocean, int mode);

/*
	Ajoute un nouveau b�b�-poisson � la liste dans une case vide de l'oc�an
	Re�oit la liste des poissons, l'oc�an et le pointeur attribu� au poisson-parent
*/
int ajout_bb_poisson(t_liste* liste, t_ocean ocean, t_noeud* p_parent);

/*
	Retire un poisson de la liste_poisson & vide sa case attribu�e de l'oc�an
*/
void retirer_poisson(t_liste* liste, t_ocean ocean, int mode);



