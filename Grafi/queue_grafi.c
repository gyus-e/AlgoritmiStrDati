#include "stdio.h"
#include "queue_grafi.h"
#include "grafi.h"

struct Queue * enqueue (struct Queue * Q, struct Vertice * V)
{
    if (V != NULL)
    {
        if (Q == NULL)
        {
            Q = malloc (sizeof(struct Queue));
            Q->head = V;
            Q->next = NULL;
        }
        else
        {
            Q->next = enqueue (Q->next, V);
        }
    }
    return Q;
}

struct Queue * dequeue (struct Queue * Q)
{
    if (Q != NULL)
    {
        struct Queue * temp = Q;
        Q = Q->next;
        free (temp);
    }
    return Q;
}

struct Queue * fill (struct Grafo * G)
{
    struct Queue * Q;
    for (int i = 0; i < G->V_Sz; i++)
    {
        Q = enqueue (Q, G->V[i]);
    }
    return Q;
}

struct Queue * delete (struct Queue * Q, struct Vertice * V)
{
    struct Queue * Pred = NULL, * Curr = Q;
    while (Curr != NULL)
    {
        if (Curr->head == V)
        {
            if (Pred != NULL)
            {
                Pred->next = Curr->next;
            }
            else 
            {
                Q = Curr->next;
            }
            free (Curr);
        }
        else 
        {
            Pred = Curr;
            Curr = Curr->next;
        }
    }
    return Q;
}