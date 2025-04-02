#pragma once

// for debug
#include <stdlib.h> 
#include <stdio.h>

#include "util.h"
#include "utilitaire_affichage.h"

#define HAUTEUR 60
#define LARGEUR 120

typedef enum { HAUT, HAUT_DR, DROITE, BAS_dR, BAS, BAS_G, GAUCHE, HAUT_G } t_direction;

// �num�ration pour une case de l'oc�an
typedef enum { VIDE,POISSON, REQUIN } t_contenu;

// Structure qui repr�sente une case de l'oc�an
typedef struct {
    t_contenu contenu; // VIDE, POISSON ou REQUIN
    void *animal;      // Pointeur générique à un animal à cette case, sinon NULL
} t_case;

// Taleau 2d qui contient des case(contenu et pointeur vers l'animal)
typedef t_case t_ocean[HAUTEUR][LARGEUR];


// Mettre toute les cases à contenu VIDE et animal NULLE
void vider_ocean(t_ocean ocean);

// Obtient le contenu d'une case à la position x y
int get_contenu_case(t_ocean ocean, int x, int y, t_contenu * contenuCase);


int get_ptrAnimal_case(t_ocean ocean, int x, int y, t_contenu ptrAnimal);
