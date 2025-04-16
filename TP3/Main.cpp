#pragma once
/******************************************************************************/
/*  main.cpp                                                                 */
/*  Fichier d'en t�te de l'algorithme   */
/*  Conception : Lucas Loge & Anthony Rosa                      */
/************************/
#include "main.h"


int main(void)
{	
	FILE* fichier_stats = NULL;

	// Déclaration types
	t_stats stats;
	t_ocean* ocean = (t_ocean*)calloc(HAUTEUR_OCEAN,sizeof(t_ocean)); //on initialise 60 rangées à contenu=VIDE & animal=0x000000
	t_liste* liste_requin = init_liste();
	t_liste* liste_poisson = init_liste();
	
	// Déclarations variables
	int mode = MODE_GRAPHIQUE;
	int sortieBoucle = 0;
	int iteration = 0;
	char saisieUtilisateur = '0';

	// Initialisations
	init_alea();
	init_liste_p(liste_poisson, *ocean, NB_POISSON_DEPART);
	init_liste_r(liste_requin, *ocean, NB_REQUIN_DEPART);

	stats.nb_poisson = nb_animaux(liste_poisson);
	stats.nb_requin = nb_animaux(liste_requin);
	stats.temps = 0;

	
	// Init affichage / mode texte
	while(saisieUtilisateur != 'o' || saisieUtilisateur != 'n')
	{
		printf("Voulez-vous avec affichage? (O)ui/(N)on: ");
		scanf("%c", &saisieUtilisateur);

		if(tolower(saisieUtilisateur) == 'o')
		{
			printf("\nMode Graphique selectionne\n");
			mode = MODE_GRAPHIQUE;
			break;
		}else if(tolower(saisieUtilisateur) == 'n')
		{
			printf("\nMode sauvegarde fichier selectionne\n");
			mode = MODE_ECRI_FICH;
			break;
		}
		else 
		{
			system("cls");
			printf("Saisie invalide, veuiller ressayer.\n\n");
		}
	}
	printf("\n");

	if (mode == MODE_GRAPHIQUE)
	{	
		init_graphe(LARGEUR_OCEAN, HAUTEUR_OCEAN);
		init_zone_environnement(HAUTEUR_OCEAN, LARGEUR_OCEAN);
		dessiner_ocean(*ocean);
	}
	else 
	{
		fichier_stats = fopen("stats.dat", "w");
		if (fichier_stats == NULL) 
		{
			perror("\nCréation du fichier echouer!\n");
			return EXIT_FAILURE;
		}
	}


	// Algorithme principale

	while (!sortieBoucle)//On répète la boucle tant qu’il reste des poissons et des requins OU qu’un nombre maximal d’itérations n’est pas atteint(eg. 5000) OU que l’utilisateur n’a pas arrêté la simulation(avec la touche <ESC>)
	{
		algorithme(*ocean, liste_poisson, liste_requin, iteration, mode);

		//enregistre les nouvelles info des listes
		stats.nb_poisson = nb_animaux(liste_poisson);
		stats.nb_requin = nb_animaux(liste_requin);


		if (mode == MODE_GRAPHIQUE)
		{
			if (touche_pesee())
			{
				if (obtenir_touche() == TOUCHE_ESC)
				{
					fermer_mode_graphique();
					printf("\nTouche ESC appuyer, sortie du mode d'affichage graphique.\n");
					sortieBoucle = 1;
				}
			}

			afficher_infos(iteration, nb_animaux(liste_poisson), nb_animaux(liste_requin));

			if (stats.nb_poisson == 0)
			{
				fermer_mode_graphique();
				printf("\nNombre de poisson minimal atteint, sortie du mode d'affichage graphique.\n");
				sortieBoucle = 1;
			}
			if (stats.nb_requin == 0)
			{
				fermer_mode_graphique();
				printf("\nNombre de requin minimal atteint, sortie du mode d'affichage graphique.\n");
				sortieBoucle = 1;
			}

			delai_ecran(100);//delais de 0.1 sec pour observer les elements
		}
		else // Mode fichier texte
		{
			// log t_stats dans fichier .dat
			fprintf(fichier_stats, "%-3d %-4d %-3d\n", stats.temps, stats.nb_poisson, stats.nb_requin);

			if (iteration == MAX_ITER ||stats.nb_poisson == 0 ||stats.nb_requin == 0)
			{
				if (iteration == MAX_ITER) 
				{
					printf("\nNombre d'itération max atteint\n");
				}
				else if (stats.nb_poisson == 0) 
				{
					printf("\nNombre de poisson minimal atteint, sortie du mode d'affichage graphique.\n");
				}
				else
				{
					printf("\nNombre de requin minimal atteint, sortie du mode d'affichage graphique.\n");
				}
				
				fclose(fichier_stats);
				printf("\nStatistiques enregistrer dans stats.dat.\n");
				sortieBoucle = 1;
			}
		}
		
		iteration++;
		stats.temps++;
	}

	free_liste(liste_poisson);
	free_liste(liste_requin);
	free(ocean);

	system("pause");
	return EXIT_SUCCESS;
}


static void algorithme(t_ocean ocean, t_liste* liste_poisson, t_liste* liste_requin, int temps, int mode)
{
	//identifie & supprime les poissons mangées ou trop vieux
	courant_tete_liste(liste_poisson);
	int nbPoissons = nb_animaux(liste_poisson);
	
	for (int i = 0;i < nbPoissons;i++)
	{
		// Se fait manger par un requin
		if (requin_mange(ocean, liste_poisson->courant))
		{
			retirer_poisson(liste_poisson, ocean, mode);
		}
		// Est-ce qu'il meurt de vieilleisse?
		else if (liste_poisson->courant->info->age > MAX_AGE_POISSON) //fonction indicatrice qui supprime les poissons ayant 
		{
			// Oui
			retirer_poisson(liste_poisson, ocean, mode);
		}
		int effacer_contenu(t_ocean ocean, int posx, int posy, int mode);
		prochain_noeud(liste_poisson); //Prochain poisson dans la liste
	}


	//identifie & supprime requins trop vieux ou morts de faim
	courant_tete_liste(liste_requin);
	int nbRequins = nb_animaux(liste_requin);

	for (int j = 0; j < nbRequins; j++)
	{
		if (liste_requin->courant->info->age > MAX_AGE_REQUIN || liste_requin->courant->info->energie_sante <= 0)
		{
			retirer_requin(liste_requin, ocean, mode);
		}
		prochain_noeud(liste_requin);
	}


	// On traite tous les poisson
	courant_tete_liste(liste_poisson);
	nbPoissons = nb_animaux(liste_poisson);

	for (int k = 0;k < nbPoissons;k++)
	{
		if (liste_poisson->courant->info->jrs_gest >= NB_JRS_GEST_POISSON) // Atteint jours de gestation
		{
			ajout_bb_poisson(liste_poisson, ocean, liste_poisson->courant);
		}
		else // Sinon on le déplace
		{
			deplace_poisson(liste_poisson->courant, ocean, mode);

			// Augmente jours de gestation si atteint la puberté
			// Et si le poisson vient pas tout juste d'accoucher 
			if (liste_poisson->courant->info->age >= NB_JRS_PUB_POISSON)
			{
				liste_poisson->courant->info->jrs_gest++;
			}
		}
		
		// Incrémente l'age peut-importe le cas
		liste_poisson->courant->info->age++;

		prochain_noeud(liste_poisson);
	}
	

	//identifie puis deplace ou genere un nouveau requin
	courant_tete_liste(liste_requin);
	nbRequins = nb_animaux(liste_requin);

	for (int k = 0; k < nbRequins; k++)
	{
		if (liste_requin->courant->info->jrs_gest >= NB_JRS_GEST_REQUIN)
		{
			ajout_bb_requin(liste_requin, ocean, liste_requin->courant);
		}
		else
		{
			deplace_requin(liste_requin->courant, ocean, mode);
		}
		if (liste_requin->courant->info->age >= NB_JRS_PUB_REQUIN)
			liste_requin->courant->info->jrs_gest++;

		liste_requin->courant->info->age++; //incremente age peu importe

		prochain_noeud(liste_requin);
	}

}


static int requin_mange(t_ocean ocean, t_noeud* poisson)
{
	void* ptr_temp = NULL;
	t_noeud* requin = NULL; //ptr du requin qui mange 
	int manger = 0;
	
	// Observe dans un carré 9x9 autour du poisson
	for (int dy = -1; dy <= 1; dy++)
	{
		for (int dx = -1; dx <= 1; dx++)
		{
			if (dx != 0 || dy != 0) //toutes les cases sauf celle du milieu qui est tjrs pleine
			{
				int case_wREQUIN_x = (poisson->info->posx + dx + LARGEUR_OCEAN) % LARGEUR_OCEAN;// Évite le débordement en largeur
				int case_wREQUIN_y = poisson->info->posy + dy;

				if (case_wREQUIN_y >= 0 && case_wREQUIN_y < HAUTEUR_OCEAN)				// Évite le débordement en y (poisson ne peut pas voler au dessus de l'océan, et ne peut pas creuser dans le sol)
				{
					if (get_contenu_case(ocean, case_wREQUIN_x, case_wREQUIN_y) == REQUIN)
					{
						requin = (t_noeud*)get_ptrAnimal_case(ocean, case_wREQUIN_x, case_wREQUIN_y, ptr_temp);
						requin->info->energie_sante++;
						manger++;
						break;
					}
				}
			}
		}
	}
	return manger; // 0 se fait pas manger, 1 c'est fait manger.
}


