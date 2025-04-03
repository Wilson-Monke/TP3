/**********************************************************************/
/* UTIL.CPP   Librairie de fonctions utilitaires.                     */
/**********************************************************************/

#include"util.h"
#include<stdlib.h>
#include<time.h>

/**********************************************************************/
/* Générer une valeur aléatoire entière.                              */
/**********************************************************************/

/* Fonction pour initialiser le générateur aléatoire. */
void init_alea(){
  srand(time(NULL));
}

/* Fonction aléatoire qui renvoie un entier inclu entre [min..max]. */
int  alea(int min, int max){
  return (int)((1.0 * rand()) / (RAND_MAX + 1) * (max-min+1)) + min;
}



