#pragma once


#include "Liste.h"
//#include "animal.cpp"
/******************************************************************************/
/*  LISTE.CPP                                                                 */
/*  Module utilitaire de gestion des listes							          */
/*  Conception : Lucas Logé                                                   */
/******************************************************************************/

#if !defined (LISTE_CPP)
#define LISTE_CPP 1



/*initialise enregistrement de la liste*/
t_liste* init_liste() {
	t_liste* liste = (t_liste*)malloc(sizeof(t_liste));
	if (liste == NULL)
	{
		printf("Erreur alloc memoire");
		return NULL;
	}
	liste->tete = NULL;
	liste->courant = NULL;
	liste->fin = NULL;
	return liste;
}


/*
	créer un nouveau noeud/poisson
*/
t_noeud* creer_animal(int px, int py, int age, int energie, int gest)
{
	t_noeud* nouvel_anim = (t_noeud*)malloc(sizeof(t_noeud));
	nouvel_anim->info = (t_animal*)malloc(sizeof(t_animal));

	if (nouvel_anim == NULL)
	{
		printf("Erreur alloc memoire");
		return NULL;
	}

	init_animal(nouvel_anim->info, px, py, age, energie, gest);
	nouvel_anim->next = NULL;
	return nouvel_anim;
}


/*
	Ajoute un animal à fin la liste
	Retourne le pointeur à cet élément de la liste
*/
t_noeud* ajout_animal(t_liste* liste, int px, int py, int age, int energie, int gest)
{
	t_noeud* nouveau = creer_animal(px, py, age, energie, gest);

	if (liste == NULL)
	{
		printf("Erreur liste invalide");
		return NULL;
	}
	if (nouveau == NULL)
	{
		printf("Erreur alloc memoire");
		return NULL;
	}

	if (liste->tete == NULL) // Si la liste est vide 
	{
		liste->tete = nouveau; //envoie l'adresse du nouveau noeud en tête de liste
		liste->fin = nouveau;  // lors de l'attribution du premier noeud la tete est aussi la fin
	}
	else					 // Sinon
	{
		liste->fin->next = nouveau; // envoie l'adresse du nouveau comme prochain noeud de l'ancien dernier noeud de la liste
		liste->fin = nouveau;		// & envoie l'adresse du nouveau comme noeud de fin de la liste
	}
	return nouveau;
}



void courant_tete_liste(t_liste* liste)
{
	if (liste == NULL)
	{
		printf("Erreur liste invalide");
	}
	liste->courant = liste->tete;
}


int nb_animaux(t_liste* liste)
{
	t_noeud* temp = liste->courant;
	if (liste == NULL)
	{
		printf("Erreur liste invalide");
		return NULL;
	}
	int nb_a = 1;
	courant_tete_liste(liste);
	while (liste->courant->next != NULL) //parcoure la liste jùsqu'à la fin-1 donc on commence à compter à 1 & il y a tjrs au moins 1 élément dans la liste
	{
		nb_a++;
		liste->courant = liste->courant->next;
	}
	liste->courant = temp;
	return nb_a;
}


int prochain_noeud(t_liste* liste)
{
	if (liste == NULL)
	{
		printf("Erreur liste invalide");
		return NULL;
	}
	else if(liste->courant->next == NULL)
	{
		//printf("Fin de la liste");
		return NULL;
	}
	else 
	{
		liste->courant = liste->courant->next;
	}
	
	return 1;
}

t_animal* info_noeud(t_liste* liste)
{
	if (liste == NULL)
	{
		printf("Erreur liste invalide");
		return NULL;
	}
	return liste->courant->info;
}

t_animal* retire_noeud(t_liste* liste)
{
	if (liste == NULL)
	{
		printf("Erreur liste invalide");
		return NULL;
	}
	t_noeud* temp = liste->courant;

	if (temp != liste->tete)
	{
		courant_tete_liste(liste);
		while (liste->courant->next != temp) //parcour la liste jusqu'à trouver le noeud précédent celui qu'on veut retirer
		{
			liste->courant = liste->courant->next;
		}
		liste->courant->next = temp->next; //une fois trouvé remplace le pointeur vers le noeud à retirer par celui du noeud suivant celui rétiré
	}
	else
	{
		liste->tete = liste->tete->next; //si le noeud que l'on souhaite retirer est la tete de liste on modifie simplement la liste pour commencer au prochain noeud
	}


	return (temp->info);
}


int free_liste(t_liste* liste)
{
	if (liste == NULL)
	{
		printf("Erreur liste invalide");
		return NULL;
	}

	t_noeud* temp;
	courant_tete_liste(liste);
	while (liste->courant->next != NULL) //parcour la liste jusqu'à la fin
	{
		temp = liste->courant;
		liste->courant = liste->courant->next;
		free(temp->info);
		free(temp);
	}
	free(liste->fin->info);
	free(liste->fin);
	free(liste);

	return 1;
}




#endif

