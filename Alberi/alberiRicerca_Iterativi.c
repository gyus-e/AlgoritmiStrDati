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

//Il Delete iterativo non è stato spiegato