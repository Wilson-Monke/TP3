#include "poisson.h"



/*
    Tests poisson.h



int main()
{
    srand(NULL);
    int px = 1, py = 2, age = 33, energie = 3, gest = 3, nb_p_vlu = 250;
    t_liste* liste_poisson = init_liste();
    t_ocean* ocean = (t_ocean*)calloc(LARGEUR * HAUTEUR, sizeof(t_ocean));
    init_liste_p(liste_poisson, *ocean, nb_p_vlu);
    printf("%d", nb_animaux(liste_poisson));
    courant_tete_liste(liste_poisson);
    deplace_poisson(liste_poisson->courant,*ocean);
    deplace_poisson(liste_poisson->courant, *ocean);
    deplace_poisson(liste_poisson->courant, *ocean); 
    ajout_bb_p(liste_poisson, *ocean, liste_poisson->courant); 
    retirer_poisson(liste_poisson, *ocean);
    deplace_poisson(liste_poisson->fin, *ocean);


	return 0;
}
*/