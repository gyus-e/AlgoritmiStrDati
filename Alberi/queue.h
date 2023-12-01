#include "alberi.h"

#ifndef QUEUE_H_
#define QUEUE_H_

struct Queue {
    struct Tree * head;
    struct Queue * next;
};

struct Tree * getHead (const struct Queue * const Q) {return Q->head;}
struct Queue * enqueue (struct Queue * Q, struct Tree * T);
struct Queue * dequeue (struct Queue * Q);

#endif