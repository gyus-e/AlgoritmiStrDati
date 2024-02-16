#ifndef STACK_H_
#define STACK_H_

struct stack {
    int d;
    struct stack * next;
};

int top (const struct stack * const S);
struct stack * pop (struct stack * S);
struct stack * push (struct stack * S, const int n);

#endif