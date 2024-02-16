#include "array.h"
#include "stdio.h"
#include "stdlib.h"

void fill (int * const A)
{
    for (int i = 0; i < N; i++)
    {
        A[i] = rand () % 100;
    }
}

void printArray (const int * const A)
{
    for (int i = 0; i < N; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void Swap(int * const A, const unsigned int i, const unsigned int j)
{
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}