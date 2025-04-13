#include "ocean.h"




#define COULEUR_POISSON BLUE
#define COULEUR_REQUIN	RED
#define COULEUR_VIDE BLACK

// Initialisation de l'oc�an
void vider_ocean(t_ocean ocean)
{
	for (int i = 0; i < HAUTEUR; i++) {
		for (int j = 0; j < LARGEUR; j++) {
			ocean[i][j].contenu = VIDE;
			ocean[i][j].animal = NULL;

			//printf("ocean[%d][%d] -> contenu: %d, animal: %p\n",
			//i, j, ocean[i][j].contenu, ocean[i][j].animal);
		}
	}
}


t_contenu get_contenu_case(t_ocean ocean, int x, int y)
{
	if (x < 0 || x >= LARGEUR || y < 0 || y >= LARGEUR) return VIDE;

	return ocean[y][x].contenu;
}

int get_ptrAnimal_case(t_ocean ocean, int x, int y, void* ptrAnimal)
{
	if (x < 0 || x >= LARGEUR || y < 0 || y >= LARGEUR) return 0;

	if (ocean[y][x].animal != NULL)
	{
		ptrAnimal = ocean[y][x].animal;
		return 1;
	}
	return 0;
}

int nvx_contenu_ptr(t_ocean ocean, int posx, int posy, void* nv_ptr, t_contenu nv_ctn)
{
	if (posx < 0 || posx >= LARGEUR || posy < 0 || posy >= LARGEUR) return 0;

	ocean[posy][posx].contenu = nv_ctn;
	ocean[posy][posx].animal = nv_ptr;
	return 1;
}

int effacer_contenu(t_ocean ocean, int posx, int posy)
{
	ocean[posy][posx].contenu = VIDE;
	ocean[posy][posx].animal = NULL;
	return 1;

}


t_info_adj* case_adj_vides(t_ocean ocean, int posx, int posy)
{
	int y_min = 0, y_max = 3;
	t_info_adj* info_adj = (t_info_adj*)calloc(1, sizeof(t_info_adj));
	info_adj->n_y = (posy);
	info_adj->n_x = (posx);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			info_adj->case_adj[i][j] = POISSON;//chaque element peut avoir jusqu'à 8 cases vides adjacentes mais qui sont initialisees commen etant occupees & la case du milieu qui represente le requin est tjrs occupee
	}

	//int bord = sur_le_bord(requin);
	if ((posy) == 0)				//si le requin est a la surface 
	{
		y_min = 1;								//il ne peut pas aller plus haut
		info_adj->bordy = 1;
	}
	else if ((posx) == (HAUTEUR - 1))	//si le requin est au fond de l'eau
	{
		y_max = 2;								//il ne peut pas aller plus bas
		info_adj->bordy = 2;
	}
	else
		info_adj->bordy = 0;					//il est normal

	for (int y = y_min; y < y_max; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (y != 1 || x != 1)													//on exclu la case au centre
			{
				if (((posx)+x - 1) < 0)							//si le requin est completement a gauche
				{
					(info_adj->case_adj[y][x]) = get_contenu_case(ocean, LARGEUR - 1, y - 1); //les cases a gauche du requin sont celles a l'oppose de l'ocean
					info_adj->bordx = 1;
				}
				else if (((posx)+x - 1) > (LARGEUR - 1))				//Sinon si le requin est completement a droite
				{
					(info_adj->case_adj[y][x]) = get_contenu_case(ocean, 0, y - 1);			//les cases a droite du requin sont celles a l'oppose de l'ocean
					info_adj->bordx = 2;
				}
				else
				{//Sinon
					(info_adj->case_adj[y][x]) = get_contenu_case(ocean, (posx)+x - 1, (posy)+y - 1);		//on enregistre toutes les cases valides autour du requin 
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
			}
			else
				tout_est_plein++;
		}

	}
	if (tout_est_plein > 8) //Si toutes les cases autour du requin sont pleines il ne se deplace pas
		info_adj->plein = 1;
	else
		info_adj->plein = 0;


	int se_deplace = info_adj->plein;
	info_adj->dir_dispo = (t_direction(rand() % 7)); //choisi une direction aleatoire entre 0-7 (HAUT,BAS,DROITE,ect...)
	t_direction temp = (t_direction(rand() % 7));	  //element temporaire qui permet d'eviter de regarder 2 fois la meme direction d'affiler

	while (se_deplace == 0) //cherche une direction valide ou se deplacer si le requin se deplace
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


void dessiner_ocean(t_ocean ocean)
{
	for (int i = 0;i < HAUTEUR; i++)
	{
		for (int j = 0;j < LARGEUR;j++)
		{
			if (get_contenu_case(ocean, j, i) == POISSON)
			{
				afficher_case(i, j, HAUTEUR, LARGEUR, COULEUR_POISSON);
			}
			else if (get_contenu_case(ocean, j, i) == REQUIN)
			{
				afficher_case(i, j, HAUTEUR, LARGEUR, COULEUR_REQUIN);
			}
			else if (get_contenu_case(ocean, j, i) == VIDE)
			{
				afficher_case(i, j, HAUTEUR, LARGEUR, BLACK);
			}
		}
	}
}
