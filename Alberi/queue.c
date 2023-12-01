#include "stdio.h"
#include "queue.h"
#include "alberi.h"

struct Queue * enqueue (struct Queue * Q, struct Tree * T)
{
    if (T != NULL)
    {
        if (Q == NULL)
        {
            Q = malloc (sizeof(struct Queue));
            Q->head = T;
            Q->next = NULL;
        }
        else
        {
            Q->next = enqueue (Q->next, T);
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