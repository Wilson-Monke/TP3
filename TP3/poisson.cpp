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
	int nb_p = 0, y = 0, x = 0;
	int age = (rand() % MAX_AGE_POISSON);


	while (nb_p < nb_p_vlu)
	{
		y = (rand() % HAUTEUR);
		x = (rand() % LARGEUR);
		if ((ocean[y][x].contenu) == VIDE)
		{
			age = (rand() % MAX_AGE_POISSON);
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
	ocean[poisson->info->posy][poisson->info->posx].contenu = VIDE; //vide le contenu original
	t_info_adj* info_adj = case_adj_vides(poisson, ocean);	//fonction qui observe les cases autour du poisson et retourne si elles sont pleines
															//cette fonction determine aussi une direction & une case possibles pour un element ainsi on peut directement faire:
	if (info_adj->plein != 1)								//si les cases adj ne sont pas pleines
	{
		poisson->info->posx = info_adj->n_x;				//ecrit les coords de la case disponible
		poisson->info->posy = info_adj->n_y;
	}

	ocean[poisson->info->posy][poisson->info->posx].contenu = POISSON; //met le poisson a sa nouvelle position ou sa position intiale
	return 1;

}

int ajout_bb_p(t_liste* liste, t_ocean ocean, t_noeud* p_parent)
{
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

	t_info_adj* info_adj = case_adj_vides(p_parent, ocean);//fonction qui observe les cases autour du poisson et retourne si elles sont pleines
															//cette fonction determine aussi une direction & une case possibles pour un element ainsi on peut directement faire:
	

	int fx_couche = (rand() % 3);
	/*******************************************
	ATTENTION QUAND ON RUN nb_animaux le pointeur courant est rst
	
	*******************************************/
	if (fx_couche != 1 && info_adj->plein==0 && (nb_animaux(liste))<MAX_POISSON) //2/3 chances de reussite de grossesse & case_adj pas pleines && MAX_POISSON PAS ATTEINT
	{
		ajout_animal(liste, info_adj->n_x, info_adj->n_y, 0, ENERGIE_INIT_POISSON, 0);	//ajoute le nouveau poisson a la fin de la liste
		ocean[info_adj->n_y][info_adj->n_x].contenu = POISSON;							//place le nouveau poisson dans l'ocean
		p_parent->info->energie_sante--;												//decrem energie du poisson_parent
		p_parent->info->jrs_gest = NB_JRS_GEST_POISSON;									//reinit jrs_gest poisson_parent
	}
	else
	{
		p_parent->info->jrs_gest = NB_JRS_GEST_POISSON;
		return NULL;//operation n'a pas fonctionne mais jrs_gest est reinit
	}
	return 1; //operation est completee normalement



}


void retirer_poisson(t_liste* liste, t_ocean ocean) {
	
	ocean[liste->courant->info->posy][liste->courant->info->posx].contenu = VIDE;
	retire_noeud(liste);//fonction qui retire le noeud courant de la liste
}



t_info_adj* case_adj_vides(t_noeud* poisson, t_ocean ocean)
{
	int y_min = 0, y_max = 3;
	t_info_adj* info_adj = (t_info_adj*)calloc(1,sizeof(t_info_adj));
	info_adj->n_y = (poisson->info->posy);
	info_adj->n_x = (poisson->info->posx);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			info_adj->case_adj[i][j] = POISSON;//chaque element peut avoir jusqu'à 8 cases vides adjacentes mais qui sont initialisees commen etant occupees & la case du milieu qui represente le poisson est tjrs occupee
	}

	//int bord = sur_le_bord(poisson);
	if ((poisson->info->posy) == 0)				//si le poisson est a la surface 
	{
		y_min = 1;								//il ne peut pas aller plus haut
		info_adj->bordy = 1;
	}
	else if ((poisson->info->posy) == (HAUTEUR - 1))	//si le poisson est au fond de l'eau
	{
		y_max = 2;								//il ne peut pas aller plus bas
		info_adj->bordy = 2;
	}else
		info_adj->bordy = 0;					//il est normal

	for (int y = y_min; y < y_max; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (y != 1 || x != 1)													//on exclu la case au centre
			{
				if (((poisson->info->posx) + x - 1) < 0)							//si le poisson est completement a gauche
				{
					(info_adj->case_adj[y][x]) = get_contenu_case(ocean, LARGEUR - 1, y - 1); //les cases a gauche du poisson sont celles a l'oppose de l'ocean
					info_adj->bordx = 1;
				}
				else if (((poisson->info->posx) + x - 1) > (LARGEUR - 1))				//Sinon si le poisson est completement a droite
				{
					(info_adj->case_adj[y][x]) = get_contenu_case(ocean, 0, y - 1);			//les cases a droite du poisson sont celles a l'oppose de l'ocean
					info_adj->bordx = 2;
				}
				else
				{//Sinon
					(info_adj->case_adj[y][x]) = get_contenu_case(ocean, (poisson->info->posx) + x - 1, (poisson->info->posy) + y - 1);		//on enregistre toutes les cases valides autour du poisson 
					info_adj->bordx = 0;
				}

			}

		}
	}

	int tout_est_plein = 0;
	for (int k = 0; k < 3; k++)
	{
		for (int l = 0; l < 3; l++)
		{
			if (k != 1 || l != 1)					//toutes les cases sauf celle du milieu qui est tjrs pleine
			{
				if (info_adj->case_adj[k][l] != 0)	//si la case n'est pas vide
					tout_est_plein++;
			}else
				tout_est_plein++;
		}

	}
	if (tout_est_plein > 8) //Si toutes les cases autour du poisson sont pleines il ne se deplace pas
		info_adj->plein = 1;
	else
		info_adj->plein = 0;


	int se_deplace = info_adj->plein;
	info_adj->dir_dispo = (t_direction(rand() % 7)); //choisi une direction aleatoire entre 0-7 (HAUT,BAS,DROITE,ect...)
	t_direction temp = (t_direction(rand() % 7));	  //element temporaire qui permet d'eviter de regarder 2 fois la meme direction d'affiler

	while (se_deplace == 0) //cherche une direction valide ou se deplacer si le poisson se deplace
	{
		while (info_adj->dir_dispo == temp)
			info_adj->dir_dispo = (t_direction(rand() % 7));	  //si on essaye de regarder encore la meme direction on change de direction

		switch (info_adj->dir_dispo) //Selon la direction voulue regarde si elle est valable
		{
			case HAUT_G:
			{
				temp = HAUT_G;
				if (info_adj->case_adj[0][0] == VIDE) //Sinon recommence
				{
					info_adj->n_y--;
					if (info_adj->bordx == 1)	// Si completement a gauche
						info_adj->n_x = LARGEUR - 1;//Place completement a droite
					else  						//Sinon Position normale
						info_adj->n_x--;


					se_deplace = 1;
				}
				break;
			}case HAUT:
			{
				temp = HAUT;
				if (info_adj->case_adj[0][1] == VIDE) //Sinon recommence
				{
					info_adj->n_y--;
					se_deplace = 1;
				}
				break;
			}
			case HAUT_D:
			{
				temp = HAUT_D;
				if (info_adj->case_adj[0][2] == VIDE) //Sinon recommence
				{
					info_adj->n_y--;
					if (info_adj->bordx == 2)	// Si completement a droite
						info_adj->n_x = 0;//Place completement a gauche
					else  						//Sinon Position normale
						info_adj->n_x--;


					se_deplace = 1;
				}
				break;
			}
			case GAUCHE:
			{
				temp = GAUCHE;
				if (info_adj->case_adj[1][0] == VIDE) //Sinon recommence
				{
					if (info_adj->bordx == 1)	// Si completement a gauche
						info_adj->n_x = LARGEUR - 1;//Place completement a droite
					else  						//Sinon Position normale
						info_adj->n_x--;


					se_deplace = 1;
				}
				break;
			}
			case DROITE:
			{
				temp = DROITE;
				if (info_adj->case_adj[1][2] == VIDE) //Sinon recommence
				{
					if (info_adj->bordx == 2)	// Si completement a droite
						info_adj->n_x = 0;//Place completement a gauche
					else  						//Sinon Position normale
						info_adj->n_x--;


					se_deplace = 1;
				}
				break;
			}
			case BAS_G:
			{
				temp = BAS_G;
				if (info_adj->case_adj[2][0] == VIDE) //Sinon recommence
				{
					info_adj->n_y++;
					if (info_adj->bordx == 1)	// Si completement a gauche
						info_adj->n_x = LARGEUR - 1;//Place completement a droite
					else  						//Sinon Position normale
						info_adj->n_x--;


					se_deplace = 1;
				}
				break;
			}
			case BAS:
			{
				temp = BAS;
				if (info_adj->case_adj[2][1] == VIDE) //Sinon recommence
				{
					info_adj->n_y++;
					se_deplace = 1;
				}
				break;
			}
			case BAS_D:
			{
				temp = BAS_D;
				if (info_adj->case_adj[2][2] == VIDE) //Sinon recommence
				{
					info_adj->n_y++;
					if (info_adj->bordx == 2)	// Si completement a droite
						info_adj->n_x = 0;//Place completement a gauche
					else  						//Sinon Position normale
						info_adj->n_x--;


					se_deplace = 1;
				}
				break;
			}
			default:
			{
				se_deplace = 0;
				break;
			}
		}

	}

	return info_adj;
}




#endif
