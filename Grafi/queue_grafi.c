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