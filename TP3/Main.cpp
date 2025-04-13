#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
/******************************************************************************/
/*  main.h                                                                 */
/*  Fichier d'en t�te de l'algorithme   */
/*  Conception : Lucas Loge & Anthony Rosa                                              */
/************************/


/*---------------------------------------------------------------------------------------------------*/
/*											CONSTANTES												 */
/*---------------------------------------------------------------------------------------------------*/
// Entr�e utilisateur
#define MODE_AFFICHAGE	'o'
#define MODE_ECRI_FICH	'N'
#define TOUCHE_ESC		27
#define NB_ANIMAUX_VLU	300	

// Couleurs
#define COULEUR_ROUGE       12
#define COULEUR_VERT		10
#define COULEUR_VIOLET		13
#define COULEUR_DEFAUT      7   //BLANC

int main(void)
{
	init_alea();
	char saisieUtilisateur = '0';
	int mode = 0;
	t_ocean* ocean = (t_ocean*)calloc(LARGEUR * HAUTEUR, sizeof(t_ocean));
	t_liste* liste_requin = init_liste();
	t_liste* liste_poisson = init_liste();
	

	printf("Voulez-vous avec affichage? (O)ui/(N)on	");
	mode = 1;
	//scanf("%c", &saisieUtilisateur);
	
	//switch (saisieUtilisateur)
	//{
	//case MODE_AFFICHAGE:
	//	mode = 1;
	//	break;

	//case MODE_ECRI_FICH:
	//	mode = 2;
	//	break;

	//default:
	//	mode = NULL;
	//	break;
	//}

	if (mode == 1)
	{
		int nb_p = (NB_ANIMAUX_VLU * 0.8), nb_r = (NB_ANIMAUX_VLU * 0.2);
		int iteration = 0;
		//vider structures de donnees????????????
		init_liste_p(liste_poisson, *ocean, nb_p);
		afficher_liste(liste_poisson);
		init_liste_r(liste_requin, *ocean, nb_r);
		init_graphe(LARGEUR, HAUTEUR);
		init_zone_environnement(HAUTEUR, LARGEUR);
		while (saisieUtilisateur != TOUCHE_ESC) // Tant qu'on ne p�se pas <ESC>
		{
			if (_kbhit())  // Si une touche est press�e
			{
				if (_kbhit())  // Si une touche est press�e
				{
					saisieUtilisateur = _getch(); // Obtenir la touche	
				}
			}
			dessiner_ocean(*ocean);
			afficher_infos(iteration, nb_animaux(liste_poisson), nb_animaux(liste_requin));
			algorithme(*ocean, liste_poisson, liste_requin, iteration, mode);
			delai_ecran(1000);//delais de 0.1 sec pour observer les elements
			iteration++;
		}
		free_liste(liste_poisson);
		free_liste(liste_requin);
		free(ocean);
	}
}


void algorithme(t_ocean ocean, t_liste* liste_poisson, t_liste* liste_requin, int temps, int mode)
{
	//identifie & supprime les poissons manges ou trop vieux
	checklist(ocean, liste_poisson);
	courant_tete_liste(liste_poisson);

	for (int i = 0;i < nb_animaux(liste_poisson);i++) 
	{
		if (se_fait_manger(ocean, liste_poisson->courant))
		{
			requin_mange(ocean, liste_poisson->courant);
			retirer_poisson(liste_poisson, ocean);
		}
		else if (liste_poisson->courant->info->age > MAX_AGE_POISSON)
		{
			retirer_poisson(liste_poisson, ocean);
		}

		prochain_noeud(liste_poisson);
	}
	checklist(ocean, liste_poisson);



	//identifie & supprime requins trop vieux ou morts de faim
	checklist(ocean, liste_requin);
	courant_tete_liste(liste_requin);
	for (int j = 0;j < nb_animaux(liste_requin);j++) 
	{
		if (liste_requin->courant->info->age > MAX_AGE_REQUIN || liste_requin->courant->info->age <= 0)
		{
			retirer_requin(liste_requin, ocean);
		}
		prochain_noeud(liste_requin);
	}
	checklist(ocean, liste_requin);


	//identifie puis deplace ou genere un nouveau poisson
	checklist(ocean, liste_poisson);
	t_info_adj* info_adj_p = NULL;
	courant_tete_liste(liste_poisson);

	int nb_poisson = nb_animaux(liste_poisson);
	for (int k = 0;k < nb_poisson;k++)
	{
		info_adj_p = case_adj_vides(ocean, liste_poisson->courant->info->posx, liste_poisson->courant->info->posy);
		if (info_adj_p->plein == 0)
		{
			if (liste_poisson->courant->info->jrs_gest >= NB_JRS_GEST_POISSON)
			{
				ajout_bb_p(liste_poisson, ocean, liste_poisson->courant);
				checklist(ocean, liste_poisson);
			}
			else
			{
				deplace_poisson(liste_poisson->courant, ocean);
				//afficher_liste(liste_poisson);
				checklist(ocean, liste_poisson);
			}
			if (liste_poisson->courant->info->age >= NB_JRS_PUB_POISSON)
				liste_poisson->courant->info->jrs_gest++;

			liste_poisson->courant->info->age++;

		}
		prochain_noeud(liste_poisson);
	}
	checklist(ocean, liste_poisson);



	//identifie puis deplace ou genere un nouveau requin
	checklist(ocean, liste_requin);

	t_info_adj* info_adj_r = NULL;
	courant_tete_liste(liste_requin);
	for (int k = 0;k < nb_animaux(liste_requin);k++) 
	{
		info_adj_r = case_adj_vides(ocean, liste_requin->courant->info->posx, liste_requin->courant->info->posy);
		if (info_adj_r->plein == 0)
		{
			if (liste_requin->courant->info->jrs_gest >= NB_JRS_GEST_REQUIN)
			{
				ajout_bb_r(liste_requin, ocean, liste_requin->courant);
			}
			else
			{
				deplace_requin(liste_requin->courant, ocean);
			}
			if (liste_requin->courant->info->age >= NB_JRS_PUB_POISSON)
				liste_requin->courant->info->jrs_gest++;

			liste_requin->courant->info->age++;

		}
		prochain_noeud(liste_requin);
	}

}


int se_fait_manger(t_ocean ocean, t_noeud* poisson)
{
	t_info_adj* info_adj = case_adj_vides(ocean, poisson->info->posx, poisson->info->posy);
	int manger = 0;//0 si pas de requin adj 1 si requin adj
	for (int i = 0;i < 2;i++)
	{
		for (int j = 0;j < 2;j++)
		{
			if (i != 1 && j != 1) //ne regarde jamais la case du milieu
			{
				if (info_adj->case_adj[i][j] == REQUIN)//si il y a un requin adj
				{
					manger = 1; //se fait manger
					break;
				}
			}
		}
	}
	if (manger != 1)
		manger = 0;

	return manger;
}



void requin_mange(t_ocean ocean, t_noeud* poisson)
{
	t_info_adj* info_adj = case_adj_vides(ocean, poisson->info->posx, poisson->info->posy);//poisson qui se fait manger
	int pos_x_r = poisson->info->posx, pos_y_r = poisson->info->posy;
	t_noeud* requin = NULL; //ptr du requin qui mange
	for (int i = 0;i < 2;i++)
	{
		for (int j = 0;j < 2;j++)
		{
			if (i != 1 && j != 1) //ne regarde jamais la case du milieu
			{
				if (info_adj->case_adj[i][j] == REQUIN) //si il y a un requin adj
				{
					pos_y_r += (i - 1);
					pos_x_r += (j - 1);
					break;
				}
			}
		}
	}

	requin = (t_noeud*)ocean[pos_y_r][pos_x_r].animal;
	requin->info->energie_sante++;

}

void checklist(t_ocean ocean, t_liste* liste)
{

	/*courant_tete_liste(liste);
	void* ptr_animal = NULL;

	while (liste->courant->next != NULL)
	{
		if (liste->courant != ocean[liste->courant->info->posy][liste->courant->info->posx].animal)
		{
			printf("ERREUR");
		}
		prochain_noeud(liste);
	}*/

}

void afficher_liste(t_liste* liste) {
	if (!liste || !liste->tete) {
		printf("Liste vide ou invalide.\n");
		return;
	}

	t_noeud* courant = liste->tete;
	int index = 0;

	while (courant != NULL) {
		if (courant->info != NULL) {
			printf("Noeud %d: Pos=(%d,%d), Age=%d, Energie=%d, Gestation=%d\n",
				index,
				courant->info->posx,
				courant->info->posy,
				courant->info->age,
				courant->info->energie_sante,
				courant->info->jrs_gest);
		}
		else {
			printf("Noeud %d: info == NULL\n", index);
		}

		courant = courant->next;
		index++;
	}

	printf("Fin de la liste (%d éléments).\n\n\n", index);
}




/*
	Tests requin.h


int main()
{
	srand(NULL);
	int px = 1, py = 2, age = 33, energie = 3, gest = 3, nb_p_vlu = 250;
	t_liste* liste_requin = init_liste();
	t_ocean* ocean = (t_ocean*)calloc(LARGEUR * HAUTEUR, sizeof(t_ocean));
	init_liste_r(liste_requin, *ocean, nb_p_vlu);
	printf("%d", nb_animaux(liste_requin));
	courant_tete_liste(liste_requin);
	deplace_requin(liste_requin->courant,*ocean);
	deplace_requin(liste_requin->courant, *ocean);
	deplace_requin(liste_requin->courant, *ocean);
	ajout_bb_r(liste_requin, *ocean, liste_requin->courant);
	retirer_requin(liste_requin, *ocean);
	deplace_requin(liste_requin->fin, *ocean);


	return 0;
}
*/