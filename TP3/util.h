/**********************************************************************/
/* UTIL.H   Librairie de fonctions utilitaires.                       */
/**********************************************************************/
#if !defined UTIL
#define UTIL 1

void init_alea();
/* Fonction pour initialiser le g�n�rateur al�atoire. */

int  alea(int min, int max);
/* Fonction al�atoire qui renvoie un entier inclu entre [min..max]. */

#endif