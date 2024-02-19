#include "array.h"
#include "stack.h"
#include "boolean.h"

#include "quicksort.h"
#include "heapsort.h"
#include "mergesort.h"

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int main ()
{
    unsigned int in = 0;
    unsigned int dim = 0;
    while (true)
    {
        printf("Insert size of array:\n");
        if (scanf ("%u", &dim) != 1 || dim < 1)
        {
            break;
        }
        printf("Generating new array:\n");
        int * A =  malloc (dim * (sizeof(int)));
        srand (time(0));
        fill (A, dim);
        printArray (A, dim);

        printf ("Press 0 for HeapSort\n"
        "Press 1 for QuickSort\n"
        "Press 2 for QuickSort_iterativo\n"
        "Press 3 for MergeSort\n"
        "Press 4 for MergeSort_iterativo\n");

        if (scanf ("%u", &in) != 1 || in > 4)
        {
            break;
        }

        switch (in)
        {
            case 0:
            HeapSort (A, dim);
            break;

            case 1:
            QuickSort (A, 0, dim-1);
            break;

            case 2:
            QuickSort_iterativo (A, 0, dim-1);
            break;

            case 3:
            MergeSort (A, 0, dim-1);
            break;

            case 4:
            MergeSort_iterativo (A, 0, dim-1);
            break; 

            default:
            break;
        }

        printf("Sorted array:\n");
        printArray (A, dim); 
        free(A);
        printf("\n"); 
    }
    return 0;
}
