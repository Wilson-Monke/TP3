#pragma once


#include "animal.h"

/******************************************************************************/
/*  ANIMAL.CPP                                                                */
/*  fonctions pour gérer un élément de  type "t_animal"						  */
/*  Conception : Lucas Logé                                                   */
/******************************************************************************/
#if !defined (ANIMAL_CPP)
#define ANIMAL_CPP 1


/* Reçoit un animal et ses valeurs initiales, va initialiser l'animal reçu.  */
void init_animal(t_animal* animal, int px, int py, int age, int energie, int gest)
{
	animal->posx = px;
	animal->posy = py;
	animal->age = age;
	animal->energie_sante = energie;
	animal->jrs_gest = gest;
}


/* Reçoit un animal et retourne sa position via [*px, *py]. */
void get_position(const t_animal* animal, int* px, int* py)
{
	*px = animal->posx;
	*py = animal->posy;

}

/* Reçoit un animal et une position et va inscrire cette position à l'animal. */
void set_position(t_animal* animal, int px, int py)
{
	animal->posx = px;
	animal->posy = py;
}

/* Reçoit un animal et retourne 1 si le poisson a attient l'age de
   puberté ET a terminé sa période de gestation (donc, il va procréer),
   retourne 0 sinon. */
int  puberte_atteinte(const t_animal* animal, int puberte, int gestation)
{
	if ((animal->age >= puberte) && (animal->jrs_gest >= gestation))
		return 1;
	else
		return 0;
}

/* Reçoit un animal et va incrémenter son age ainsi que le nombre de jours
   en gestation de +1 jour si il est assez vieux pour procréer. */
void inc_age(t_animal* animal, int puberte)
{
	(animal->age)++;
	if (animal->age >= puberte)
		(animal->jrs_gest)++;

}

/* Reçoit un animal et va réinitialiser les jours de gestation à "val".  */
void reset_gestation(t_animal* animal, int val)
{
	animal->jrs_gest = val;

}

/* Reçoit un animal et va incrémenter son niveau d'énergie de la valeur reçue.  */
void ajout_energie(t_animal* animal, int energie)
{
	animal->energie_sante += energie;
}

/* Reçoit un animal et va décrémenter son niveau d'énergie de -1.  */
void dec_energie(t_animal* animal)
{
	(animal->energie_sante)--;
}

/* Reçoit un animal et va retourner son niveau d'énergie.  */
int  get_energie(t_animal* animal)
{
	return animal->energie_sante;
}

/* Retourne 1 si l'animal reçu vient de mourir de faim (plus d'énergie)
   OU si il a atteint son âge maximal (age_max). On retourne 0 sinon.  */
int  est_mort(const t_animal* animal, int age_max)
{
	if ((animal->energie_sante <= 0) || (animal->age >= age_max))
		return 1;
	else
		return 0;
}

#endif
