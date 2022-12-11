/*
Titre: t_circuit
Description: Programme qui implémente les fonctions d'un circuit.

Auteur: Simon Dallaire, Mathieu Parent &  Khalil Medkouri
Date: 2022-12-10
*/
#include <stdio.h>
#include <stdlib.h>
#include "t_circuit.h"

t_circuit* t_circuit_init(void)
{
	t_circuit* nouv_circuit;

	//Allocation d'une memoir de taille t_circuit
	nouv_circuit = (t_circuit*)malloc(sizeof(t_circuit));

	//Si l'allocation ne marche pas fermeture du programme
	if (nouv_circuit == NULL)
	{
		printf("ERREUR ALLOCATION MEMOIRE T_CIRCUIT_INIT !");
		system("pause");
		exit(EXIT_FAILURE);
	}

	//On initialise les portes a 0
	nouv_circuit->nb_portes = 0;
	nouv_circuit->nb_entrees = 0;
	nouv_circuit->nb_sorties = 0;

	return nouv_circuit;// Retourne t_circuit qui vient d'etre initialiser
}

void t_circuit_destroy(t_circuit* circuit)
{
	//Tant que le nb.d'entre > 0 ou le nb.de porte > 0 || le nb.de sortie > 0 en boucle
	while (circuit->nb_entrees > 0 || circuit->nb_portes > 0 || circuit->nb_sorties > 0)
	{
		//Liberation de la memoire des composantes de t_porte
		if (circuit->nb_portes > 0)
		{
			t_porte_destroy(circuit->portes[circuit->nb_portes - 1]);
			circuit->nb_portes--;
		}

		//Liberation de la memoire des composantes t_entree
		if (circuit->nb_entrees > 0)
		{
			t_entree_destroy(circuit->entrees[circuit->nb_entrees - 1]);
			circuit->nb_entrees--;		
		}

		//Liberation de la memoire des composantes t_sortie
		if (circuit->nb_sorties > 0)
		{
			t_sortie_destroy(circuit->sorties[circuit->nb_sorties - 1]);
			circuit->nb_sorties--;
		}
	}
	free(circuit);//Finalement en libere de la memoire le t_circuit
}

t_porte* t_circuit_ajouter_porte(t_circuit* circuit, e_types_portes le_type)
{
	int id; // Identifiant unique pour la porte
	t_porte* nouv_porte; // Cree une nouvelle porte

	//Verification si le maximum de portes n'est pas atteint
	if (circuit->nb_portes < CIRCUIT_MAX_PORTES)
	{
		// Attribution d'un ID unique
		id = circuit->nb_portes == 0 ? 0 : (circuit->nb_portes - 1) + 1;

		//Initialise la nouvelle porte
		nouv_porte = t_porte_init(id, le_type);

		//Enregistre la nouvelle porte dans le circuit
		circuit->portes[nouv_porte->id] = nouv_porte;
		circuit->nb_portes++;
		
		return nouv_porte;// Retour de la porte cree.
	}

	return NULL;//Nb de porte max atteint
}

t_entree* t_circuit_ajouter_entree(t_circuit* circuit)
{
	int id; // Identifiant unique pour l'entree
	t_entree* nouv_entre;

	//Verification si le maximum d'entree n'est pas atteint
	if (circuit->nb_entrees < MAX_ENTREES)
	{
		// Attribution d'un ID unique
		id = circuit->nb_entrees == 0 ? 0 : (circuit->nb_entrees - 1) + 1;

		// Initialisation porte_entree
		nouv_entre = t_entree_init(id);

		// Enregistre la nouvelle entree dans le circuit
		circuit->entrees[nouv_entre->id] = nouv_entre;
		circuit->nb_entrees++;
				
		return nouv_entre;//retourne l'entree cree
	}
	return NULL;//Nb d'entree max atteint
}

t_sortie* t_circuit_ajouter_sortie(t_circuit* circuit)
{
	int id; // Identifiant unique pour la sortie
	t_sortie* nouv_sortie;

	//Verification si le maximum de sortie n'est pas atteint
	if (circuit->nb_sorties < MAX_SORTIES)
	{
		// Attribution d'un ID unique
		id = circuit->nb_sorties == 0 ? 0 : (circuit->nb_sorties - 1) + 1;

		// Initialise la porte sortie
		nouv_sortie = t_sortie_init(id);

		// Enregistre la sortie dans le circuit
		circuit->sorties[nouv_sortie->id] = nouv_sortie;
		circuit->nb_sorties++;
		
		return nouv_sortie;// retourne la sortie cree
	}

	return NULL;//nb de sortie max atteint
}

int t_circuit_est_valide(t_circuit* circuit)
{
	//Verification de chaque porte[x] si elle est reliee a un composant
	for (int ip = 0; ip < circuit->nb_portes; ip++)
	{
		//Si le retour de la fonction == 0 circuit non valide
		if (t_porte_est_reliee(circuit->portes[ip]) == 0)
			return 0;
	}

	//Verification de chaque entree[x] si elle est reliee a un composant
	for (int ie = 0; ie < circuit->nb_entrees; ie++)
	{
		//Si le retour de la fonction == 0 circuit non valide
		if (t_entree_est_reliee(circuit->entrees[ie]) == 0)
			return 0;
	}

	//Verification de chaque sortie[x] si elle est reliee a un composant
	for (int is = 0; is < circuit->nb_sorties; is++)
	{
		//Si le retour de la fonction == 0 circuit non valide
		if (t_sortie_est_reliee(circuit->sorties[is]) == 0)
			return 0;
	}

	return 1;// circuit valide
}

int t_circuit_appliquer_signal(t_circuit* circuit, int signal[], int nb_bits)
{
	//Pas assez de bits pour les entrees
	if (circuit->nb_entrees > nb_bits)
		return 0;// signal non appliquer , erreur

	//En donne la valeur du signal[x] pour chaque pin de l'entree[x]
	for (int i = 0; i < circuit->nb_entrees; i++)
		circuit->entrees[i]->pin->valeur = signal[i];

	return 1;//signal appliquer avec succes
}

void t_circuit_reset(t_circuit* circuit)
{
	//Remise a l'etat initialise de chaque composantes t_entree
	for (int entree = 0; entree < circuit->nb_entrees; entree++)
		t_entree_reset(circuit->entrees[entree]);
	
	//Remise a l'etat initialise de chaque composantes t_sortie
	for (int sortie = 0; sortie < circuit->nb_sorties; sortie++)
		t_sortie_reset(circuit->sorties[sortie]);

	//Remise a l'etat initialise de chaque composantes t_porte
	for (int porte = 0; porte < circuit->nb_portes; porte++)
		t_porte_reset(circuit->portes[porte]);
}

int t_circuit_propager_signal(t_circuit* circuit)
{
	t_file_porte* file;
	t_porte* porte_courante;
	int nb_iterations = 0;// Initialise la variable a zero
	
	//Verification si le circuit est valide
	if (t_circuit_est_valide(circuit))
	{
		//PROPAGER SIGNAL POUR CHAQUE ENTREE
		for (int i = 0; i < circuit->nb_entrees; i++)
			t_entree_propager_signal(circuit->entrees[i]);
			
		//Initialise la file
		file = t_file_porte_initialiser(100);

		//Ajouter à file TOUTES les portes du circuit 
		for (int i = 0; i < circuit->nb_portes; i++)
			t_file_porte_enfiler(file, circuit->portes[i]);

		//Tant que la file de t_porte n'est pas vide et que le nb d'iteration < nb porte en boucle
		while (!t_file_porte_est_vide(file) && (nb_iterations < circuit->nb_portes))
		{
			//Recuperer les donner dans la file et le stock dans porte_courante.
			porte_courante = t_file_porte_defiler(file);
			
			//Si echec pour propager signal en remet dans la file
			if (t_porte_propager_signal(porte_courante) == 0)
				t_file_porte_enfiler(file, porte_courante);

			nb_iterations++;
		}
		return 1;// Circuit correctement propager
	}
	return 0;// Le circuit n'est pas valide
}
