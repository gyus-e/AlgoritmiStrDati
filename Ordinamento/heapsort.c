#include "array.h"
#include "stack.h"
#include "boolean.h"
#include "heapsort.h"
#include <stdio.h>
#include <stdlib.h>

//Heapsort è un Selection sort che sfrutta un Maxheap per trovare piú rapidamente il massimo.
//Maxheap: albero binario completo tale che, per ogni nodo x, il valore di x è maggiore o uguale al valore dei suoi figli. Il massimo sará la radice.
//L'heap viene implementato come array.


void HeapSort(int *A)
{
    Buildheap(A);
    int heapsize = N;

    for (int i = N-1; i >= 1; i--)
    {
        //A[0] è sempre il massimo.
        //Portando il massimo in posizione M, lo si pone alla fine.
        Swap(A, 0, i);
        //Per mantenere la proprietá del Maxheap, si effettua heapify sul sottoarray non ordinato (di dimensione heapsize - 1).
        heapsize--;
        Heapify(A, heapsize, 0);
    }
}

// Le foglie sono giá alberi heap.
// In un albero completo di n nodi, ci sono n/2 foglie.
// Si parte dall'ultimo nodo interno (il padre dell'ultima foglia, in posizione n) applicando heapify su ogni nodo a risalire.
void Buildheap(int * const A)
{
    for (int i = Parent(N); i >= 0; i--)
    {
        Heapify(A, N, i);
    }
}

// Assume che i sottoalberi sinistro e destro di t siano giá heap.
// Individua il valore piú grande tra figlio sinistro, figlio destro e t, posizionandolo nella radice.
void Heapify(int * const A, const unsigned int heapsize, const unsigned int i)
{
    int Sx = Left(i);  // posizione del figlio sinistro del nodo i
    int Dx = Right(i); // posizione del figlio destro del nodo i
    int max = i;

    if (A[max] < A[Sx] && Sx < heapsize) // i ha un figlio sinistro solo se Sx < heapsize
    {
        max = Sx;
    }

    if (A[max] < A[Dx] && Dx < heapsize)
    {
        max = Dx;
    }

    if (max != i)
    {
        Swap(A, i, max);
        Heapify(A, heapsize, max); //heapify si richiama sul nodo scambiato perché bisogna ritrasformarlo in heap
    }
    
}


unsigned int Left(const unsigned int i) 
{ 
    return 2 * i;
}

unsigned int Right(const unsigned int i) 
{ 
    return 2 * i + 1; 
}

unsigned int Parent(const unsigned int i) 
{ 
    return (int)(i / 2); 
}
