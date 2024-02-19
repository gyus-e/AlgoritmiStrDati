#include "array.h"
#include "stack.h"
#include "boolean.h"
#include "mergesort.h"
#include <stdio.h>
#include <stdlib.h>

void MergeSort (int * A, int l, int r)
{
    if (l < r)
    {
        int q = (int) ((l+r)/2);
        MergeSort (A, l, q);
        MergeSort (A, q+1, r);
        Merge (A, l, q, r);
    }
}

void Merge (int * A, int l, int q, int r)
{
    int * B = malloc (r+1 * sizeof (int));
    int i = l;
    int j = q+1;
    int k = l;

    while (i <= q && j <= r)
    {
        if (A[i] < A[j])
        {
            B[k] = A[i];
            i++;
        }
        else 
        {
            B[k] = A[j];
            j++;
        }
        k++;
    }
    
    int x;
    if (i <= q)
    {
        x = i;
    }
    else 
    {
        x = j;
    }
    while (k <= r)
    {
        B[k] = A[x];
        x++;
        k++;
    }

    for (int u = l; u <= r; u++)
    {
        A[u] = B[u];
    }
    free (B);
}

void MergeSort_iterativo (int * A, int l, int r)
{
    bool start = true;
    int last;

    int cl = l, cr = r;
    int q;
    struct stack * stk_l = NULL, * stk_r = NULL, *stk_q = NULL;

    while (start || stk_l != NULL)
    {
        if (start)
        {
            if (cl < cr)
            {
                q = (int) ((cl+cr)/2);

                stk_l = push (stk_l, cl);
                stk_r = push (stk_r, cr);
                stk_q = push (stk_q, q);

                cr = q;
            }
            else 
            {
                start = false;
                last = cr;
            }
        }
        else 
        {
            cl = top (stk_l);
            cr = top (stk_r);
            q = top (stk_q);
            if (q == last)
            {
                cl = q+1;
                start = true;
            }
            else 
            {
                stk_l = pop (stk_l);
                stk_r = pop (stk_r);
                stk_q = pop (stk_q);
                last = cr;
                Merge (A, cl, q, cr);
            }
        }
    }
}