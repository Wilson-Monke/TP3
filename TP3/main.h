#pragma once
#include "requin.h"
#include "poisson.h"

/****************************************************************************/
/*  main.h																	*/
/*  Fichier d'en t�te de l'algorithme										*/
/*  Conception : Lucas Loge                                                 */
/****************************************************************************/


#if !defined (MAIN_H)
#define MAIN_H 1

/*
	fonction qui determine si le poisson se fait manger
*/
int se_fait_manger(t_ocean ocean, t_noeud* poisson);

/*
	fonction qui incremente de 1 energie du requin qui mange le poisson
*/
void requin_mange(t_ocean ocean, t_noeud* poisson);

/*
	fonction de l'algorithme
*/
void algorithme(t_ocean ocean, t_liste* liste_poisson, t_liste* liste_requin, int temps, int mode);

/*
	fonction test qui permet de retourner si une erreur s'est produite
*/
void checklist(t_ocean ocean, t_liste* liste);

void afficher_liste(t_liste* liste);
#endif