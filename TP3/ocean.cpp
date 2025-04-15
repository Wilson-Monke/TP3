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

int get_ptrAnimal_case(t_ocean ocean, int x, int y, void* ptrAnimal)
{
	if (x < 0 || x >= LARGEUR_OCEAN || y < 0 || y >= LARGEUR_OCEAN) return 0;

	if (ocean[y][x].animal != NULL)
	{
		ptrAnimal = ocean[y][x].animal;
		return 1;
	}
	return 0;
}

int nvx_contenu_ptr(t_ocean ocean, int posx, int posy, void* nv_ptr, t_contenu nv_ctn)
{
	if (posx < 0 || posx >= LARGEUR_OCEAN || posy < 0 || posy >= LARGEUR_OCEAN) return 0;

	ocean[posy][posx].contenu = nv_ctn;
	ocean[posy][posx].animal = nv_ptr;

	if (nv_ctn == POISSON)
	{
		afficher_case(posy, posx, HAUTEUR_OCEAN, LARGEUR_OCEAN, COULEUR_POISSON);
	}
	else if (nv_ctn == REQUIN)
	{
		afficher_case(posy, posx, HAUTEUR_OCEAN, LARGEUR_OCEAN, COULEUR_REQUIN);
	}

	return 1;
}

int effacer_contenu(t_ocean ocean, int posx, int posy)
{
	ocean[posy][posx].contenu = VIDE;
	ocean[posy][posx].animal = NULL;

	afficher_case(posy, posx, HAUTEUR_OCEAN, LARGEUR_OCEAN, COULEUR_VIDE); 

	return 1;

}

static int nb_case_adj_vide(t_ocean ocean, int posx, int posy)
{
	int nbCasesVides = 0;

	// Itère dans un carré 9x9
	for (int dy = -1; dy <= 1; dy++)
	{
		for (int dx = -1; dx <= 1; dx++)
		{
			if (dx != 0 || dy != 0) //toutes les cases sauf celle du milieu qui est tjrs pleine
			{
				// 
				int caseVide_x = (posx + dx + LARGEUR_OCEAN) % LARGEUR_OCEAN;
				int caseVide_y = (posy + dy + HAUTEUR_OCEAN) % HAUTEUR_OCEAN;

				if (get_contenu_case(ocean, caseVide_x, caseVide_y) == VIDE)
				{
					nbCasesVides++;
				}
			}
		}
	}

	return nbCasesVides;
}


t_location_case_vide get_rand_case_vide(t_ocean ocean, int posx, int posy)
{
	int nbCaseVide = nb_case_adj_vide(ocean, posx, posy);
	int caseChoisi = alea(0, nbCaseVide);
	int iteration = 0;
	t_location_case_vide case_vide;
	case_vide.invalide = 1;

	if (nbCaseVide != 0) 
	{
		// Itère dans un carré 9x9
		for (int dy = -1; dy <= 1; dy++)
		{
			for (int dx = -1; dx <= 1; dx++)
			{
				if (dx != 0 || dy != 0) //toutes les cases sauf celle du milieu qui est tjrs pleine
				{
					int caseVide_x = (posx + dx + LARGEUR_OCEAN) % LARGEUR_OCEAN;
					int caseVide_y = (posy + dy + HAUTEUR_OCEAN) % HAUTEUR_OCEAN;

					if (get_contenu_case(ocean, caseVide_x, caseVide_y) == VIDE && caseChoisi == iteration)
					{
						case_vide.posx = caseVide_x;
						case_vide.posy = caseVide_y;
						case_vide.invalide = 0;

						return case_vide;
					}
					else
					{
						iteration++;
					}
				}
			}
		}
	}

	return case_vide;
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



void print_ocean(t_ocean ocean) 
{
	for (int y = 0; y < HAUTEUR_OCEAN; y++) {
		for (int x = 0; x < LARGEUR_OCEAN; x++) {
			// Get type as string
			const char* contenu_str;
			switch (ocean[y][x].contenu) {
			case VIDE:    contenu_str = "VIDE"; break;
			case POISSON: contenu_str = "POISSON"; break;
			case REQUIN:  contenu_str = "REQUIN"; break;
			default:      contenu_str = "INCONNU"; break;
			}

			// Print content and pointer address
			printf("Case [%d][%d] : contenu = %s, animal = %p\n",
				y, x, contenu_str, ocean[y][x].animal);
		}
	}
}

void print_poissons(t_ocean ocean) {
	for (int y = 0; y < HAUTEUR_OCEAN; y++) {
		for (int x = 0; x < LARGEUR_OCEAN; x++) {
			if (ocean[y][x].contenu == POISSON) {
				printf("POISSON at [%d][%d] : animal = %p\n",
					y, x, ocean[y][x].animal);
			}
		}
	}
}