#pragma once
/******************************************************************************/
/*  main.cpp                                                                 */
/*  Fichier d'en t�te de l'algorithme   */
/*  Conception : Lucas Loge & Anthony Rosa                      */
/************************/
#include "main.h"


int main(void)
{
	init_alea();
	
	t_ocean* ocean = (t_ocean*)calloc(HAUTEUR_OCEAN,sizeof(t_ocean)); //on initialise 60 rangées à contenu=VIDE & animal=0x000000
	t_liste* liste_requin = init_liste();
	t_liste* liste_poisson = init_liste();
	t_stats stats;			//stats durant les iterations
	t_stats stats_init;		//stats initiales

	int mode = MODE_GRAPHIQUE;
	int sortieBoucle = 0;
	int iteration = 0;

	stats_init.nb_poisson = NB_ANIMAUX_VLU * POURCENTAGE_POISSON;
	stats_init.nb_requin = NB_ANIMAUX_VLU * POURCCENTAGE_REQUIN;

	init_liste_p(liste_poisson, *ocean, stats_init.nb_poisson);
	init_liste_r(liste_requin, *ocean, stats_init.nb_requin);

	stats.nb_poisson = nb_animaux(liste_poisson);
	stats.nb_requin = nb_animaux(liste_requin);


	printf("Voulez-vous avec affichage? (O)ui/(N)on");
	/*
	while(mode != MODE_GRAPHIQUE || mode != MODE_ECRI_FICH)
	{
		scanf(%c, &saisieUtilisateur);

		if(to_lower(saisieUtilisateur) == 'o')
		{
			printf("\n Mode Graphique selectionné");
		}else if(to_lower(saisieUtilisateur) == 'n')
		{
			printf("\n Mode Graphique selectionné");
		}
	}
	*/
	printf("\n");


	if (mode == MODE_GRAPHIQUE)
	{	
		init_graphe(LARGEUR_OCEAN, HAUTEUR_OCEAN);
		init_zone_environnement(HAUTEUR_OCEAN, LARGEUR_OCEAN);
		dessiner_ocean(*ocean);
	}

	while (!sortieBoucle || (iteration <= 5000))//On répète la boucle tant qu’il reste des poissons et des requins OU qu’un nombre maximal d’itérations n’est pas atteint(eg. 5000) OU que l’utilisateur n’a pas arrêté la simulation(avec la touche <ESC>)
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
					sortieBoucle;
				}
			}

			afficher_infos(iteration, nb_animaux(liste_poisson), nb_animaux(liste_requin));

			if (stats.nb_poisson == 0)
			{
				fermer_mode_graphique();
				printf("\nNombre de poisson minimal atteint, sortie du mode d'affichage graphique.\n");
				sortieBoucle;
			}
			if (stats.nb_requin == 0)
			{
				fermer_mode_graphique();
				printf("\nNombre de requin minimal atteint, sortie du mode d'affichage graphique.\n");
				sortieBoucle;
			}

			delai_ecran(100);//delais de 0.1 sec pour observer les elements
		}
		/*
		else // Mode fichier texte 
		{
		
<<<<<<< HEAD
			// log from t_stats
=======
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
>>>>>>> parent of a4024c6 (Smol changes)
		}
		
		*/
		iteration++;
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
			retirer_poisson(liste_poisson, ocean);
		}
		// Meurt apres 3eme accouchement?
		else if (liste_poisson->courant->info->nb_accouch >= MAX_ACCOUCH_POISSON) //si nb_accouch = 3 le poisson a deja eu 3 accouchements donc on le supprime
		{
			// Oui
			retirer_poisson(liste_poisson, ocean);
		}
		// Est-ce qu'il meurt de vieilleisse?
		else if (liste_poisson->courant->info->age > MAX_AGE_POISSON) //fonction indicatrice qui supprime les poissons ayant 
		{
			// Oui
			retirer_poisson(liste_poisson, ocean);
		}
		
		prochain_noeud(liste_poisson); //Prochain poisson dans la liste
	}

	//identifie & supprime requins trop vieux ou morts de faim

	courant_tete_liste(liste_requin);
	int nbRequins = nb_animaux(liste_requin);

	for (int j = 0; j < nbRequins; j++)
	{
		if (liste_requin->courant->info->age > MAX_AGE_REQUIN || liste_requin->courant->info->energie_sante <= 0)
		{
			retirer_requin(liste_requin, ocean);
		}
		prochain_noeud(liste_requin);
	}

	// On traite tous les poisson
	courant_tete_liste(liste_poisson);
	nbPoissons = nb_animaux(liste_poisson);

	for (int k = 0;k < nbPoissons;k++)
	{
		if (liste_poisson->courant->info->jrs_gest >= NB_JRS_GEST_POISSON)
		{
			ajout_bb_poisson(liste_poisson, ocean, liste_poisson->courant);
		}
		else
		{
			deplace_poisson(liste_poisson->courant, ocean);
			
		}
		if (liste_poisson->courant->info->age >= NB_JRS_PUB_POISSON) 
		{
			liste_poisson->courant->info->jrs_gest++;
		}
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
			deplace_requin(liste_requin->courant, ocean);
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
				// 
				int case_wREQUIN_x = (poisson->info->posx + dx + LARGEUR_OCEAN) % LARGEUR_OCEAN;
				int case_wREQUIN_y = (poisson->info->posy + dy + HAUTEUR_OCEAN) % HAUTEUR_OCEAN;

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
	return manger; // 0 se fait pas manger, 1 c'est fait manger.
}


