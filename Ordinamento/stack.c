#include "stack.h"
#include "stdio.h"
#include "stdlib.h"

void push (struct stack * S, const int d) 
{
    while (S!= NULL) 
    {
        S = S->next;
    } 
    S = malloc (sizeof (struct stack)); 
    S->dato = d; 
    S->next = NULL;
}

struct stack * pop (struct stack * S)
{
    struct stack * ret = NULL;
    if (S != NULL)
    {
        ret = S->next;
        free (S);
    }
    return ret;
}

int top (const struct stack * const S) {
    if (S != NULL) 
    {
        return S->dato; 
    } 
    else 
    {
        return -1;
    }
}