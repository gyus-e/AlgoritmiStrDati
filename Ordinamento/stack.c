#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int top (const struct stack * const S)
{
    if (S != NULL)
        return S->d;
    else return -1;
}

struct stack * pop (struct stack * S)
{
    if (S != NULL)
    {
        struct stack * tmp = S;
        S = S->next;
        free (tmp);
        tmp = NULL;
    }
    return S;
}

struct stack * push (struct stack * S, const int n)
{
    struct stack * ret = malloc (sizeof (struct stack));
    ret->d = n;
    ret->next = S;
    return ret;
}