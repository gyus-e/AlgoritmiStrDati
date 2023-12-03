#include "alberi.h"

#ifndef ALBERIRICERCA_H_
#define ALBERIRICERCA_H_

struct Tree * Search (struct Tree * T, TIPO k);
struct Tree * Min (struct Tree * T);
struct Tree * Max (struct Tree * T);
struct Tree * Successore (struct Tree * T, TIPO k);
struct Tree * Insert (struct Tree * T, TIPO k);
struct Tree * Delete (struct Tree * T, TIPO k);

struct Tree * DeleteRoot (struct Tree * T);
struct Tree * StaccaMin (struct Tree * T, struct Tree * Pred);


#endif