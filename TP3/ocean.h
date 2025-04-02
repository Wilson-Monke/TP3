#pragma once
#pragma once

#ifndef OCEAN_H
#define OCEAN_H

#include "animal.h"
#include "Liste.h"
#include <list>

#define HAUTEUR 60
#define LARGEUR 120

// �num�ration pour une case de l'oc�an
typedef enum {
    VIDE,
    POISSON,
    REQUIN
} t_contenu;

// Structure qui repr�sente une case de l'oc�an
typedef struct {
    t_contenu type;
    // Pointeur vers un poisson ou requin
    void* animal;
} t_case;

// Structure de l'oc�an qui contient une grille et des listes d'animaux
typedef struct {
    t_case grille[HAUTEUR][LARGEUR];
    liste poissons;
    liste requins;
} t_ocean;

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
