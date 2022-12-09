#define _CRT_SECURE_NO_WARNINGS
#include "t_porte.h"

t_porte* t_porte_init(int id, e_types_portes type)
{
	t_porte* nouv_porte;

	nouv_porte = (t_porte*)malloc(sizeof(t_porte));

	if (nouv_porte == NULL)
	{
		printf("ERREUR ALLOCATION MEMOIRE T_PORTE_INIT");
		system("pause");
		exit(EXIT_FAILURE);
	}

	nouv_porte->nom = (char*)malloc(sizeof(NOM_PORTE_TAILLE_MAX + 1));
	nouv_porte->id = id;

	sprintf(nouv_porte->nom, "P%d", id);
	nouv_porte->type = type;
	if(type==PORTE_NOT)
	{
		nouv_porte->nb_entrees = 1;
		nouv_porte->entrees[0] = t_pin_entree_init();
	}

	else
	{
		nouv_porte->nb_entrees = 2;
		for (int i = 0; i < nouv_porte->nb_entrees; i++)
		{
			nouv_porte->entrees[i] = t_pin_entree_init();
		}
	}
	nouv_porte->sortie = t_pin_sortie_init();

	return nouv_porte;
}

void t_porte_destroy(t_porte* porte)
{
	free(porte->nom);
	free(porte);
}

void t_porte_calculer_sorties(t_porte* porte)
{
	
	switch (porte->type) 
	{
	case PORTE_ET:
		//Et
		
		t_pin_sortie_set_valeur(porte->sortie,(porte->entrees[0]->valeur) & (porte->entrees[1]->valeur));
		break;
	case PORTE_OU:
		//OU
	
		t_pin_sortie_set_valeur(porte->sortie,(porte->entrees[0]->valeur) | (porte->entrees[1]->valeur));
		break;
	case PORTE_NOT:
		//NOT
		
		if (porte->entrees[0]->valeur == 0) 
		{
			t_pin_sortie_set_valeur(porte->sortie, 1);
		}
		else 
		{
			t_pin_sortie_set_valeur(porte->sortie, 0);
		}
		break;
	case PORTE_XOR:
		//XOR
		
		t_pin_sortie_set_valeur(porte->sortie,(porte->entrees[0]->valeur) ^ (porte->entrees[1]->valeur));
		break;
	}
	
	
}

int t_porte_relier(t_porte* dest, int num_entree, const t_pin_sortie* source)
{
	
	/* Si l'indice de la pin a reliee est superieur au nombre d'entrees possedees par la
	porte. */
	if (num_entree <= dest->nb_entrees)
	{
		
		/* On relie les pins en utilisant la fonction t_pin_entree_relier. */
		t_pin_entree_relier(dest->entrees[num_entree-1], source);
		
		/* On retourne la valeur 1. */
		
		return 1;
	}

	/* Sinon */
	else
	{
		
		/* On retourne la valeur 0. */
		return 0;
	}
}

int t_porte_est_reliee(t_porte* porte)
{
	int test = 1;		/* Entier servant a memoriser le resultat du test. */
	int entree = 0;		/* Compteur servant a memoriser l'indice de l'entree testee. */

	/* Fait */
	do
	{
		/* Si l'entre testee n'est pas reliee. */
		if (t_pin_entree_est_reliee(porte->entrees[entree]) == 0)
		{
			/* On attribue la valeur 0 a la variable test. */
			test = 0;
		}
		/* On incremente le compteur entree. */
		entree++;
		/* Tant que la variable test est egale a 1 et que la valeur du compteur entree est
		inferieure au nombre d'entrees possedees par la porte. */
	} while (test == 1 && entree < porte->nb_entrees);

	/* Si la sortie de la porte n'est pas reliee. */
	if (t_pin_sortie_est_reliee(porte->sortie) == 0)
	{
		/* On attribue la valeur 0 a la variable test. */
		test = 0;
	}
	/* On retourne la valeur de la variable test. */
	return test;
}

void t_porte_reset(t_porte* porte)
{
	for (int i = 0; i < porte->nb_entrees; i++)
	{
		/* On reinitialise la valeur de la pin entree. */
		t_pin_entree_reset(porte->entrees[i]);
	}
	/* On reinitialise la valeur de la pin sorie. */
	t_pin_sortie_reset(porte->sortie);
}

int t_porte_propager_signal(t_porte* porte)
{
	
	if (t_porte_est_reliee(porte))
	{
		
		t_porte_calculer_sorties(porte);

		
		t_pin_sortie_propager_signal(porte->sortie);
		return 1;
	}
	else 
	{
		printf("La porte %s n'est pas complétement relié\n", porte->nom);
		return 0;
	}
}

t_pin_sortie* t_porte_get_pin_sortie(t_porte* porte)
{
    return porte->sortie;
}
