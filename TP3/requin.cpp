#pragma once

#include "requin.h"


/******************************************************************************/
/*  REQUIN.CPP                                                                 */
/*  Module utilitaire qui permet de maintenir la liste des requins vivants   */
/*  Conception : Lucas Loge                                                   */
/******************************************************************************/
#if !defined (REQUIN_CPP)
#define REQUIN_CPP 1


void init_liste_r(t_liste* liste_r, t_ocean ocean, int nb_r_vlu)
{

	init_alea();
	int nb_r = 0, y = 0, x = 0;
	int age = alea(0, MAX_AGE_REQUIN);
	int energie = alea(1, ENERGIE_DIGESTION * 2);
	int gest = alea(1, (NB_JRS_GEST_REQUIN));


	while (nb_r < nb_r_vlu)
	{
		y = alea(0, HAUTEUR_OCEAN - 1);
		x = alea(0, LARGEUR_OCEAN - 1);
		if ((ocean[y][x].contenu) == VIDE)
		{
			age = alea(0, MAX_AGE_REQUIN);
			energie = alea(1, ENERGIE_DIGESTION * 2);
			if (age >= NB_JRS_PUB_REQUIN)
				gest = alea(1, (NB_JRS_GEST_REQUIN));
			else
				gest = 0;

			(ocean[y][x]).animal = ajout_animal(liste_r, x, y, age, energie, gest);
			(ocean[y][x]).contenu = REQUIN;
			nb_r++;
		}

	}
}


int deplace_requin(t_noeud* requin, t_ocean ocean)
{
	int posxActuelle = requin->info->posx;
	int posyActuelle = requin->info->posy;

	if (requin == NULL)
	{
		printf("Erreur animal invalide");
		return NULL;
	}

	t_location_case_vide nouvelle_case = get_rand_case_vide(ocean, posxActuelle, posyActuelle);

	if (nouvelle_case.invalide != 1)
	{
		// Déplace le requin à la nouvelle case
		nvx_contenu_ptr(ocean, nouvelle_case.posx, nouvelle_case.posy, requin, REQUIN);
		printf("\n\nPoisson ajouté dans une nouvelle case[%i][%i]\n", nouvelle_case.posy, nouvelle_case.posx);
		print_poissons(ocean);
		//Modifier les infos du requin
		requin->info->posx = nouvelle_case.posx;
		requin->info->posy = nouvelle_case.posy;

		// Efface le requin de l'ancienne case
		effacer_contenu(ocean, posxActuelle, posyActuelle);
		printf("\n\nPoisson deleter [%i][%i]\n", posyActuelle, posxActuelle);
		print_poissons(ocean);
	}

	return 1;
}

int ajout_bb_requin(t_liste* liste, t_ocean ocean, t_noeud* r_parent)
{
	int posxActuelle = r_parent->info->posx;
	int posyActuelle = r_parent->info->posy;

	if (liste == NULL)
	{
		printf("Erreur liste invalide");
		return NULL;
	}
	if (r_parent == NULL)
	{
		printf("Erreur animal invalide");
		return NULL;
	}

	t_location_case_vide nouvelle_case = get_rand_case_vide(ocean, posxActuelle, posyActuelle);


	if (nouvelle_case.invalide != 1) // si case_adj pas pleines 
	{
		ocean[nouvelle_case.posy][nouvelle_case.posx].animal = ajout_animal(liste, nouvelle_case.posx, nouvelle_case.posy, 0, ENERGIE_DIGESTION, 0);	//ajoute le nouveau requin a la fin de la liste
		ocean[nouvelle_case.posy][nouvelle_case.posx].contenu = REQUIN;							//place le nouveau requin dans l'ocean
		r_parent->info->energie_sante--;												//decrem energie du requin_parent
		r_parent->info->jrs_gest = -(NB_JRS_GEST_REQUIN);									//reinit jrs_gest requin_parent
	}
	else
	{
		r_parent->info->jrs_gest = -(NB_JRS_GEST_REQUIN);
		return NULL;//operation n'a pas fonctionne mais jrs_gest est reinit
	}


	return 1; //operation est completee normalement
}

void retirer_requin(t_liste* liste, t_ocean ocean) {

	effacer_contenu(ocean, liste->courant->info->posx, liste->courant->info->posy);
	retire_noeud(liste);
}



#endif
