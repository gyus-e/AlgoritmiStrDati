#ifndef GRAFI_H_
#define GRAFI_H_

typedef int TIPO;

#define infinity -1

#define black 'b'
#define gray 'g'
#define white 'w'

typedef int bool;
#define true 1
#define false 0

//Per rappresentare un vertice useremo una lista il cui primo elemento è il vertice e i successivi quelli a esso adiacenti.
struct Vertice {
    TIPO val;
    struct Vertice * next;
    //per semplificare l'implementazione aggiungo una chiave numerica univoca con cui identificare il vertice
    int key;
};

struct Grafo {
    struct Vertice ** v; //Array contenente tutti i vertici.
    int V_Sz; //numero di vertici.
    int E_Sz; //numero di archi.
};

char * Color; //Array che associa a ogni vertice un colore
int * Distance; //Array che associa a ogni vertice la sua distanza dalla sorgente
struct Vertice ** Pred; //Array che associa a ogni vertice il suo predecessore

unsigned int tempo = 0;
int * T_Scoperta; //Array che associa a ogni vertice il momento in cui è stato scoperto.
int * T_Fine; //Array che associa a ogni vertice il momento in cui sono stati esplorati tutti i suoi vertici adiacenti.

void Init_BFS (struct Grafo * G); //Inizializza Color e D.
void BFS (struct Grafo * G, struct Vertice * S); //Breadth First Search: Visita in ampiezza. S è il vertice sorgente.

void StampaPercorsoMinimo (struct Grafo * G, struct Vertice * S, struct Vertice * x);

void Init_DFS (struct Grafo * G);
void DFS (struct Grafo * G);
void DFS_Visit (struct Grafo * G, struct Vertice * S);
//La DFS genera la Foresta Depth-First.

/////////////////////////////////////////////////////////////////////////////////////////////////
//TEOREMA DELLA STRUTTURA A PARENTESI:

//Dato un grafo G, e dati due vertici V e U appartenenti al grafo
//Al termine di una visita DFS sará possibile UNA SOLA delle seguenti:

//  1) T_Scoperta [V] < T_Scoperta [U] < T_Fine [U] < T_Fine [V]
//  2) T_Scoperta [U] < T_Scoperta [V] < T_Fine [V] < T_Fine [U]

//  3) T_Scoperta [V] < T_Fine [V] < T_Scoperta [U] < T_Fine [U]
//  4) T_Scoperta [U] < T_Fine [U] < T_Scoperta [V] < T_Fine [V]

/////////////////////////////////////////////////////////////////////////////////////////////////
//TEOREMA DEL PERCORSO BIANCO:

//Dato un grafo G, ed eseguita una DFS su G
//PER OGNI coppia di vertici distinti V e U appartenenti al grafo

//U è un discendente di V nella Foresta Depth First 
//              SE E SOLO SE
//All'istante T_Scoperta [V] ESISTE un percorso in G fatto di soli vertici bianchi da V a U

//Tramite la DFS è possibile partizionare gli archi del grafo in 4 tipi:
//  -Archi dell'albero
//  -Archi all'indietro
//  -Archi in avanti
//  -Archi di attraversamento
void PartizionaArchi (struct Grafo * G, struct Vertice * S);
//In particolare, trovare archi all'indietro ci permette di individuare la presenza di cicli nel grafo.
bool Aciclico (struct Grafo * G);
bool Aciclico_Visit (struct Grafo * G, struct Vertice * S);

//Un ordinamento topologico è una relazione d'ordine totale, definita come segue:
//Per ogni arco del grafo, se l'arco è della forma (v, u), allora v precede u nell'ordinamento.

//TEOREMA: se G è aciclico, esiste almeno un ordinamento topologico di G

//Per costruire un ordinamento topologico, bisogna conoscere il grado entrante di tutti i vertici (cioé il numero di archi che vanno verso un vertice).
int * GradoEntrante (struct Grafo * G);
void OrdinamentoTopologico (struct Grafo * G);

//L'ordinamento inverso puó essere individuato dalla DFS 
void OrdinamentoTopologico_DFS (struct Grafo * G);

#endif
