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
	fonction qui incremente de 1 energie du requin qui mange le poisson
*/
static int requin_mange(t_ocean ocean, t_noeud* poisson);

/*
	fonction de l'algorithme
*/
static void algorithme(t_ocean ocean, t_liste* liste_poisson, t_liste* liste_requin, int temps, int mode);







/*
	FONCTION DEBUG A RETIRER!!
*/

void afficher_liste(t_liste* liste);
#endif