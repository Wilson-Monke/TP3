
#ifndef OCEAN_H
#define OCEAN_H

#include <stdlib.h> // useless?

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

// Structure de l'oc�an qui contient une grille et des listes d'animaux
typedef t_case t_ocean[HAUTEUR][LARGEUR];


// Initialisation de l'oc�an
void initialiser_ocean(t_ocean* ocean);

// Ajout d'un animal dans l'oc�an
void ajouter_animal(t_ocean* ocean, int x, int y, t_contenu type);

// D�placement des animaux dans l'oc�an
void deplacer_animaux(t_ocean* ocean);

// Suppression des animaux morts
void nettoyer_ocean(t_ocean* ocean);

// Affichage de l'oc�an
void afficher_ocean(const t_ocean* ocean);

#endif // OCEAN_H
