#pragma once
/****************************************************************************/
/*  main.h																	*/
/*  Fichier d'en t�te de l'algorithme										*/
/*  Conception : Lucas Loge                                                 */
/****************************************************************************/
#include "requin.h"
#include "poisson.h"


#define _CRT_SECURE_NO_WARNINGS

#define MODE_GRAPHIQUE	1
#define MODE_ECRI_FICH	0
#define TOUCHE_ESC		27
#define NB_ANIMAUX_VLU	500	
#define POURCENTAGE_POISSON 0.8
#define POURCCENTAGE_REQUIN 0.2


// Couleurs
#define COULEUR_ROUGE       12
#define COULEUR_VERT		10
#define COULEUR_VIOLET		13
#define COULEUR_DEFAUT      7   //BLANC

typedef struct
{
	int nb_poisson;
	int nb_requin;
}t_stats;


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

/*
	Fonction qui print la liste dans l'invite de commande
*/
void afficher_liste(t_liste* liste);
