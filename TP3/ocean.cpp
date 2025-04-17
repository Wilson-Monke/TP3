#include "ocean.h"


#define COULEUR_POISSON BLUE
#define COULEUR_REQUIN	RED
#define COULEUR_VIDE BLACK

// Initialisation de l'oc�an
void vider_ocean(t_ocean ocean)
{
	for (int i = 0; i < HAUTEUR_OCEAN; i++) {
		for (int j = 0; j < LARGEUR_OCEAN; j++) {
			ocean[i][j].contenu = VIDE;
			ocean[i][j].animal = NULL;
			ocean[i][j].animal = 0;
		}
	}
}


t_contenu get_contenu_case(t_ocean ocean, int x, int y)
{
	if (x < 0 || x >= LARGEUR_OCEAN || y < 0 || y >= LARGEUR_OCEAN) return VIDE;

	return ocean[y][x].contenu;
}

void* get_ptrAnimal_case(t_ocean ocean, int x, int y, void* ptrAnimal)
{
	if (x < 0 || x >= LARGEUR_OCEAN || y < 0 || y >= LARGEUR_OCEAN) return 0;

	if (ocean[y][x].animal != NULL)
	{
		ptrAnimal = ocean[y][x].animal;
		return ptrAnimal;
	}
	return NULL;
}

int nvx_contenu_ptr(t_ocean ocean, int posx, int posy, void* nv_ptr, t_contenu nv_ctn, int mode)
{
	if (posx < 0 || posx >= LARGEUR_OCEAN || posy < 0 || posy >= LARGEUR_OCEAN) return 0;

	ocean[posy][posx].contenu = nv_ctn;
	ocean[posy][posx].animal = nv_ptr;

	if (mode == MODE_GRAPHIQUE)
	{
		if (nv_ctn == POISSON)
		{
			afficher_case(posy, posx, HAUTEUR_OCEAN, LARGEUR_OCEAN, COULEUR_POISSON);
		}
		else if (nv_ctn == REQUIN)
		{
			afficher_case(posy, posx, HAUTEUR_OCEAN, LARGEUR_OCEAN, COULEUR_REQUIN);
		}
	}
	

	return 1;
}

int effacer_contenu(t_ocean ocean, int posx, int posy, int mode)
{
	ocean[posy][posx].contenu = VIDE;
	ocean[posy][posx].animal = NULL;

	if (mode == MODE_GRAPHIQUE)
	{
		afficher_case(posy, posx, HAUTEUR_OCEAN, LARGEUR_OCEAN, COULEUR_VIDE);
	}

	return 1;
}


static void case_adj_vide(t_ocean ocean, int posx, int posy, t_location_case_vide* vide_positions, int* nb_vide)
{
	int nbCasesVides = 0;

	// Observe dans un carré 3x3 autour de la case de l'animal
	for (int dy = -1; dy <= 1; dy++)
	{
		for (int dx = -1; dx <= 1; dx++)
		{
			if (dx != 0 || dy != 0) //toutes les cases sauf celle du milieu qui est tjrs pleine
			{
				int caseVide_x = (posx + dx + LARGEUR_OCEAN) % LARGEUR_OCEAN;	// Évite le débordement en x (poisson va se retrouver de l'autre côté)
				int caseVide_y = posy + dy;

				if (caseVide_y >= 0 && caseVide_y < HAUTEUR_OCEAN)				// Évite le débordement en y (poisson ne peut pas voler au dessus de l'océan, et ne peut pas creuser dans le sol)
				{
					if (get_contenu_case(ocean, caseVide_x, caseVide_y) == VIDE)
					{
						vide_positions[*nb_vide].posx = caseVide_x;
						vide_positions[*nb_vide].posy = caseVide_y;
						(*nb_vide)++;
					}
				}
			}
		}
	}
}


t_location_case_vide get_rand_case_vide(t_ocean ocean, int posx, int posy)
{
	t_location_case_vide positions_vide[8];
	int nb_vide = 0;
	t_location_case_vide case_rand_vide;
	
	case_adj_vide(ocean, posx, posy, positions_vide, &nb_vide);

	if (nb_vide > 0)
	{
		int index_alea = alea(0, nb_vide);
		case_rand_vide = positions_vide[index_alea];
	}
	else 
	{
		case_rand_vide.invalide = 1;
		case_rand_vide.posx = -1;
		case_rand_vide.posy = -1;
	}

	return case_rand_vide; 
}


void dessiner_ocean(t_ocean ocean)
{
	for (int i = 0;i < HAUTEUR_OCEAN; i++)
	{
		for (int j = 0;j < LARGEUR_OCEAN;j++)
		{
			if (get_contenu_case(ocean, j, i) == POISSON)
			{
				afficher_case(i, j, HAUTEUR_OCEAN, LARGEUR_OCEAN, COULEUR_POISSON);
			}
			else if (get_contenu_case(ocean, j, i) == REQUIN)
			{
				afficher_case(i, j, HAUTEUR_OCEAN, LARGEUR_OCEAN, COULEUR_REQUIN);
			}
		
		}
	}
}
