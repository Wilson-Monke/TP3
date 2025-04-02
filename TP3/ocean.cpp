#include "ocean.h"

// Initialisation de l'oc�an
void initialiser_ocean(t_ocean* ocean) 
{
    /*
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            ocean->grille[i][j].type = VIDE;
            ocean->grille[i][j].animal = NULL;
        }
    
    
    }*/

    /*
    init_liste(); //!!!� V�RIFIER POUR L'ORTHOGRAPHE!!!
    init_liste(); //!!!� V�RIFIER POUR L'ORTHOGRAPHE!!!

    */
 }

// Ajout d'un animal � l'oc�an
void ajouter_animal(t_ocean* ocean, int x, int y, t_contenu type) 
{
    /*
    if (x < 0 || x >= HAUTEUR || y < 0 || y >= LARGEUR) return;
    if (ocean->grille[x][y].type != VIDE) return;

    */
    
}

// D�placement des animaux
void deplacer_animaux(t_ocean* ocean) {
   /* Element* courant = ocean->poissons.tete;
    while (courant != NULL) {
        t_animal* poisson = (t_animal*)courant->valeur;
        deplacer_animal(ocean, poisson);
        courant = courant->suivant;
    }

    courant = ocean->requins.tete;
    while (courant != NULL) {
        t_animal* requin = (t_animal*)courant->valeur;
        deplacer_animal(ocean, requin);
        courant = courant->suivant;
    }*/
}

// Suppression des animaux morts
void nettoyer_ocean(t_ocean* ocean) {
    /*nettoyer_liste(&ocean->poissons, ocean);
    nettoyer_liste(&ocean->requins, ocean);*/
}

// Affichage simplifi� de l'oc�an
void afficher_ocean(const t_ocean* ocean) {
   /* for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            if (ocean->grille[i][j].type == VIDE) {
                printf(".");
            }
            else if (ocean->grille[i][j].type == POISSON) {
                printf("O");
            }
            else if (ocean->grille[i][j].type == REQUIN) {
                printf("X");
            }
        }
        printf("\n");
    }*/
}
