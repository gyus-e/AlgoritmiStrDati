//Esame 19/11/2022

//Dati in ingresso un albero binario di ricerca e un intero positivo k
//Scrivere un algoritmo ricorsivo che cancelli tutti i nodi che si trovano in posizioni multiple di k nell'ordinamento totale delle chiavi dell'albero.

//Esempio: se k=2 e l'albero contiene 1,4,5,7,29,30,56,91 si cancellano 4,7,30,91 cioé i valori la cui posizione nell'ordinamento è un multiplo di 2.

#include "alberi.h"
#include "stdio.h"

//Si puó effettuare una visita in order per ottenere la posizione, posto di conoscere il numero di nodi giá visitati (sará il nostro valore di ritorno).
//Ma bisogna cancellare in postorder per non perdere la posizione originale dei nodi.
//Poiché il valore di ritorno è il numero di nodi visitati, la cancellazione deve essere implementata come in DeleteTR.
unsigned int DeletePosMultipli (struct Tree * T, struct Tree * Pred, const unsigned int k, unsigned int visited)
{
    if (T != NULL)
    {
        unsigned int pos = DeletePosMultipli (T->left, T, k, visited); //I nodi giá visitati prima di arrivare a T, piú i nodi a sinistra di T che saranno stati visitati al ritorno di questa chiamata.

        //order: trova la posizione del nodo corrente
        pos = pos + 1;
        
        visited = DeletePosMultipli (T->right, T, k, pos); //Ora il numero di nodi visitati è dato dalla posizione. Ma al termine voglio restituire anche quelli che saranno stati visitati al ritorno dalla chiamata a destra.
        
        //postorder: elimina i nodi
        if (pos % k == 0)
        {
            struct Tree * newT = DeleteRoot (T);
            if (Pred != NULL)
            {
                if (Pred->left == T)
                {
                    Pred->left = newT;
                }
                else if (Pred->right == T)
                {
                    Pred->right = newT;
                }
            }
        }
    }
    return visited;
}
//Questo algoritmo, come il Delete con tail recursion, non restituisce l'albero modificato se gli viene passata la radice.
//Quindi serve una funzione dedicata per la radice, che chiamerá l'algoritmo ricorsivo sui sottoalberi figli.
struct Tree * DeletePosMultipli_Root (struct Tree * T, const unsigned int k)
{
    if (T != NULL)
    {
        unsigned int pos = DeletePosMultipli (T->left, T, k, 0); //restituisce il numero di nodi visitati
        pos = pos + 1; //visita in order: trova la posizione del nodo corrente
        DeletePosMultipli (T->right, T, k, pos); //non ci interessa salvare il valore di ritorno

        if (pos % k == 0)
        {
            T = DeleteRoot (T);
        }
    }
    return T;
}

struct Tree * DeleteRoot (struct Tree * T)
{
    struct Tree * toDelete = T;
    if (T->left == NULL)
    {
        T = T->right;
    }
    else if (T->right == NULL)
    {
        T = T->left;
    }
    else 
    {
        toDelete = StaccaMin (T->left, T);
        T->key = toDelete->key;
    }
    free (toDelete);
    toDelete = NULL;
    return T;
}

struct Tree * StaccaMin (struct Tree * T, struct Tree * Pred)
{
    if (T == NULL)
    {
        return NULL;
    }
    else if (T->left != NULL)
    {
        return StaccaMin (T->left, T);
    }
    else 
    {
        if (Pred != NULL)
        {
            if (T == Pred->left)
            {
                Pred->left = T->right;
            }
            else if (T == Pred->right)
            {
                Pred->right = T->right;
            }
        }
        return T;
    }
}