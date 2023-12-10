#ifndef ALBERI_RB_H_
#define ALBERI_RB_H_

//Le foglie sono nodi NIL, dal contenuto irrilevante, ma di colore nero.
//In questo modo, non è necessario distinguere tra un puntatore a un nodo e un puntatore Null.
//Al posto di un puntatore Null si usa un puntatore ad un nodo NIL.

//PROPRIETÁ DI UN ALBERO RED-BLACK:
//Ogni nodo è rosso o nero
//I nodi NIL sono neri
//Se un nodo è rosso, i suoi figli sono entrambi neri
//Ogni percorso da un nodo interno fissato a un nodo NIL qualsiasi ha lo stesso numero di nodi neri

//Definiamo l'altezza nera di un nodo x, bh(x), come il numero di nodi neri da x a un qualsiasi nodo Null

//Per semplicitá, considereremo sempre nera la radice dell'albero'(in questo modo potrá avere figli di qualsiasi colore e non violerá la proprietá di altezza nera uguale per nessun nodo).

#define red 'r'
#define black 'b'

typedef int TIPO;

struct Tree {
    TIPO key;
    struct Tree * left;
    struct Tree * right;
    char color;
};

const struct Tree Nil = {0, NULL, NULL, black}; //usiamo un unico valore per rappresentare tutti i nodi Nil

//Il numero di nodi interni n di un (sotto-)albero radicato nel nodo x è:
// n >= 2^(bh(x))-1     n+1 = 2^(bh(x))      log(n+1) = bh(x)
//L'altezza nera di un nodo x deve essere maggiore o uguale alla metá dell'altezza di x: 
// bh(x) >= height(x)/2     2*bh(x) >= height(x)
//Ne segue che un albero Red Black radicato in x, con n nodi, ha altezza:
// height(x) <= 2*bh(x) = 2*log(n+1)

//Togliendo i nodi rossi da un albero RB si ottiene un albero pieno

//In un albero RB con n nodi, inserimenti, ricerche e cancellazioni hanno tutte tempo logaritmico su n
// t = O(log(n))

struct Tree * NewNode (TIPO k);

struct Tree * InsertRB (struct Tree * T, TIPO k);

struct Tree * BilanciaSx (struct Tree * T);
int ViolazioneSx (struct Tree * T);

struct Tree * BilanciaDx (struct Tree * T);
int ViolazioneDx (struct Tree * T);

struct Tree * RotazioneSx (struct Tree * T);
struct Tree * RotazioneDx (struct Tree * T);

struct Tree * DeleteRB (struct Tree * T, TIPO k);

#endif