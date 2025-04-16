#pragma once

#define MODE_GRAPHIQUE	1
#define MODE_ECRI_FICH	0
#define MAX_ITER 2000

// Paramètres animaux NOT USED
#define NB_ANIMAUX_VLU	500
#define POURCENTAGE_POISSON 0.8
#define POURCCENTAGE_REQUIN 0.2


// Paramètres POISSON
#define NB_POISSON_DEPART 400
#define MAX_POISSON 1000		//nombre maximal de poissons avant la surpopulation
#define MAX_AGE_POISSON 150		//age maximal du poisson
#define NB_JRS_PUB_POISSON 30	//nombre de jours avant la pubert�
#define NB_JRS_GEST_POISSON 15	//nombre de jours de gestation
#define ENERGIE_INIT_POISSON 3	//valeur initiale d'�nergie
#define MAX_ACCOUCH_POISSON 3		//age maximal du poisson

// Paramètres REQUINS
#define NB_REQUIN_DEPART 80
#define MAX_AGE_REQUIN 1500		//age maximal du requin
#define NB_JRS_PUB_REQUIN 90	//nombre de jours avant la pubert�
#define NB_JRS_GEST_REQUIN 30	//nombre de jours de gestation
#define ENERGIE_DIGESTION 10	//valeur ajout�e � l'indice d��nergie apr�s un repas
#define MAX_JRS_JEUNE 30		//nombre de jours sans manger max