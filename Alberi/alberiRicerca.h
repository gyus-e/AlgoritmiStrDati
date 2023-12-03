#include "alberi.h"

#ifndef ALBERIRICERCA_H_
#define ALBERIRICERCA_H_

struct Tree * Search (struct Tree * T, TIPO k);
struct Tree * Min (struct Tree * T);
struct Tree * Max (struct Tree * T);
struct Tree * Successore (struct Tree * T, TIPO k);
struct Tree * Insert (struct Tree * T, TIPO k); //Per la versione ottimizzata sulla memoria, vedere Insert_Iterativo
struct Tree * Delete (struct Tree * T, TIPO k); //Utile da ricordare per gli alberi bilanciati, dove la Tail Recursion non è possibile
void DeleteTR (struct Tree * T, TIPO k, struct Tree * Pred = NULL); //Delete ottimizzato sulla memoria con Tail Recursion.

//funzioni ausiliarie di Delete
struct Tree * DeleteRoot (struct Tree * T);
struct Tree * StaccaMin (struct Tree * T, struct Tree * Pred);



#endif