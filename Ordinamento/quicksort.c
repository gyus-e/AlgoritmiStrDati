#include "array.h"
#include "stack.h"
#include "quicksort.h"
#include "stdio.h"
#include "stdlib.h"

void QuickSort(int *A, int p, int r)
{
    if (p < r)
    {
        int q = Partiziona(A, p, r);
        QuickSort(A, p, q);
        QuickSort(A, q + 1, r);
    }
}

//ATTENZIONE
//in certi casi partiziona va out of bounds per quanto riguarda j

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





///////////////////////////////////////////////////////////////////////////////////////////////

void Quicksort_iterativo (int * A, int p, int r)
{
    int cp = p; int cr = r;
    struct stack * p_stack = NULL; 
    struct stack * r_stack = NULL;
    bool start = true; 
    int q;

    while (start == true || r_stack == NULL)
    {
        if (start == true)
        {
            if (cp < cr)
            {
                q = Partiziona (A, cp, cr);

                push (p_stack, cp); push (r_stack, cr);
                cr = q;
            }
            else 
            {
                start = false;
            }
        }
        else 
        {
            cp = top (p_stack); cr = top (r_stack);
            p_stack = pop (p_stack); r_stack = pop (r_stack);

            if (cr == q)
            {
                push (p_stack, cp); push (r_stack, cr);
                cp = q+1;

                start = true;
            }
        }
    }
}

