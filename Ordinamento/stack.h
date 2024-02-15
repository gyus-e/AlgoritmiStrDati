#ifndef STACK_H_
#define STACK_H_

struct stack {
    int dato;
    struct stack * next;
};
void push (struct stack * S, const int d);
struct stack * pop (struct stack * S);
int top (const struct stack * const S);

#endif