#include "array.h"
#include "heapsort.h"

//Heapsort è un Selection sort che sfrutta un Maxheap per trovare piú rapidamente il massimo.
//Maxheap: albero binario completo. Per ogni nodo x, il valore di x è maggiore o uguale al valore dei suoi figli. 
//Il massimo del Maxheap è la radice.

//L'heap viene implementato come array. L'elemento in posizione i-esima è il nodo i-esimo contando in orizzontale.

//Assumendo che l'array vada da A[0] ad A[N-1]
//Posizione del figlio sinistro del nodo i
unsigned int Left(const unsigned int i) 
{ 
    return ((2 * i) + 1);
}

//Posizione del figlio destro del nodo i
unsigned int Right(const unsigned int i) 
{ 
    return ((2 * i) + 2); 
}

//Posizione del padre del nodo i
int Parent(const unsigned int i) 
{
    if (i <= 2)
    {
        return 0;
    }
    else
    {
        return (int)(i / 2); 
    }
}

// Assume che i sottoalberi sinistro e destro di t siano giá heap.
// Individua il valore piú grande tra figlio sinistro, figlio destro e t, posizionandolo nella radice.
void Heapify (int * A, const unsigned int heapsize, const unsigned int i)
{
    const unsigned int Sx = Left(i);
    const unsigned int Dx = Right(i);
    unsigned int max = i;

    if (Sx < heapsize && A[Sx] > A[max]) // i ha un figlio sinistro solo se Sx < heapsize
    {
        max = Sx;
    }
    if (Dx < heapsize && A[Dx] > A[max])
    {
        max = Dx;
    }

    if (i != max)
    {
        Swap (A, i, max);
        //heapify deve essere richiamato sul nodo scambiato perché potrebbe aver perso le proprietá del Maxheap
        Heapify (A, heapsize, max);
    }
}

// Le foglie sono giá alberi heap.
// In un albero completo di n nodi, ci sono n/2 foglie.
// Si parte dall'ultimo nodo interno (il padre dell'ultima foglia, in posizione n) applicando heapify su ogni nodo a risalire.
void Buildheap (int * A, const unsigned int n)
{
    for (int i = Parent (n); i >= 0; i--)
    {
        Heapify (A, n, i);
    }
}

void HeapSort (int * A, const unsigned int n)
{
    Buildheap (A, n);
    unsigned int heapsize = n;

    for (int i = n-1; i > 0; i--)
    {
        //A[0] è sempre il massimo.
        //Portando il massimo in posizione i, lo si pone alla fine.
        Swap (A, i, 0);
        //Per mantenere la proprietá del Maxheap, si effettua heapify sul sottoarray non ordinato (di dimensione heapsize - 1).
        heapsize--;
        Heapify (A, heapsize, 0);
    }
}
