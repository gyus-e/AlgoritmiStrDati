#ifndef STACK_H_
#define STACK_H_

typedef int bool;
#define true 1
#define false 0

struct stack {
    int d;
    struct stack * next;
};

int top (const struct stack * const S);
struct stack * pop (struct stack * S);
struct stack * push (struct stack * S, const int n);

#endif