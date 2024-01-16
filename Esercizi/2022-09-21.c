//Esame 21/09/2022

//Dati in ingresso la radice di un ABR e due valori k1 e k2
//Scrivere un algoritmo ricorsivo per cancellare dall'albero tutti i nodi con chiave compresa tra k1 e k2.
//Riscrivere l'algoritmo in forma iterativa.

#include "alberi.h"
#include "alberiRicerca.h"
#include "stdio.h"

//È sostanzialmente una modifica di Delete per gli ABR
struct Tree * DeleteInterval (struct Tree * T, const int k1, const int k2)
{
	if (k1 <= k2 && T != NULL)
	{
		if (k1 <= T->key && T->key <= k2)
		{
			T = DeleteRoot (T);
			T = DeleteInterval (T, k1, k2);
		}
		else if (k1 > T->key) 
		{
			T->right = DeleteInterval (T->right, k1, k2);
		}
		else if (k2 < T->key)
		{
			T->left = DeleteInterval (T->left, k1, k2);
		}
	}
	return T;
}

//La versione iterativa non richiede stack
struct Tree * DeleteInterval_Iterativo (struct Tree * T, const int k1, const int k2)
{
	if (k1 > k2 || T == NULL)
	{
		return T;
	}

	struct Tree * Tcurr = T;
	while (Tcurr != NULL)
	{
		if (k1 <= Tcurr->key && Tcurr->key <= k2)
		{
			Tcurr = DeleteRoot (Tcurr);
		}
		else if (k1 > Tcurr->key) 
		{
			Tcurr = Tcurr->right;
		}
		else if (k2 < Tcurr->key)
		{
			Tcurr = Tcurr->left;
		}
	}
	return T;
}

//Qui la versione proposta durante le videolezioni di tutorato del 2022
//Anziché richiamare l'algoritmo sulla radice dopo la cancellazione, effettua due chiamate ricorsive sui figli prima della cancellazione
struct Tree * DeleteInterval_POSTORDER (struct Tree * T, const int k1, const int k2)
{
	if (k1 <= k2 && T != NULL)
	{
		if (k1 <= T->key && T->key <= k2)
		{
			T->left = DeleteInterval_POSTORDER (T->left, k1, k2);
			T->right = DeleteInterval_POSTORDER (T->right, k1, k2);
			T = DeleteRoot (T);
		}
		else if (k1 > T->key) 
		{
			T->right = DeleteInterval_POSTORDER (T->right, k1, k2);
		}
		else if (k2 < T->key)
		{
			T->left = DeleteInterval_POSTORDER (T->left, k1, k2);
		}
	}
	return T;
}	