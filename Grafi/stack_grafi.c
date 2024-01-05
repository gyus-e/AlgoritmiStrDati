#include "stdio.h"
#include "stack_grafi.h"
#include "grafi.h"

struct Stack * push (struct Stack * S, struct Vertice * V)
{
    if (V != NULL)
    {
        struct Stack * Nuovo = malloc (sizeof(struct Stack));
        Nuovo->head = V;
        Nuovo->next = S;
        return Nuovo;
    }
    else 
    {
        return S;
    }
}

struct Stack * pop (struct Stack * S)
{
    if (S != NULL)
    {
        struct Stack * temp = S;
        S = S->next;
        free (temp);
    }
    return S;
}