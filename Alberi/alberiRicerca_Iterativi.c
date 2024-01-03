#include "stdio.h"
#include "alberi.h"
#include "alberiRicerca_Iterativi.h"

struct Tree * Search_Iterativo (struct Tree * T, TIPO k)
{
    struct Tree * ret = T;
    while (ret != NULL && ret->key != k)
    {
        if (ret->key < k)
        {
            ret = ret->right;
        }
        else
        {
            ret = ret->left;
        }
    }
    return ret;
}

struct Tree * Min_Iterativo (struct Tree * T)
{
    struct Tree * min = T;
    while (min != NULL && min->left != NULL)
    {
        min = min->left;
    }
    return min;
}

struct Tree * Max_Iterativo (struct Tree * T)
{
    struct Tree * max = T;
    while (max != NULL && max->right != NULL)
    {
        max = max->right;
    }
    return max;
}

struct Tree * Successore_Iterativo (struct Tree * T, TIPO k)
{
    struct Tree * temp = T, * ret = NULL;
    while (temp != NULL && temp->key != k)
    {
        if (temp->key < k) //se k è piú grande del nodo corrente
        {
            temp = temp->right; //cerca nel sottoalbero destro
        }
        else //se k è piú piccolo del nodo corrente
        {
            ret = temp; //ricorda il padre
            temp = temp->left; //cerca nel sottoalbero sinistro
        }
    }    
    if (temp != NULL && temp->right != NULL) //se k è uguale al nodo corrente
    {
        ret = Min(temp->right); //il successore è il minimo nel sottoalbero destro
    }
    return ret;
}

//Versione ottimizzata sulla memoria: non usa stack
struct Tree * Insert_Iterativo (struct Tree * T, TIPO k)
{
    struct Tree * curr = T, * pred = NULL;
    while (curr != NULL && curr->key != k) //scorre l'albero
    {
        pred = curr;
        if (curr->key < k)
        {
            curr = curr->right;
        }
        else
        {
            curr = curr->left;
        }
    }
    if (curr == NULL)
    {
        if (pred == NULL)
        {
            return NewNode (k);
        }
        else if (pred->key < k)
        {
            pred->right = NewNode (k);
        }
        else
        {
            pred->left = NewNode (k);
        }
    }
    return T;
}

//Il Delete iterativo non è stato spiegato. Vedere DeleteTR per una versione ottimizzata sulla memoria.
//In alternativa propongo una mia implementazione.

struct Tree * Delete_Iterativo (struct Tree * T, TIPO k)
{
    if (T != NULL)
    {
        struct Tree * Tcurr = T;
        while (Tcurr != NULL) 
        {
            if (k == Tcurr->key)
            {
                Tcurr = DeleteRoot(Tcurr);
            }
            else if (k > Tcurr->key)
            {
                Tcurr = Tcurr->right;
            }
            else if (k < T->key)
            {
                Tcurr = Tcurr->left;
            }
        }
    }
    return T;
}

//DeleteRoot è giá iterativo. Cambia solo StaccaMin.
struct Tree * DeleteRoot_Iterativo (struct Tree * T)
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
            toDelete = StaccaMin_Iterativo (T->right, T);
            T->key = toDelete->key;
        }
        free (toDelete);
        toDelete = NULL;
        return T;
}
//Analogo alla ricerca del minimo iterativa
struct Tree * StaccaMin_Iterativo (struct Tree * T, struct Tree * Pred)
{
    struct Tree * min = T;
    while (min != NULL && min->left != NULL)
    {
        Pred = min;
        min = min->left;
    }

    if (Pred != NULL)
    {
        if (min == Pred->left)
        {
            Pred->left = min->right;
        }
        else if (min == Pred->right)
        {
            Pred->right = min->right;
        }
    }

    return min;
}