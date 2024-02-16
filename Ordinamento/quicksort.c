#include "array.h"
#include "stack.h"
#include "boolean.h"
#include "quicksort.h"
#include <stdio.h>
#include <stdlib.h>

void QuickSort(int *A, int p, int r)
{
    if (p < r)
    {
        int q = Partiziona(A, p, r);
        QuickSort(A, p, q);
        QuickSort(A, q + 1, r);
    }
}

//Partiziona separa l'array in due parti, in base a un pivot
//A sinistra vanno tutti gli elementi minori del pivot
//A destra vanno tutti gli elementi maggiori del pivot
int Partiziona(int *A, int p, int r)
{
    //vale che: p < r
    int x = A[p]; //x è il pivot
    int i = p - 1; 
    int j = r + 1;
    //vale che: i < j

    do 
    {
        //finché A[j] è piú grande del pivot, decrementa j
        do
        {
            j--;
        } while (A[j] > x);

        //finché A[i] è piú piccolo del pivot, incrementa i
        do 
        {
            i++;
        } while (A[i] < x);
        
        //Se i < j, sono stati trovati due elementi da scambiare
        if (i<j)
        {
            Swap (A, i, j);
        }

    } while (i < j);
    //alla fine dell'esecuzione si avrá o i=j o i>j a seconda di come è fatto l'array
    
    return j;
}

void QuickSort_iterativo (int *A, int p, int r)
{
    bool start = true;
    int last;

    int cp = p, cr = r, q;
    struct stack  *stk_p = NULL, *stk_r = NULL, *stk_q = NULL;

    while (start || stk_p != NULL)
    {
        if (start)
        {
            if (cp < cr)
            {
                q = Partiziona (A, cp, cr);
                
                stk_p = push (stk_p, cp);
                stk_r = push (stk_r, cr);
                stk_q = push (stk_q, q);

                cr = q;
            }
            else 
            {
                last = cr;
                start = false;
            }
        }
        else 
        {
            cp = top (stk_p);
            cr = top (stk_r);
            q = top (stk_q);

            if (last == q)
            {
                cp = q+1;
                start = true;
            }
            else 
            {
                stk_p = pop (stk_p); 
                stk_q = pop (stk_q); 
                stk_r = pop (stk_r);
                last = cr;
            }
        }
    }
}