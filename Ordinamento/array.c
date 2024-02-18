#include "array.h"
#include "stdio.h"
#include "stdlib.h"

void fill (int * const A, const int n)
{
    for (int i = 0; i < n; i++)
    {
        A[i] = rand () % 100;
    }
}

void printArray (const int * const A, const int n)
{
    for (int i = 0; i < n; i++)
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