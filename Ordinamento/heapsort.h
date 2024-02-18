#ifndef HEAPSORT_H_
#define HEAPSORT_H_

void HeapSort(int *A, const unsigned int n);
void Buildheap(int *A, const unsigned int n);
void Heapify(int *A, const unsigned int heapsize, const unsigned int i);


unsigned int Left(const unsigned int i);
unsigned int Right(const unsigned int i);
int Parent(const unsigned int i);

#endif