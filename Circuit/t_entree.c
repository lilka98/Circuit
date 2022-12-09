#define _CRT_SECURE_NO_WARNINGS
#include "t_entree.h"

t_entree* t_entree_init(int num)
{
	t_entree* nouv_entree = (t_entree*)malloc(sizeof(t_entree));
	
	if (nouv_entree == NULL)
	{
		EXIT_FAILURE;
	}
	nouv_entree->nom = (char*)malloc(sizeof(NOM_ENTREE_TAILLE_MAX + 1));

	nouv_entree->id = num;
	
	sprintf(nouv_entree->nom, "E%d", num);
	
	nouv_entree->pin = t_pin_sortie_init();

	return nouv_entree;
}

void t_entree_destroy(t_entree* entree)
{
	t_pin_sortie_destroy(entree->pin);
	free(entree->nom);
	free(entree);
}

t_pin_sortie* t_entree_get_pin(t_entree* entree)
{
	return entree->pin;
}

int t_entree_est_reliee(t_entree* entree)
{
	return t_pin_sortie_est_reliee(entree->pin);
}

void t_entree_reset(t_entree* entree)
{
	t_pin_sortie_reset(entree->pin);
}

int t_entree_propager_signal(t_entree* entree)
{
	if (entree->pin->valeur != -1)
	{
		t_pin_sortie_propager_signal(entree->pin);

		return 1;
	}

	else
	{
		return 0;
	}
}

int t_entree_get_valeur(t_entree* entree)
{
	return entree->pin->valeur;
}
