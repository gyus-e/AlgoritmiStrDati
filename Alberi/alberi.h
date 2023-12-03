#include "stdio.h"
#include "stdlib.h"

#ifndef ALBERI_H_
#define ALBERI_H_

typedef int TIPO;

//private:
struct Tree {
    TIPO key;
    struct Tree * left;
    struct Tree * right;
};

//public:
struct Tree * NewNode (TIPO k);
void Print_BFS (struct Tree * T);
void Print_DFS (struct Tree * T);
struct Tree * Search_DFS (struct Tree * T, TIPO k);
TIPO Eval (struct Tree * T);

#endif