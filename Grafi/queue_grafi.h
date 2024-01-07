#include "grafi.h"

#ifndef QUEUE_GRAFI_H_
#define QUEUE_GRAFI_H_

struct Queue {
    struct Vertice * head;
    struct Queue * next;
};

struct Vertice * getHead (const struct Queue * const Q) {return Q->head;}
struct Queue * getNext (const struct Queue * const Q) {return Q->next;}
struct Queue * enqueue (struct Queue * Q, struct Vertice * V);
struct Queue * dequeue (struct Queue * Q);
struct Queue * fill (struct Grafo * G);
struct Queue * delete (struct Queue * Q, struct Vertice * V);

#endif