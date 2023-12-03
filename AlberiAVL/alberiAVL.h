#ifndef ALBERIAVL_H_
#define ALBERIAVL_H_

typedef int TIPO;

//Albero AVL: albero vuoto (altezza = -1), oppure nodo con due sottoalberi tali che:
//- Le altezze dei due sottoalberi differiscono al massimo di 1.
//- I due sottoalberi sono a loro volta AVL.

//"AVL" viene dal nome dei due ideatori: Adelson-Velsky, Landis.

//Per l'implementazione bisogna salvare in ogni nodo il valore dell'altezza.
//Il costo aggiuntivo di memoria, rispetto agli alberi binari di ricerca, è lineare sul numero di elementi.
struct Tree {
    TIPO key;
    struct Tree * left;
    struct Tree * right;
    unsigned int h;
};

//AVL minimo: AVL di altezza h col minor numero di nodi possibile.

//Teorema: i sottoalberi di un AVL minimo di altezza h sono rispettivamente l'AVL minimo di altezza h-1 e quello di altezza h-2.
//Teorema: se T è un AVL minimo di altezza h, con n elementi, qualsiasi altro AVL con n elementi avrá altezza minore o uguale a h.
//Teorema: l'altezza di un AVL minimo è logaritmica sul numero di nodi.

struct Tree * InsertAVL (struct Tree * , TIPO );

struct Tree * BilanciaSx (struct Tree * );
struct Tree * BilanciaDx (struct Tree * );
struct Tree * RotazioneSx (struct Tree * );
struct Tree * RotazioneDx (struct Tree * );

struct Tree * DeleteAVL (struct Tree * , TIPO );
struct Tree * DeleteRootAVL (struct Tree *);
struct Tree * StaccaMinAVL (struct Tree * , struct Tree * );

struct Tree * NewNode (TIPO);
int height (struct Tree *);

//Gli alberi AVL sono un caso particolare degli alberi binari di ricerca. Le funzioni di search, max, min e successore sono le stesse.
//Le versioni iterative di questi algoritmi non porterebbero vantaggi sulla memoria: sarebbe comunque necessario uno stack di costo lineare sull'altezza.

#endif