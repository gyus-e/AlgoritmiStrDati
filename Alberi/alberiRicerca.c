#include <stdio.h>
#include <stdlib.h>
#include "alberi.h"
#include "alberiRicerca.h"

//Tutte queste funzioni hanno tempo lineare sull'altezza. In generale, l'altezza è logaritmica sul numero di nodi dell'albero.
//Attenzione: in caso di un albero degenere (cioé una lista) l'altezza è lineare sul numero di nodi.

//Ricerca su albero ordinato.
struct Tree * Search (struct Tree * T, TIPO k)
{
    if (T != NULL && T->key != k)
    {
        if (T->key < k)
        {
            return Search (T->right, k);
        }
        else if (T->key > k)
        {
            return Search (T->left, k);
        }
    }
    else 
    {
        return T;
    }
}

//Il minimo è l'ultimo nodo a sinistra privo di figli a sinistra. 
//Non è necessariamente una foglia: puó avere figli a destra!
struct Tree * Min (struct Tree * T)
{
    if (T != NULL)
    {
        if (T->left != NULL)
        {
            return Min (T->left);
        }
    }
    return T;
}

//Il massimo è l'ultimo nodo a destra privo di figli a destra. 
//Non è necessariamente una foglia: puó avere figli a sinistra!
struct Tree * Max (struct Tree * T)
{
    if (T != NULL)
    {
        if (T->left != NULL)
        {
            return Max (T->right);
        }
    }
    return T;
}

//Successore: trova il nodo dell'albero immediatamente piú grande a un dato valore.
//Attenzione: k non è necessariamente nell'albero.
struct Tree * Successore (struct Tree * T, TIPO k)
{
    if (T != NULL)
    {
        if (k == T->key) //se k è uguale alla radice
        {
            return Min (T->right); //il successore è il minimo nel sottoalbero destro
            
        } 
        else if (k > T->key) //se k è piú grande della radice
        {
            return Successore (T->right, k); //cerca il successore nel sottoalbero destro
        }
        else //se k è piú piccolo della radice
        {
            struct Tree * ret = Successore (T->left, k); //cerca il successore nel sottoalbero sinistro
            if (ret == NULL) //se non c'è, allora il successore è la radice
            {
                ret = T;
            }
            return ret;
        }
    }
}

//Inserimento. Richiede stack.
struct Tree * Insert (struct Tree * T, TIPO k)
{
    if (T == NULL)
    {
        T = NewNode (k);
    }
    else
    {
        if (T->key < k)
        {
            T->right = Insert (T->right, k);
        }
        else if (T->key > k)
        {
            T->left = Insert (T->left, k);
        }
    }
    return T;
}

//Cancellazione.
//Algoritmo analogo all'inserimento.
//Fa uso di una funzione ausiliaria: DeleteRoot.
//Fa uso di stack. Per la versione senza stack, vedere DeleteTR.
struct Tree * Delete (struct Tree * T, TIPO k)
{
    if (T != NULL) //T arriva a Null quando k non è nell'albero.
    {
        if (k == T->key) //Caso base: k è stato trovato. 
        {
            T = DeleteRoot(T); //Elimina questo nodo preservando le proprietá di ordinamento e i sottoalberi figli.
        }
        else if (k > T->key)
        {
            T->right = Delete (T->right, k);
        }
        else if (k < T->key)
        {
            T->left = Delete (T->left, k);
        }
    }
    return T;
}

//DeleteRoot. Fa uso di una funzione ausiliaria: StaccaMin
struct Tree * DeleteRoot (struct Tree * T)
{
        struct Tree * toDelete = T;

        if (T->left == NULL) //non c'è figlio sinistro: assegna a T il suo figlio destro (puó anche essere Null)
        {   
            T = T->right;
        }
        else if (T->right == NULL) //non c'è figlio destro: assegna a T il suo figlio sinistro
        {
            T = T->left;
        }
        else //problema: il nodo da eliminare ha due figli
        {
            //Vogliamo solo rimuovere il dato: manteniamo il nodo T.
            //Spostiamo in T il dato di un altro nodo.
            //Questo nodo deve essere facile da eliminare e mantenere le proprietá di ordinamento dopo aver spostato il suo dato in T.
            //Tale nodo è il minimo del sottoalbero destro di T (oppure il massimo del sottoalbero sinistro).
            toDelete = StaccaMin (T->right, T); //il minimo sará il nodo da eliminare, ma prima bisogna copiare in T il suo valore.
            T->key = toDelete->key;
        }
        free (toDelete);
        toDelete = NULL;
        return T;
}

//StaccaMin funziona come l'algoritmo di ricerca del minimo. 
//Bisogna solo aggiungere un else nel caso base per assicurarne la corretta eliminazione dall'albero.
//L'algoritmo deve comunque restituire il nodo contenente il valore minimo.
struct Tree * StaccaMin (struct Tree * T, struct Tree * Pred)
{
    if (T != NULL)
    {
        if (T->left != NULL)
        {
            return StaccaMin (T->left, T); //Scende a sinistra lungo l'albero.
        } 
        else //Caso base: T è il minimo. Non ha figli a sinistra. Bisogna modificare l'albero sostituendo T con il suo eventuale figlio destro.
        {
            if (Pred != NULL) //se Pred è Null, allora DeleteRoot sta rimuovendo la radice dell'albero. Basta solo copiare il minimo del sottoalbero destro nella radice e poi eliminarlo.
            {
                if (T == Pred->left) //se T è il figlio a sinistra 
                {
                    Pred->left = T->right; 
                }
                else //se T è il figlio a destra: ricorda che, in DeleteRoot, StaccaMin viene chiamato su (T->right, T). Il minimo potrebbe essere in T alla prima chiamata.
                {  
                    Pred->right = T->right;
                }
            }
        }
    }
    return T; //restituisce il nodo minimo (non piú presente nell'albero)
}

//Delete Tail Rercursive.
//Necessario un puntatore al padre.
//Non funziona se viene chiamato sulla radice: serve una funzione dedicata per la radice che chiamerá il DeleteTR sui sottoalberi figli.
void DeleteTR (struct Tree * T, TIPO k, struct Tree * Pred)
{
    if (T != NULL)
    {
        if (k == T->key) 
        {
            //Non possiamo piú restituire un valore da assegnare a T: dobbiamo salvare l'albero restituito da DeleteRoot in una variabile temporanea
            struct Tree * newT = DeleteRoot(T);
            //Quindi dobbiamo metterla al posto giusto nell'albero (per questo serve indicare anche il padre)
            if (Pred != NULL) //Controllo inutile grazie alla funzione DeleteTR_Root, ma aggiunto per robustezza
            {
                if (T == Pred->left)
                {
                    Pred->left = newT;
                }
                else
                {
                    Pred->right = newT;
                }
            }
        }
        else if (k > T->key)
        {
            DeleteTR (T->right, k, T);
        }
        else if (k < T->key)
        {
            DeleteTR (T->left, k, T);
        }
    }
    return;
}

struct Tree * DeleteTR_Root (struct Tree * T, TIPO k)
{
    if (T != NULL)
    {
        if (k == T->key)
        {
            T = DeleteRoot (T);
        }
        else if (k > T->key)
        {
            DeleteTR (T->right, k, T);
        }
        else if (k < T->key)
        {
            DeleteTR (T->left, k, T);
        }
    }
    return T;
}