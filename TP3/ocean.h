#pragma once

// for debug
#include <stdlib.h> 
#include <stdio.h>

#include "util.h"
#include "utilitaire_affichage.h"

#define HAUTEUR 60
#define LARGEUR 120

typedef enum { HAUT, HAUT_D, DROITE, BAS_D, BAS, BAS_G, GAUCHE, HAUT_G } t_direction;

// Enumeration pour une case de l'oc�an
typedef enum { VIDE, POISSON, REQUIN } t_contenu;

// Structure qui represente une case de l'ocean
typedef struct {
	t_contenu contenu; // VIDE, POISSON ou REQUIN
	void* animal;      // Pointeur générique a un animal a cette case, sinon NULL
} t_case;

// Taleau 2d qui contient des case(contenu et pointeur vers l'animal)
typedef t_case t_ocean[HAUTEUR][LARGEUR];


typedef struct {
	t_contenu case_adj[3][3];	//etat des cases autout d'une coordonnee de l'ocean
	int plein;					//indique si toutes les cases sont pleines(1) ou non(0)
	int bordx;					//indique si l'emplacement se trouve completement a gauche(1) ou a droite(2) ou normal(0)
	int bordy;					//indique si l'emplacement se trouve completement en haut(1) ou en bas(2) ou normal(0)
	t_direction dir_dispo;		//indique une direction disponible vide ou envoyer un element
	int n_y;					//indique le y de la nouvelle case
	int n_x;					//indique le x de la nouvelle case
}t_info_adj;


// Mettre toute les cases à contenu VIDE et animal NULLE
void vider_ocean(t_ocean ocean);

// Obtient le contenu d'une case à la position x y
// Retourne une valeur t_contenu
t_contenu get_contenu_case(t_ocean ocean, int x, int y);


int get_ptrAnimal_case(t_ocean ocean, int x, int y, void* ptrAnimal);

int nvx_contenu_ptr(t_ocean ocean, int posx, int posy, void* nv_ptr, t_contenu nv_ctn);

int effacer_contenu(t_ocean ocean, int posx, int posy);

void dessiner_ocean(t_ocean ocean);


/*
	Fonction speciale qui retourne une structure avec:
		le tableau de cases adj
		si toutes les cases sont pleines (int 1 ou 0)
		si on se trouve sur un des bords de l'ocean
		quelle direction a ete selectionnee comme nouvelle position
		les coordonnees de la nouvelle case
	Elle remplit les fonctions :
		Compter le nombre de cases voisines libres autour d’une coordonnée (posx, posy).
		Choisir aléatoirement une case voisine libre autour d’une coordonnée (posx, posy).
*/
t_info_adj* case_adj_vides(t_ocean ocean, int posx, int posy);
