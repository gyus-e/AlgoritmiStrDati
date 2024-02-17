#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "alberi.h"

struct Tree * head (const struct Queue * const Q) 
{
    return Q->head;
}

struct Queue * enqueue (struct Queue * Q, struct Tree * T)
{
    if (T != NULL)
    {
        struct Queue * newQ = NewQueueNode (T);
        newQ->next = Q;
        return newQ;
    }
    else 
    {
        return Q;
    }
}

void dequeue (struct Queue * Q)
{
    struct Queue * curr = Q, * pred = NULL;
    while (curr->next != NULL)
    {
        pred = curr;
        curr = curr->next;
    }
    deleteNode (curr, pred);
    curr = NULL;
}

struct Queue * NewQueueNode (struct Tree * T)
{
    struct Queue * Q = malloc (sizeof(struct Queue));
    Q->head = T;
    Q->next = NULL;
    return Q;
}


void deleteNode (struct Queue * Q, struct Queue * Pred)
{
    if (Pred != NULL)
    {
        Pred->next = NULL;
    }
    if (Q != NULL)
    {
        free (Q);
        Q = NULL;
    }
}