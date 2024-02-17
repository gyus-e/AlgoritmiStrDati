#ifndef QUEUE_H_
#define QUEUE_H_

struct Queue {
    struct Tree * head;
    struct Queue * next;
};

struct Tree * head (const struct Queue * const Q);
struct Queue * enqueue (struct Queue * Q, struct Tree * T);
void dequeue (struct Queue * Q);
struct Queue * NewQueueNode (struct Tree * T);
void deleteNode (struct Queue * Q, struct Queue * Pred);
#endif