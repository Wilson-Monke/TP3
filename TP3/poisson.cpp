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
	 
	if (poisson == NULL)
	{
		printf("Erreur animal invalide");
		return NULL;
	}

	t_case temp = get_rand_case_vide(ocean, poisson->info->posx, poisson->info->posy);
	
	if (temp.invalide != 1) 
	{
		// Déplace le poisson à la nouvelle case
		nvx_contenu_ptr(ocean, poisson->info->posx, poisson->info->posy, temp);

		// Efface le poisson de l'ancienne case
		effacer_contenu(ocean, poisson->info->posx, poisson->info->posy);
	}
	
	return 1;
}

int ajout_bb_p(t_liste* liste, t_ocean ocean, t_noeud* p_parent)
{
	/*
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

	t_info_adj* info_adj = case_adj_vides(ocean, p_parent->info->posx, p_parent->info->posy);//fonction qui observe les cases autour du poisson et retourne si elles sont pleines
															//cette fonction determine aussi une direction & une case possibles pour un element ainsi on peut directement faire:

	int fx_couche = alea(0,2);

	if (info_adj->plein == 0/*fx_couche != 1 && info_adj->plein == 0 && (nb_animaux(liste))<MAX_POISSON) //2/3 chances de reussite de grossesse &$ case_adj pas pleines && MAX_POISSON PAS ATTEINT
	{
		ocean[info_adj->n_y][info_adj->n_x].animal = ajout_animal(liste, info_adj->n_x, info_adj->n_y, 0, ENERGIE_INIT_POISSON, 0);	//ajoute le nouveau poisson a la fin de la liste
		ocean[info_adj->n_y][info_adj->n_x].contenu = POISSON;							//place le nouveau poisson dans l'ocean
		p_parent->info->energie_sante--;												//decrem energie du poisson_parent
		p_parent->info->jrs_gest = (NB_JRS_GEST_POISSON);									//reinit jrs_gest poisson_parent
	}
	else
	{
		p_parent->info->jrs_gest = (NB_JRS_GEST_POISSON);
		return NULL;//operation n'a pas fonctionne mais jrs_gest est reinit
	}
	

	*/
	return 1; //operation est completee normalement
}


void retirer_poisson(t_liste* liste, t_ocean ocean) {

	effacer_contenu(ocean, liste->courant->info->posx, liste->courant->info->posy);
	retire_noeud(liste);
}


#endif
