/*
SIMULATEUR DE CIRCUIT LOGIQUE

Programme qui illustre l'utilisation de la librairie de circuits logique.

Un circuit est construit de façon programmatique (les portes, les entrées, les sorties sont créées et
ajoutées au circuit, puis reliées entre-elles. Une fois construit, on vérifie si il est valide. Si il est
valide, un sigal est appliqué aux entrées et propagé à travers les circuit. Nous terminons par afficher 
le signal en sortie. 
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include "t_circuit.h"
#include "t_porte.h"
#include "t_entree.h"
#include "t_sortie.h"
#include <math.h>



int main(void)
{
	int choix_option;
	int choix_porte;
	int choix_lien;
	int choix_lien_entree;
	int choix_lien_sortie=0;
	int choix_destination;
	int choix_lien_porte_entree;
	t_circuit* circuit;
	int* signal;
	int* compteur;

	circuit = t_circuit_init();
	do {
		printf("***** CIRCUITS LOGIQUES *****\n\n1. Ajouter une entree\n2. Ajouter une porte\n3. Ajouter une sortie\n4. Ajouter un lien\n5. Verifier la validite du circuit\n6. Calculer la table de vÚrite du circuit\n7. Sauvegarder le circuit\n8. Charger un circuit\n0. Quitter\n>");

		scanf("%i", &choix_option);

		
		switch (choix_option) 
		{
		case 1:
			t_circuit_ajouter_entree(circuit);
			printf("L'entree de circuit %s a bien ete ajoutee.\n", circuit->entrees[(circuit->nb_entrees - 1)]->nom);
			system("pause");
			break;
		case 2:
			printf("\n*** Choisissez le type de porte: ***\n[1] Porte ET\n[2] Porte OU\n[3] Porte NOT\n[4] Porte XOR\n>");

			scanf("%i", &choix_porte);

			switch (choix_porte) 
			{
			case 1:
				//Ajout porte ET
				t_circuit_ajouter_porte(circuit, PORTE_ET);
				break;
			case 2:
				//Ajout porte OU
				t_circuit_ajouter_porte(circuit, PORTE_OU);
				break;
			case 3:
				//Ajout porte NOT
				t_circuit_ajouter_porte(circuit, PORTE_NOT);
				break;
			case 4:
				//Ajout porte XOR
				t_circuit_ajouter_porte(circuit, PORTE_XOR);
				break;
			default:
				printf("Choix Invalide. Recommencez.\n");
				break;
			}
			printf("La porte %s a bien ete ajoutee.\n", circuit->portes[(circuit->nb_portes - 1)]->nom);
			system("pause");
			break;
		case 3:
			t_circuit_ajouter_sortie(circuit);
			printf("La sortie de circuit %s a bien ete ajoutee.\n", circuit->sorties[(circuit->nb_sorties - 1)]->nom);
			system("pause");
			break;
		case 4:
			printf("*** Source du lien ****\n1. Entree\n2. Porte\n>");

			scanf("%i", &choix_lien);

			switch (choix_lien)
			{
			case 1:
				if (circuit->nb_entrees == 0)
				{
					printf("Aucune entree!\n");
				}
				else
				{
					printf("*** Choix de l'entree ****\n");
					for (int i = 0; i < circuit->nb_entrees; i++)
					{
						printf("[%d] %s\n", i + 1, circuit->entrees[i]->nom);
					}
					printf(">");
					scanf("%i", &choix_lien_entree);

				}
				break;
			case 2:
				if (circuit->nb_portes == 0)
				{
					printf("Aucune porte!");
				}
				else
				{
					printf("*** Choix de la porte ****\n");
					for (int i = 0; i < circuit->nb_portes; i++)
					{
						printf("[%d] %s ", i + 1, circuit->portes[i]->nom);
						switch (circuit->portes[i]->type)
						{
						case 0:
							printf("(Porte ET)\n");
							break;
						case 1:
							printf("(Porte OU)\n");
							break;
						case 2:
							printf("(Porte NOT)\n");
							break;
						case 3:
							printf("(Porte XOR)\n");
							break;
						}
					}

					printf(">");
					scanf("%i", &choix_lien_entree);
				}
				break;
			default:
				printf("Choix Invalide. Recommencez.\n");
				system("pause");
				break;
			}
			//break;
			
			
			
			printf("*** Destination du lien ****\n1. Sortie\n2. Porte\n>");
			scanf("%i", &choix_destination);

			switch (choix_destination)
			{
			case 1:
				if (circuit->nb_sorties == 0)
					printf("Aucune sortie!");
				else
				{
					printf("*** Choix de la sortie ****\n");
					for (int i = 0; i < circuit->nb_sorties; i++)
					{
						printf("[%d] %s\n", i + 1, circuit->sorties[i]->nom);
					}
					printf(">");
					scanf("%i", &choix_lien_sortie);


				}
				if (choix_lien == 1)
					t_sortie_relier(circuit->sorties[choix_lien_sortie - 1], t_entree_get_pin(circuit->entrees[choix_lien_entree - 1]));
				if (choix_lien == 2)
				{
					t_sortie_relier(circuit->sorties[choix_lien_sortie - 1], circuit->portes[choix_lien_entree - 1]->sortie);
				}
				printf("Le lien a bien ete ajoute\n");
				system("pause");
				break;
			case 2:
				if (circuit->nb_portes == 0)
					printf("Aucune porte!");
				else
				{
					printf("*** Choix de la porte ****\n");
					for (int i = 0; i < circuit->nb_portes; i++)
					{
						printf("[%d] %s ", i + 1, circuit->portes[i]->nom);
						switch (circuit->portes[i]->type)
						{
						case 0:
							printf("(Porte ET)\n");
							break;
						case 1:
							printf("(Porte OU)\n");
							break;
						case 2:
							printf("(Porte NOT)\n");
							break;
						case 3:
							printf("(Porte XOR)\n");
							break;
						}
					}
					printf(">");
					scanf("%i", &choix_lien_sortie);
					
					
					if (circuit->portes[choix_lien_sortie - 1]->type != 2)
					{
						printf("*** Choix de l'entree de la porte ****\nChoisissez une valeur entre 1 et 2:");
						scanf("%i", &choix_lien_porte_entree);
					}
					else
						choix_lien_porte_entree = 1;

					if (choix_lien == 1)
					{

						t_porte_relier(circuit->portes[choix_lien_sortie - 1], choix_lien_porte_entree, t_entree_get_pin(circuit->entrees[choix_lien_entree - 1]));
					}
					if (choix_lien == 2)
					{
						t_porte_relier(circuit->portes[choix_lien_sortie - 1], choix_lien_porte_entree, circuit->portes[choix_lien_entree - 1]->sortie);
					}
					
					
					printf("Le lien a bien ete ajoute\n");
					system("pause");
				}
				break;
				
			}
			break;
		case 5:
			
			if (!t_circuit_est_valide(circuit)) 
			{
				for (int i = 0; i < circuit->nb_entrees; i++) 
				{
					if (!t_entree_est_reliee(circuit->entrees[i]))
						printf("L'entree E%d n'est pas reliee.\n",i);
				}

				for (int i = 0; i < circuit->nb_sorties; i++) 
				{
					if (!t_sortie_est_reliee(circuit->sorties[i]))
						printf("La sortie S%d n'est pas reliee.\n", i);
				}

				for (int i = 0; i < circuit->nb_portes; i++)
				{
					if (!t_porte_est_reliee(circuit->portes[i]))
						printf("La porte P%d n'est pas reliee.\n", i);
				}
				printf("*** Le circuit est invalide!\n");

			}
			else 
			{
				printf("*** Le circuit est valide!\n");
			}
			system("pause");
			break;
		case 6:
			if (t_circuit_est_valide(circuit) == 0) 
			{
				printf("***Le circuit n'est pas valide!");
				
			}
			else
			{
				signal = (int*)malloc(sizeof(int) * circuit->nb_entrees);
				compteur = (int*)malloc(sizeof(int) * circuit->nb_entrees);//Test avec compteur
				if (signal == NULL)
				{
					EXIT_FAILURE;
				}
				if (compteur == NULL)
				{
					EXIT_FAILURE;
				}

				for (int i = 0; i < pow(2, circuit->nb_entrees); i++)
				{
					for (int y = 0; y < circuit->nb_entrees; y++)
					{
						if (i == 0)
						{
							signal[y] = 0;
						}

						else if (y == 0)
						{

							if (signal[y] == 0)
								signal[y] = 1;
							else
								signal[y] = 0;
						}

						else if (i % (int)(pow(2, y)) == 0)
						{
							if (signal[y] == 0)
								signal[y] = 1;
							else
								signal[y] = 0;
						}
						else
						{
							if (signal[y] == 0)
								signal[y] = 0;
							else
								signal[y] = 1;
						}


						printf("%d ", signal[y]);
					}
					t_circuit_appliquer_signal(circuit, signal, circuit->nb_entrees);
					t_circuit_propager_signal(circuit);
					printf("--> ");
					for (int y = 0; y < circuit->nb_sorties; y++)
					{
						printf("%d ", t_sortie_get_valeur(circuit->sorties[y]));
					}
					printf("\n");

				}

				
			}

			system("pause");
			break;
		default:
			printf("Choix Invalide. Recommencez.\n");
			system("pause");
			break;

		}
			
		
			
				
		
	system("cls");
	} while (choix_option != 0);
	

	
	return EXIT_SUCCESS;
}
