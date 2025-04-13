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
		y = alea(0, HAUTEUR - 1);
		x = alea(0, LARGEUR - 1);
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
	if (requin == NULL)
	{
		printf("Erreur animal invalide");
		return NULL;
	}
	effacer_contenu(ocean, requin->info->posx, requin->info->posy);
	t_info_adj* info_adj = case_adj_vides(ocean, requin->info->posx, requin->info->posy);	//fonction qui observe les cases autour du requin et retourne si elles sont pleines
	//cette fonction determine aussi une direction & une case possibles pour un element ainsi on peut directement faire:
	if (info_adj->plein != 1)								//si les cases adj ne sont pas pleines
	{
		requin->info->posx = info_adj->n_x;				//ecrit les coords de la case disponible
		requin->info->posy = info_adj->n_y;
	}

	ocean[requin->info->posy][requin->info->posx].contenu = REQUIN; //met le requin a sa nouvelle position ou sa position intiale
	ocean[requin->info->posy][requin->info->posx].animal = requin;
	return 1;

}

int ajout_bb_r(t_liste* liste, t_ocean ocean, t_noeud* r_parent)
{
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

	t_info_adj* info_adj = case_adj_vides(ocean, r_parent->info->posx, r_parent->info->posy);//fonction qui observe les cases autour du requin et retourne si elles sont pleines
	//cette fonction determine aussi une direction & une case possibles pour un element ainsi on peut directement faire:


	if (info_adj->plein == 0) //case_adj pas pleines 
	{
		ocean[info_adj->n_y][info_adj->n_x].animal = ajout_animal(liste, info_adj->n_x, info_adj->n_y, 0, ENERGIE_DIGESTION, 0);		//ajoute le nouveau requin a la fin de la liste
		ocean[info_adj->n_y][info_adj->n_x].contenu = REQUIN;							//place le nouveau requin dans l'ocean
		r_parent->info->energie_sante--;												//decrem energie du requin_parent
		r_parent->info->jrs_gest = (NB_JRS_GEST_REQUIN);									//reinit jrs_gest requin_parent
	}
	else
	{
		r_parent->info->jrs_gest = (NB_JRS_GEST_REQUIN);									//reinit jrs_gest requin_parent
		return NULL;//operation n'a pas fonctionne
	}
	return 1; //operation est completee normalement



}


void retirer_requin(t_liste* liste, t_ocean ocean) {

	effacer_contenu(ocean, liste->courant->info->posx, liste->courant->info->posy);
	retire_noeud(liste);//fonction qui retire le noeud courant de la liste
}



#endif
