#pragma once


#include "animal.h"

/******************************************************************************/
/*  ANIMAL.CPP                                                                */
/*  fonctions pour g�rer un �l�ment de  type "t_animal"						  */
/*  Conception : Lucas Log�                                                   */
/******************************************************************************/
#if !defined (ANIMAL_CPP)
#define ANIMAL_CPP 1


/* Re�oit un animal et ses valeurs initiales, va initialiser l'animal re�u.  */
void init_animal(t_animal* animal, int px, int py, int age, int energie, int gest)
{
	animal->posx = px;
	animal->posy = py;
	animal->age = age;
	animal->energie_sante = energie;
	animal->jrs_gest = gest;
}


/* Re�oit un animal et retourne sa position via [*px, *py]. */
void get_position(const t_animal* animal, int* px, int* py)
{
	*px = animal->posx;
	*py = animal->posy;

}

/* Re�oit un animal et une position et va inscrire cette position � l'animal. */
void set_position(t_animal* animal, int px, int py)
{
	animal->posx = px;
	animal->posy = py;
}

/* Re�oit un animal et retourne 1 si le poisson a attient l'age de
   pubert� ET a termin� sa p�riode de gestation (donc, il va procr�er),
   retourne 0 sinon. */
int  puberte_atteinte(const t_animal* animal, int puberte, int gestation)
{
	if ((animal->age >= puberte) && (animal->jrs_gest >= gestation))
		return 1;
	else
		return 0;
}

/* Re�oit un animal et va incr�menter son age ainsi que le nombre de jours
   en gestation de +1 jour si il est assez vieux pour procr�er. */
void inc_age(t_animal* animal, int puberte)
{
	(animal->age)++;
	if (animal->age >= puberte)
		(animal->jrs_gest)++;

}

/* Re�oit un animal et va r�initialiser les jours de gestation � "val".  */
void reset_gestation(t_animal* animal, int val)
{
	animal->jrs_gest = val;

}

/* Re�oit un animal et va incr�menter son niveau d'�nergie de la valeur re�ue.  */
void ajout_energie(t_animal* animal, int energie)
{
	animal->energie_sante += energie;
}

/* Re�oit un animal et va d�cr�menter son niveau d'�nergie de -1.  */
void dec_energie(t_animal* animal)
{
	(animal->energie_sante)--;
}

/* Re�oit un animal et va retourner son niveau d'�nergie.  */
int  get_energie(t_animal* animal)
{
	return animal->energie_sante;
}

/* Retourne 1 si l'animal re�u vient de mourir de faim (plus d'�nergie)
   OU si il a atteint son �ge maximal (age_max). On retourne 0 sinon.  */
int  est_mort(const t_animal* animal, int age_max)
{
	if ((animal->energie_sante <= 0) || (animal->age >= age_max))
		return 1;
	else
		return 0;
}

#endif
