#define _CRT_SECURE_NO_WARNINGS
#include "t_sortie.h"

t_sortie* t_sortie_init(int num)
{
	t_sortie* nouv_sortie = (t_sortie*)malloc(sizeof(t_sortie));

	if (nouv_sortie == NULL)
	{
		EXIT_FAILURE;
	}

	nouv_sortie->nom = (char*)malloc(sizeof(NOM_SORTIE_TAILLE_MAX + 1));

	nouv_sortie->id = num;
	sprintf(nouv_sortie->nom, "S%d", num);
	nouv_sortie->pin = t_pin_entree_init();

	return nouv_sortie;
}

void t_sortie_destroy(t_sortie* sortie)
{
	t_pin_entree_destroy(sortie->pin);
	free(sortie->nom);
	free(sortie);
}

t_pin_entree* t_sortie_get_pin(t_sortie* sortie)
{
	return sortie->pin;
}

int t_sortie_relier(t_sortie* dest, const t_pin_sortie* source)
{
	if (t_pin_entree_est_reliee(dest->pin))
	{
		t_pin_entree_reset(dest->pin);
	}
	t_pin_entree_relier(dest->pin, source);
	if (t_pin_entree_est_reliee(dest->pin)) {
		return 1;
	}
	else
	{
		return 0;
	}
}

int t_sortie_est_reliee(t_sortie* sortie)
{
	if (t_pin_entree_est_reliee(sortie->pin))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void t_sortie_reset(t_sortie* sortie)
{
	t_pin_entree_reset(sortie->pin);
}

int t_sortie_get_valeur(t_sortie* sortie)
{
	return sortie->pin->valeur;
}
