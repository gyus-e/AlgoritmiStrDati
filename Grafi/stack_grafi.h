#include "grafi.h"

#ifndef STACK_GRAFI_H_
#define STACK_GRAFI_H_

struct Stack {
    struct Vertice * head;
    struct Stack * next;
};

struct Vertice * top (const struct Stack * const S) {return S->head;}
struct Stack * push (struct Stack * S, struct Vertice * V);
struct Stack * pop (struct Stack * S);

#endif