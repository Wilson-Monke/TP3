#include "poisson.h"


/******************************************************************************/
/*  POISSON.CPP                                                                 */
/*  Module utilitaire qui permet de maintenir la liste des poissons vivants   */
/*  Conception : Lucas Loge                                                   */
/******************************************************************************/
#if !defined (POISSON_CPP)
#define POISSON_CPP 1


void init_liste_p(t_liste* liste_p,t_ocean ocean, int nb_p_vlu)
{
	init_alea();
	int nb_p = 0, y = 0, x = 0;
	int age = alea(0,MAX_AGE_POISSON);


	while (nb_p < nb_p_vlu)
	{
		y = alea(0, HAUTEUR_OCEAN - 1);
		x = alea(0, LARGEUR_OCEAN - 1);
		if ((ocean[y][x].contenu) == VIDE)
		{
			age = alea(0,MAX_AGE_POISSON);
			(ocean[y][x]).animal = ajout_animal(liste_p, x, y, age, ENERGIE_INIT_POISSON, 0);
			(ocean[y][x]).contenu = POISSON;
			nb_p++;
		}

	}
}

int deplace_poisson(t_noeud* poisson,t_ocean ocean)
{
	int posxActuelle = poisson->info->posx;
	int posyActuelle = poisson->info->posy;

	if (poisson == NULL)
	{
		printf("Erreur animal invalide");
		return NULL;
	}

	t_location_case_vide nouvelle_case = get_rand_case_vide(ocean, posxActuelle, posyActuelle);
	
	if (nouvelle_case.invalide != 1)
	{
		// Déplace le poisson à la nouvelle case
		nvx_contenu_ptr(ocean, nouvelle_case.posx, nouvelle_case.posy, poisson, POISSON);

		//Modifier les infos du poisson
		poisson->info->posx = nouvelle_case.posx;
		poisson->info->posy = nouvelle_case.posy;

		// Efface le poisson de l'ancienne case
		effacer_contenu(ocean, posxActuelle, posyActuelle);
	}
	
	return 1;
}

int ajout_bb_poisson(t_liste* liste, t_ocean ocean, t_noeud* p_parent)
{
	int posxActuelle = p_parent->info->posx;
	int posyActuelle = p_parent->info->posy;

	if (liste == NULL)
	{
		printf("Erreur liste invalide");
		return NULL;
	}
	if (p_parent == NULL)
	{
		printf("Erreur animal invalide");
		return NULL;
	}

	t_location_case_vide nouvelle_case = get_rand_case_vide(ocean, posxActuelle, posyActuelle);

	int fx_couche = alea(0,2);

	if (nouvelle_case.invalide != 1 && fx_couche != 1 && (nb_animaux(liste))<MAX_POISSON) //2/3 chances de reussite de grossesse &$ case_adj pas pleines && MAX_POISSON PAS ATTEINT
	{
		ocean[nouvelle_case.posy][nouvelle_case.posx].animal = ajout_animal(liste, nouvelle_case.posx, nouvelle_case.posy, 0, ENERGIE_INIT_POISSON, 0);	//ajoute le nouveau poisson a la fin de la liste
		ocean[nouvelle_case.posy][nouvelle_case.posx].contenu = POISSON;							//place le nouveau poisson dans l'ocean
		p_parent->info->energie_sante--;												//decrem energie du poisson_parent
		p_parent->info->jrs_gest = -(NB_JRS_GEST_POISSON);									//reinit jrs_gest poisson_parent
	}
	else
	{
		p_parent->info->jrs_gest = -(NB_JRS_GEST_POISSON);
		return NULL;//operation n'a pas fonctionne mais jrs_gest est reinit
	}
	

	return 1; //operation est completee normalement
}


void retirer_poisson(t_liste* liste, t_ocean ocean) {

	effacer_contenu(ocean, liste->courant->info->posx, liste->courant->info->posy);
	retire_noeud(liste);
}


#endif
