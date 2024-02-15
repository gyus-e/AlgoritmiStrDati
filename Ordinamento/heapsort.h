#ifndef HEAPSORT_H_
#define HEAPSORT_H_

void HeapSort(int *A);
void Buildheap(int *A);
void Heapify(int *A, const unsigned int heapsize, const unsigned int i);

void Swap (int * A, const unsigned int i, const unsigned int j);
unsigned int Left(const unsigned int i);
unsigned int Right(const unsigned int i);
unsigned int Parent(const unsigned int i);

#endif