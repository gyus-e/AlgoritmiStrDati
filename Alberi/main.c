#include "alberi.h"
#include "alberiRicerca.h"

#include <stdio.h>
#include <stdlib.h>

int main ()
{
    struct Tree * T = NULL;
    int k;
    while (scanf("%d", &k) == 1)
    {
        T = Insert (T, k);
    }

    Print_BFS (T);
    printf("\n");
    //Print_DFS (T);

    return 0;
}