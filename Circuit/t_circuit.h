/*
Module: T_CIRCUIT
Description: D�finit le type circuit et fournit les fonctions pour manipuler un circuit.
Auteur: Anis Boubaker
Derni�re modification: 2018-03-19
*/


#ifndef CIRCUIT_H_
#define CIRCUIT_H_


#define MAX_ENTREES 50 //Nombre maximal d'entr�es que peut contenir le circuit
#define MAX_SORTIES 50 //Nombre maximal de sorties que peut contenir le circuit
#define CIRCUIT_MAX_PORTES 100 //Nombre maximal de portes que peut contenir le circuit

#include "t_entree.h"
#include "t_porte.h"
#include "t_file_porte.h"
#include "t_sortie.h"


typedef struct t_entree t_entree; 
typedef struct t_porte t_porte;
typedef struct t_file_porte t_file_porte;
typedef struct t_sortie t_sortie;
typedef enum e_types_portes e_types_portes;


/*
D�finit le type t_circuit qui permet de stocker l'information relative � un circuit. 
*/
struct t_circuit {
	//Tableu statique qui stocke des pointeurs vers les entr�es incluses dans le circuit
	t_entree *entrees[MAX_ENTREES]; 
	//Tableu statique qui stocke des pointeurs vers les sorties incluses dans le circuit
	t_sortie *sorties[MAX_SORTIES]; 
	//Tableu statique qui stocke des pointeurs vers les portes incluses dans le circuit
	t_porte *portes[CIRCUIT_MAX_PORTES]; 
	//Nombre d'entr�es dans le tableau d'entr�es du circuit
	int nb_entrees;
	//Nombre de sorties dans le tableau de sorties du circuit
	int nb_sorties; 
	//Nombre de portes dans le tableau de portes du circuit
	int nb_portes;
};

typedef struct t_circuit t_circuit;

/*
Fonction: T_CIRCUIT_INIT
Description: Cr�e un nouveau circuit vide. 
Param�tres: Aucun
Retour: Pointeur vers le circuit cr��
Param�tres modifi�: Aucun.
*/
t_circuit* t_circuit_init(void);

/*
Fonction: T_CIRCUIT_DESTROY
Description: Lib�re la m�moire occup�e par le circuit et tous ses composants.
Param�tres: 
- circuit: Pointeur vers le circuit � d�truire. 
Retour: Aucun.
Param�tres modifi�: circuit
*/
void t_circuit_destroy(t_circuit *circuit);

/*
Fonction: T_CIRCUIT_AJOUTER_PORTE
Description: Cr�e une nouvelle porte et l'ajoute au circuit. 
NDE: 
- Il faut s'assurer qu'on ne d�passe pas le nombre de portes permis (CIRCUIT_MAX_PORTES).
- Il faut s'assurer que la porte aura un identifiant unique parmi les portes du circuit.
Param�tres:
- circuit: Pointeur vers le circuit auquel la porte sera ajout�e
- type: Type de la porte cr��e parmi les types de portes pr�d�finis (e_type_porte, c.f. t_porte.h)
Retour: Pointeur vers la nouvelle porte cr��e s'il a �t� possible de la cr�er. NULL sinon.
*/
t_porte* t_circuit_ajouter_porte(t_circuit *circuit, e_types_portes le_type);

/*
Fonction: T_CIRCUIT_AJOUTER_ENTREE
Description: Cr�e une nouvelle entr�e de circuit et l'ajoute au circuit.
NDE:
- Il faut s'assurer qu'on ne d�passe pas le nombre d'entr�es permis (MAX_ENTREES).
- Il faut s'assurer que l'entr�e aura un identifiant unique parmi les entr�es du circuit.
Param�tres:
- circuit: Pointeur vers le circuit auquel l'entr�e sera ajout�e
Retour: Pointeur vers l'entr�e cr��e s'il a �t� possible de la cr�er. NULL sinon.
*/
t_entree* t_circuit_ajouter_entree(t_circuit * circuit);

/*
Fonction: T_CIRCUIT_AJOUTER_SORTIE
Description: Cr�e une nouvelle sortie de circuit et l'ajoute au circuit.
NDE:
- Il faut s'assurer qu'on ne d�passe pas le nombre d'sorties permis (MAX_ENTREES).
- Il faut s'assurer que la sortie aura un identifiant unique parmi les sorties du circuit.
Param�tres:
- circuit: Pointeur vers le circuit auquel l'sortie sera ajout�e
Retour: Pointeur vers la sortie cr��e s'il a �t� possible de la cr�er. NULL sinon.
*/
t_sortie* t_circuit_ajouter_sortie(t_circuit * circuit);

/*
Fonction: T_CIRCUIT_EST_VALIDE
Description: V�rifie si un circuit donn� est un circuit valide. Pour qu'un circuit soit valide
			 toutes les entr�es, portes et sorties du circuit doivent �tre reli�es. 
NDE: Vous utiliserez les fonctions t_entree_est_reliee, t_sortie_est_reliee et t_porte_est_reliee. 
Param�tres:
- circuit: Pointeur vers le circuit dont on veut v�rifier la validit�
Retour: (Bool�en) Vrai si le circuit est valide, faux sinon.
*/
int t_circuit_est_valide(t_circuit *circuit);

/*
Fonction: T_CIRCUIT_APPLIQUER_SIGNAL
Description: Alimente le circuit avec le signal "signal" pass� en param�tre. Le signal est un ensemble
		     de bits (entiers qui valent 0 ou 1) qui sont appliqu�s aux entr�es du circuit. 
			 Les bits seront appliqu�s par ordre aux diff�rentes entr�es du circuit (le premier bit
			 du tableau � l'entr�e 0 du circuit, le 2e bit � l'entr�e 1, etc.)
NDE: 
- Vous devez vous assurer que le nombre de bits du signal est suffisant pour alimenter tout le circuit.
  (donc le nombre est au moins �gal au nombre d'entr�es du circuit)
- Pour appliquer un bit � un entr�e, il faut changer la valeur de la pin de sortie de l'entree (champs 
  pin dans t_entree).
Param�tres:
- circuit: Pointeur vers le circuit auquel on souhaite appliquer le signal
- signal: Tableau de bits qui constituent le signal � appliquer au circuit
- nb_bits: Nombre de bits dans le tableau signal. 
Retour: (Bool�en) Vrai si il a �t� possible d'appliquer le signal (i.e. assez de bits), faux sinon.
*/
int t_circuit_appliquer_signal(t_circuit * circuit, int signal[], int nb_bits);

/*
Fonction: T_CIRCUIT_RESET
Description: R�initialise un circuit en "d�salimentant" tous ses composants (entr�es, sorties et portes)
			 Cette fonction fait appel aux fonctions reset des diverses composants du circuit: 
			 t_entree_reset, t_sortie_reset et t_porte_reset.
Param�tres:
- circuit: Pointeur vers le circuit � r�initialiser.
Retour: Aucun.
*/
void t_circuit_reset(t_circuit *circuit);

/*
Fonction: T_CIRCUIT_PROPAGER_SIGNAL
Description: Propage le signal appliqu� aux entr�e du circuit � tous les composants. Le signal est propag�
			 de proche en proche: on part des entr�es et on envoie leur signal aux pins auquelles elles sont
			 connect�es. Si l'entr�e est connect�e � une porte, la porte calcule sa sortie puis envoie son 
			 signal � la pin � laquelle elle est connect�e, etc. jusqu'� ce que toutes les sorties re�oivent 
			 leur signal. 

			 Avant d'appeler cette fonction, on doit avoir pr�alablement appliqu� un signal au circuit 
			 (fonction t_circuit_appliquer_signal). La propagation du signal ne sera faite que si le circuit est valide.
			 
			 La fonction retourne faux s'il a �t� impossible de propager un signal dans l'un des cas suivants:
			 - Le circuit est invalide (voir t_circuit_est_valide)
			 - Le circuit n'a pas �t� pr�alablement aliment� (voir t_circuit_appliquer_signal)
			 - En cas de pr�sence de boucles dans le circuit
NDE: Pour propager le signal de proche en proche, vous utiliserez l'algorithme d�crit dans l'�nonc� qui utilise 
     une file de portes (t_file_porte)
Param�tres:
- circuit: Pointeur vers le circuit � r�initialiser.
Retour: Bool�en vrai si le signal s'est correctement propag� jusqu'aux sorties. Faux sinon. 
*/
int t_circuit_propager_signal(t_circuit *circuit);

#endif