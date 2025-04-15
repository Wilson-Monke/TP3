#pragma once

// for debug
#include <stdlib.h> 
#include <stdio.h>

#include "util.h"
#include "utilitaire_affichage.h"

#define HAUTEUR_OCEAN 60
#define LARGEUR_OCEAN 120

typedef enum { HAUT, HAUT_D, DROITE, BAS_D, BAS, BAS_G, GAUCHE, HAUT_G } t_direction;

// Enumeration pour une case de l'oc�an
typedef enum { VIDE, POISSON, REQUIN } t_contenu;

// Structure qui represente une case de l'ocean
typedef struct {
	t_contenu contenu; // VIDE, POISSON ou REQUIN
	void* animal;      // Pointeur générique a un animal a cette case, sinon NULL
} t_case;

// Taleau 2d qui contient des case(contenu et pointeur vers l'animal)
typedef t_case t_ocean[HAUTEUR_OCEAN][LARGEUR_OCEAN];


typedef struct {
	int invalide;
	int posy;
	int posx;
} t_location_case_vide;



// Mettre toute les cases à contenu VIDE et animal NULLE
void vider_ocean(t_ocean ocean);

// Obtient le contenu d'une case à la position x y
// Retourne une valeur t_contenu
t_contenu get_contenu_case(t_ocean ocean, int x, int y);

int get_ptrAnimal_case(t_ocean ocean, int x, int y, void* ptrAnimal);

int nvx_contenu_ptr(t_ocean ocean, int posx, int posy, void* nv_ptr, t_contenu nv_ctn);

int effacer_contenu(t_ocean ocean, int posx, int posy);

void dessiner_ocean(t_ocean ocean);

static int nb_case_adj_vide(t_ocean ocean, int posx, int posy);

t_location_case_vide get_rand_case_vide(t_ocean ocean, int posx, int posy);


void print_ocean(t_ocean ocean);
void print_poissons(t_ocean ocean);