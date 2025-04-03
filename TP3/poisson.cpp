#include "poisson.h"


/******************************************************************************/
/*  POISSON.CPP                                                                 */
/*  Module utilitaire qui permet de maintenir la liste des poissons vivants   */
/*  Conception : Lucas Loge                                                   */
/******************************************************************************/
#if !defined (POISSON_CPP)
#define POISSON_CPP 1


/*
	PAS RANDOM
*/
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
			(ocean[y][x]).animal = ajout_animal(liste_p, y, x, age, ENERGIE_INIT_POISSON, 0);
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
	int se_deplace = 0;
	t_contenu** case_adj = (t_contenu**)malloc( 3 * sizeof(t_contenu*));//creer un tableau 3 rangees qui ont chacune l'espace pour un tableau avec 3 colonnes de taille t_contenu
	for (int k = 0; k < 3; k++)
	{
		case_adj[k] = (t_contenu*)malloc(3 * sizeof(t_contenu));		//creer un tableau de 3 colonnes de taille t_contenu
		case_adj[k] = (case_adj_vides(poisson, ocean))+(3*(t_contenu)k);//assigne les 3 valeurs adj trouvees pour la rangee k au tableau de cases adjacentes
	}
	int bord = case_adj[1][1];
	int tout_est_plein = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i != 1 || j != 1)
				tout_est_plein += case_adj[i][j];
			else
				tout_est_plein++;
		}

	}

	if (tout_est_plein > 8) //Si toutes les cases autour du poisson sont pleines il ne se deplace pas
	{
		return NULL;
	}
	t_direction ou_aller = (t_direction(rand() % 7)); //choisi une direction aleatoire entre 0-7 (HAUT,BAS,DROITE,ect...)
	t_direction temp = (t_direction(rand() % 7));	  //element temporaire qui permet d'eviter de regarder 2 fois la meme direction d'affiler

	while (se_deplace == 0) //cherche une direction valide ou se deplacer
	{
		while(ou_aller == temp)
			ou_aller = (t_direction(rand() % 7));	  //si on essaye de regarder encore la meme direction on change de direction

		switch (ou_aller) //Selon la direction voulue initialise le changement si la case est vide
		{
		case HAUT_G:
		{
			temp = ou_aller;
			if (case_adj[0][0] == VIDE) //Sinon recommence
			{
				(poisson->info->posy)--;
				if (bord == 1)	// Si completement a gauche
					(poisson->info->posx) = LARGEUR - 1;//Place completement a droite
				else  			//Sinon Position normale
					(poisson->info->posx)--;

				se_deplace = 1;
			}
			break;
		}
		case HAUT:
		{
			temp = ou_aller;
			if (case_adj[0][1] == VIDE)
			{
				(poisson->info->posy)--;
				se_deplace = 1;
			}
			break;
		}
		case HAUT_D:
		{
			temp = ou_aller;
			if (case_adj[0][2] == VIDE)
			{
				(poisson->info->posy)--;
				if (bord == 2)	// Si completement a droite
					(poisson->info->posx) = 0;//Place completement a gauche
				else  			//Sinon Position normale
					(poisson->info->posx)++;

				se_deplace = 1;
			}
			break;
		}
		case GAUCHE:
		{
			temp = ou_aller;
			if (case_adj[1][0] == VIDE)
			{
				if (bord == 1)	// Si completement a gauche
					(poisson->info->posx) = LARGEUR - 1;//Place completement a droite
				else
					(poisson->info->posx)--;			//Sinon Position normale
				se_deplace = 1;
			}
			break;
		}
		//pas de case au centre
		case DROITE:
		{
			temp = ou_aller;
			if (case_adj[1][2] == VIDE)
			{
				if (bord == 2)	// Si completement a droite
					(poisson->info->posx) = 0;	//Place completement a gauche
				else
					(poisson->info->posx)++;	//Sinon position normale
				se_deplace = 1;
			}
			break;
		}
		case BAS_G:
		{
			temp = ou_aller;
			if (case_adj[2][0] == VIDE) //Sinon recommence
			{
				(poisson->info->posy)++;
				if (bord == 1)	// Si completement a gauche
					(poisson->info->posx) = LARGEUR - 1;//Place completement a droite
				else  			//Sinon Position normale
					(poisson->info->posx)--;

				se_deplace = 1;
			}
			break;
		}
		case BAS:
		{
			temp = ou_aller;
			if (case_adj[2][1] == VIDE)
			{
				(poisson->info->posy)++;
				se_deplace = 1;
			}
			break;
		}
		case BAS_D:
		{
			temp = ou_aller;
			if (case_adj[2][2] == VIDE)
			{
				(poisson->info->posy)++;
				if (bord == 2)	// Si completement a droite
					(poisson->info->posx) = 0;//Place completement a gauche
				else  			//Sinon Position normale
					(poisson->info->posx)++;

				se_deplace = 1;
			}
			break;
		}
		default:
			break;
		}

	}
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
	t_contenu** case_adj = (t_contenu**)malloc(3 * sizeof(t_contenu*));//creer un tableau 3 rangees qui ont chacune l'espace pour un tableau avec 3 colonnes de taille t_contenu
	for (int k = 0; k < 3; k++)
	{
		case_adj[k] = (t_contenu*)malloc(3 * sizeof(t_contenu));		//creer un tableau de 3 colonnes de taille t_contenu
		case_adj[k] = (case_adj_vides(p_parent, ocean)) + (3 * (t_contenu)k);//assigne les 3 valeurs adj trouvees pour la rangee k au tableau de cases adjacentes
	}
	int bord = case_adj[1][1];
	int tout_est_plein = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i != 1 || j != 1)
				tout_est_plein += case_adj[i][j];
			else
				tout_est_plein++;
		}

	}
	int fx_couche = (rand() % 3);
	if (fx_couche != 1 && tout_est_plein < 8)
	{
		///ICI
	}


}


/*
	Modifie pour que ça retourne une structure avec:
		le tableau de cases adj
		si toutes les cases sont pleines (int 1 ou 0)
		quelle direction à ete selectionnee comme nouvelle position
*/
t_contenu* case_adj_vides(t_noeud* poisson, t_ocean ocean)
{
	int y_min = 0, y_max = 3, bord = 0;
	t_contenu case_adj[3][3] = { POISSON ,POISSON, POISSON,
							     POISSON, POISSON, POISSON,
								 POISSON, POISSON, POISSON };//chaque element peut avoir jusqu'à 8 cases vides adjacentes mais qui sont initialisees commen etant occupees & la case du milieu qui represente le poisson est tjrs occupee
	//int bord = sur_le_bord(poisson);
	if ((poisson->info->posy) == 0)				//si le poisson est a la surface 
	{
		y_min = 1;								//il ne peut pas aller plus haut
	}
	if ((poisson->info->posy) == (HAUTEUR - 1))	//si le poisson est au fond de l'eau
	{
		y_max = 2;								//il ne peut pas aller plus bas
	}
	for (int y = y_min; y < y_max; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (y != 1 || x != 1)													//on exclu la case au centre
			{
				if (((poisson->info->posx) + x - 1) > 0)							//si le poisson est completement a gauche
				{
					(case_adj[y][x]) = get_contenu_case(ocean, LARGEUR - 1, y - 1); //les cases a gauche du poisson sont celles a l'oppose de l'ocean
					bord = 1;
				}
				else if ((poisson->info->posx) + x - 1 < (LARGEUR - 1))				//Sinon si le poisson est completement a droite
				{
					(case_adj[y][x]) = get_contenu_case(ocean, 0, y - 1);			//les cases a droite du poisson sont celles a l'oppose de l'ocean
					bord = 2;
				}
				else																//Sinon
					(case_adj[y][x]) = get_contenu_case(ocean, (poisson->info->posx) + x - 1, (poisson->info->posy) + y - 1);		//on enregistre toutes les cases valides autour du poisson 
			}

		}
	}
	return *case_adj;
}




#endif
