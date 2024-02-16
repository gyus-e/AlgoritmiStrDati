#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

unsigned int fattoriale (const unsigned int n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return n * fattoriale (n-1);
    }
}

unsigned int fattoriale_iterativo (const unsigned int n)
{
    unsigned int cn = n;
    int ret = 1;
    //struct stack * stk_n = NULL; //superfluo, in quanto basta incrementare n per recuperare il valore precedente
    int last = 0;
    bool start = true;

    //while (start == true || stk_n != NULL)
    while (start == true || cn < n)
    {
        if (start == true)
        {
            if (cn == 0)
            {
                ret = 1;
                last = cn;
                start = false;
            }
            else 
            {
                //stk_n = push (stk_n, cn);
                cn--;
            }
        }
        else 
        {
            cn++; //cn = top (stk_n); 
           
            if (cn == last + 1); //sempre vero
            {
                ret *= cn;
                last = cn;
                //stk_n = pop (stk_n);
            }
        }
    }
    return ret;
}

int main ()
{
    unsigned int N;
    if (scanf("%u", &N) != 1)
    {
        return -1;
    }
    printf("%u\n", fattoriale(N));
    printf("%u\n", fattoriale_iterativo(N));
    return 0;
}