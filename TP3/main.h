#pragma once
#define _CRT_SECURE_NO_WARNINGS
/****************************************************************************/
/*  main.h																	*/
/*  Fichier d'en t�te de l'algorithme										*/
/*  Conception : Lucas Loge                                                 */
/****************************************************************************/
#include "requin.h"
#include "poisson.h"
#include "SimParam.h"


#define TOUCHE_ESC		27

// Couleurs
#define COULEUR_ROUGE       12
#define COULEUR_VERT		10
#define COULEUR_VIOLET		13
#define COULEUR_DEFAUT      7   //BLANC


typedef struct
{
	int nb_poisson;
	int nb_requin;
	int temps;
}t_stats;


/*
	fonction qui incremente de 1 energie du requin qui mange le poisson
*/
static int requin_mange(t_ocean ocean, t_noeud* poisson);

/*
	fonction de l'algorithme
*/
static void algorithme(t_ocean ocean, t_liste* liste_poisson, t_liste* liste_requin, int temps, int mode);



