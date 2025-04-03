#include "poisson.h"


int main()
{
    srand(NULL);
    int px = 1, py = 2, age = 33, energie = 3, gest = 3, nb_p_vlu = 250;
    t_liste* liste_poisson = init_liste();
    t_ocean* ocean = (t_ocean*)calloc(LARGEUR * HAUTEUR, sizeof(t_ocean));
    init_liste_p(liste_poisson, *ocean, nb_p_vlu);

    printf("%d", nb_animaux(liste_poisson));
    deplace_poisson(ajout_animal(liste_poisson, 25, 0, age, energie, gest),*ocean);


	return 0;
}