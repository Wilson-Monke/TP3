#include "ocean.h"

// Initialisation de l'oc�an
void vider_ocean(t_ocean ocean)
{
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            ocean[i][j].contenu = VIDE;
            ocean[i][j].animal = NULL;

            printf("ocean[%d][%d] -> contenu: %d, animal: %p\n",
            i, j, ocean[i][j].contenu, ocean[i][j].animal);
        }
    }
 }


t_contenu get_contenu_case(t_ocean ocean, int x, int y)
{
    if (x < 0 || x >= LARGEUR || y < 0 || y >= LARGEUR) return VIDE;

    return ocean[y][x].contenu;
}

int get_ptrAnimal_case(t_ocean ocean, int x, int y, int ptrAnimal)
{
    if (x < 0 || x >= LARGEUR || y < 0 || y >= LARGEUR) return 0;

    if (ocean[y][x].animal != NULL)
    {
        //(int*)ptrAnimal = ocean[y][x].animal;

        return 1;
    }
}