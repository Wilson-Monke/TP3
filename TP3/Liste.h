#pragma once

#include "animal.h"
/***********************************/
/******************************************************************************/
/*  LISTE.H                                                                   */
/*  Module utilitaire qui permet de gérer les listes poisson/requin           */
/*  Conception : Lucas Logé                                                   */
/******************************************************************************/

#if !defined (LIB_LISTE)
#define LIB_LISTE 1


/* type-structure pour un noeud-animal */
typedef struct noeud {
	t_animal* info;
	struct noeud* next;

}t_noeud;

/* structure d'enregistrement de la liste*/
typedef struct liste {
	t_noeud* tete;
	t_noeud* courant;
	t_noeud* fin;

}t_liste;




/*
	Structure speciale pour transmettre les informations autour d'un poisson & la direction disponible choisie
*/


/*initialise la liste de poissons*/
t_liste* init_liste();

/*
	créer un nouveau noeud/poisson
*/
t_noeud* creer_animal(int px, int py, int age, int energie, int gest);

/*
	Ajoute un animal à fin la liste
	Retourne le pointeur de cet élément de la liste
*/
t_noeud* ajout_animal(t_liste* liste, int px, int py, int age, int energie, int gest);

/*
	Retourne le nb d'animaux dans la liste
*/
int nb_animaux(t_liste* liste);

/*
	Placer le pointeur courant au début de la liste
*/
void courant_tete_liste(t_liste* liste);

/*
	Déplacer le pointeur courant au prochain élément de la liste
	Retourne 1 si opération fonctionne, retourne 0 si il n'y a pas de prochain élément (dernier noeud)
*/
int prochain_noeud(t_liste* liste);

/*
	Obtenir le contenu du pointeur courant
	Retourne le pointeur du noeud attribué à cet animal
*/
t_animal* info_noeud(t_liste* liste);

/*
	Retire le noeud au pointeur courant
	Le pointeur du nouveau noeud courant (noeud parent) doit ensuite pointer sur l'élément qui suit celui retiré
	Retourne une copie de l'animal retiré //pour l'instant retourne le pointeur du noeud de l'animal retiré
*/
t_animal* retire_noeud(t_liste* liste);

/*
	Vide la liste au complet et détruit tout les noeuds
	Retourne 1 si l'opération est complétée sinon retourne 0
*/
int free_liste(t_liste* liste);



#endif