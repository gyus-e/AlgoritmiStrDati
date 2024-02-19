#include "array.h"
#include "stack.h"
#include "boolean.h"

#include "quicksort.h"
#include "heapsort.h"
#include "mergesort.h"

#include "stdio.h"
#include "stdlib.h"
#include "time.h"


#define N 21

int main ()
{
    unsigned int in = 0;
    while (true)
    {
        printf("Generating new array:\n");
        int A [N];
        srand (time(0));
        fill (A, N);
        printArray (A, N);

        printf ("Press 0 for HeapSort\n"
        "Press 1 for QuickSort\n"
        "Press 2 for QuickSort_iterativo\n"
        "Press 3 for MergeSort\n"
        "Press 4 for MergeSort_iterativo\n"
        "Press 5 to quit\n");

        if (scanf ("%u", &in) != 1)
        {
            break;
        }

        switch (in)
        {
            case 0:
            HeapSort (A, N);
            break;

            case 1:
            QuickSort (A, 0, N-1);
            break;

            case 2:
            QuickSort_iterativo (A, 0, N-1);
            break;

            case 3:
            MergeSort (A, 0, N-1);
            break;

            case 4:
            MergeSort_iterativo (A, 0, N-1);
            break; 

            default:
            return 0;
        }

        printf("Sorted array:\n");
        printArray (A, N); 
        printf("\n\n");
    }
}
