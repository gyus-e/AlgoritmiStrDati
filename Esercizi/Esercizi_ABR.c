/*
Per i seguenti esercizi, si scrivano degli algoritmi ricorsivi efficienti
che non facciano uso né di variabili globali né di parametri passati per riferimento.
*/
#include "stdio.h"
#include "alberi.h"
#include "alberiRicerca.h"

//Esercizio 1:
//Dato un ABR T, due chiavi k1 ≤ k2 ed un intero c, 
//rimuovere da T tutti i nodi con chiave k compresa tra k1 e k2 (k1 ≤ k ≤ k2) e nei cui sottoalberi ci siano al piú c nodi da rimuovere.

void Esercizio1 (struct Tree * T, const int k1, const int k2, const int c)
{
}


//Esercizio 2:
//Dato un ABR T e due interi h1 ≤ h2,
//rimuovere dall’albero tutte le chiavi pari che si trovino a distanza compresa tra h1 ed h2 dalla radice.

void Esercizio2 (struct Tree * T, const int h1, const int h2, unsigned int d) //Assumo d = 0 alla prima chiamata
{
    if (T != NULL && h1 <= h2)
    {
        //Visito l'albero incrementando la distanza di 1 a ogni discesa
        Esercizio2 (T->left, h1, h2, d+1);
        Esercizio2 (T->right, h1, h2, d+1);

        //in postorder effettuo la cancellazione
        if ((T->key % 2 == 0) && (h1 <= d) && (d <= h2))
        {
            T = DeleteRoot (T);
        }
    }
}

//Esercizio 3:
//Dato un ABR T ed un intero d,
//rimuovere dall’albero tutti i nodi con chiave dispari e che si trovino a distanza da una foglia maggiore di d. 
//Hint: la distanza di un nodo da una foglia è la lunghezza del percorso più breve da quel nodo ad una qualunque foglia dell’albero.

int Esercizio3 (struct Tree * T, const int d)
{
    if (T != NULL)
    {
        unsigned int dist;
        //Caso base: foglia
        if (T->left == NULL && T->right == NULL)
        {
            dist = 0;
        }
        //Visita in postorder
        else 
        {
            int dSx = Esercizio3 (T->left, d); //distanza del figlio sinistro da una foglia
            int dDx = Esercizio3 (T->right, d); //distanza del figlio destro da una foglia
            dist = LesserValue (dSx, dDx) + 1; //la distanza del nodo corrente è la piú piccola delle due, aumentata di uno
        }
        //cancellazione
        if ((dist > d) && (T->key % 2 != 0))
        {
            T = DeleteRoot (T);
        }
        return dist;
    }
}

int LesserValue (const int a, const int b)
{
    if (a <= b)
    {
        return a;
    }
    else 
    {
        return b;
    }
}