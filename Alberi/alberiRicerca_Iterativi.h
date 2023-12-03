#include "alberi.h"

#ifndef ALBERIRICERCA_ITERATIVI_H_
#define ALBERIRICERCA_ITERATIVI_H_

//public:
struct Tree * Search_Iterativo (struct Tree * T, TIPO k);
struct Tree * Min_Iterativo (struct Tree * T);
struct Tree * Max_Iterativo (struct Tree * T);
struct Tree * Successore_Iterativo (struct Tree * T, TIPO k);
struct Tree * Insert_Iterativo (struct Tree * T, TIPO k);

#endif