/******************************************************************************/
/*  UTILITAIRE_AFFICHAGE.H                                                    */
/*  Module utilitaire qui permet d'afficher les cases d'une grille en mode    */
/*  graphique avec le module graphique "winBGim.h".                           */
/*                                                                            */
/*  Conception : Pierre Bélisle, Eric Thé                                     */
/******************************************************************************/

#ifndef utilitaire_affichage_h
#define utilitaire_affichage_h  1

#include "winbgim.h"

//Permet de travailler avec une fenêtre graphique de la dimension demandée.
//Reçoit les dimensions de la grille (le nombre de "cases" désirées).
//NOTE: utilisez la fonction "void initwindow(int nb_pixels_X, int nb_pixels_Y);"
void init_graphe(int nb_cases_lignes, int nb_cases_colonnes);

//Permet de dessiner un cadre autour de la zone d'affichage (reçoit les dimensions de la grille)
void init_zone_environnement(int dimy, int dimx);

//Affiche le temps (nb. cycles) et la population de chaque espèce au dessus de la zone d'affichage
void afficher_infos(int temps, int nb_proies, int nb_preds);    

//Affiche une case (un cercle) à la position fournie de la couleur fournie
void afficher_case(int lig, int col, int dimy, int dimx, int couleur); 

//Permet d'effacer la zone d'affichage au complet
void effacer_zone_environnement(int dimy, int dimx);

//Permet de faire une pause de "msec" millisecondes à l'écran
void delai_ecran(int msec);

//Retourne 1 si une touche a été pesée, 0 sinon.
int  touche_pesee();

//Pour récupérer un caractère saisi dans la console graphique.
int  obtenir_touche();

//Va fermer la fenêtre graphique
void fermer_mode_graphique();

#endif
