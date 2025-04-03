/**********************************************************************/
/* UTIL.H   Librairie de fonctions utilitaires.                       */
/**********************************************************************/
#if !defined UTIL
#define UTIL 1

void init_alea();
/* Fonction pour initialiser le générateur aléatoire. */

int  alea(int min, int max);
/* Fonction aléatoire qui renvoie un entier inclu entre [min..max]. */

#endif