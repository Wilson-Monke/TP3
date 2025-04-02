#include "ocean.h"


int main()
{
	t_ocean ocean;
	vider_ocean(ocean);
    t_contenu test_contenu;
    int test;

    

    for (int i = 0; i < HAUTEUR; i++) 
    {
        for (int j = 0; j < LARGEUR; j++) 
        {
          /*  printf("ocean[%d][%d] -> contenu: %d, animal: %p\n",
                i, j, ocean[i][j].contenu, ocean[i][j].animal);*/
        }
    }

    ocean[0][0].animal = &test;
    ocean[0][0].contenu = POISSON;

    get_contenu_case(ocean,0,0, &test_contenu);

    switch (test_contenu)
    {
    case      VIDE:   printf("Vide");       break;
    case   POISSON:   printf("POISSON");    break;
    case    REQUIN:   printf("REQUIN");     break;
    default:    break;
    }

    get_ptrAnimal_case(ocean, 0, 0, ());

	return 0;
}