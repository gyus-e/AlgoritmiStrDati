#include "stdio.h"
#include "alberi.h"
#include "queue.h"

//BFS (Breadth-First Search): Visita in orizzontale.
//Tempo lineare sul numero di nodi dell'albero.
//Usa una coda (first-in, first-out) per memorizzare i figli del nodo attuale.
//Dopodiché cancella dalla coda il nodo appena visitato e passa al successivo.
void Print_BFS (struct Tree * T)
{
    struct Queue * Q = NULL;
    Q = enqueue(Q, T);
    while (Q != NULL)
    {
        printf("%d ", getHead(Q)->key); //visita: stampa
        Q = enqueue (Q, T->left);
        Q = enqueue (Q, T->right);
        Q = dequeue (Q);
    }
}

//DFS (Depth-First Search): Visita in verticale.
//Tempo lineare sul numero di nodi dell'albero.
//3 tipi:
//Preorder: visita è prima delle due chiamate ricorsive.
//Order: visita è tra le due chiamate ricorsive.
//Postorder: visita è dopo le due chiamate ricorsive.

//Print: esempio di order.
void Print_DFS (struct Tree * T)
{
    if (T != NULL)
    {
        Print_DFS (T->left); //chiamata ricorsiva a sinsitra
        printf ("%d ", T->key); //visita: stampa
        Print_DFS (T->right); //chiamata ricorsiva a destra
    }
}

//Algoritmo di ricerca: esempio di preorder.
struct Tree * Search_DFS (struct Tree * T, TIPO k)
{
    struct Tree * ret = T;
    if (T != NULL)
    {
        if (T->key != k) //visita: confronto tra T->key e k
        {
            ret = Search_DFS (T->left, k); //chiamata ricorsiva a sinistra
            if (ret == NULL)
            {
                ret = Search_DFS (T->right, k); //chiamata ricorsiva a destra
            } 
        }
    }
    return ret;
}

//Eval: esempio di postorder.
//Si assume che l'albero rappresenti un'espressione aritmetica, dove i padri contengono un'operazione che va eseguita sui figli.
//Quindi le foglie assumono valori numerici, mentre i nodi interni rappresentano operatori che prendono i figli come operandi.
TIPO Eval (struct Tree * T)
{
    TIPO ret = 0;
    if (T != NULL)
    {
        if (T->left == NULL && T->right == NULL)
        {
            ret = T->key;
        }
        else
        {
            TIPO Sx = Eval (T->left); //chiamata ricorsiva a sinistra
            TIPO Dx = Eval (T->right); //chiamata ricorsiva a destra
            
            //ret = T->key (Sx, Dx);   //visita: operazione sui due figli (implementato sotto)
            switch (T->key)
            {
                case '+':
                ret = (int)Sx + (int)Dx;
                break;

                case '-':
                ret = (int)Sx - (int)Dx;
                break;

                case '*':
                ret = (int)Sx * (int)Dx;
                break;

                case '/':
                ret = (int)Sx / (int)Dx;
                break;

                default:
                ret = 0;
                break;
            }
            
        }
    }
    return ret;
}
