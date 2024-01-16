#ifndef GRAFI_H_
#define GRAFI_H_

typedef int TIPO;

#define infinity 999999999

//I vertici non visitati sono bianchi. I vertici in coda sono grigi. I vertici visitati sono neri.
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
    struct Vertice ** V; //Array contenente tutti i vertici.
    int V_Sz; //numero di vertici.
};

char * Color; //Array che associa a ogni vertice un colore
int * Distance; //Array che associa a ogni vertice la sua distanza dalla sorgente. Nei grafi pesati, la distanza è il peso del percorso minimo.
struct Vertice ** Pred; //Array che associa a ogni vertice il suo predecessore

unsigned int tempo = 0;
int * T_Scoperta; //Array che associa a ogni vertice il momento in cui è stato scoperto.
int * T_Fine; //Array che associa a ogni vertice il momento in cui sono stati esplorati tutti i suoi vertici adiacenti.


void Init_BFS (struct Grafo * G); //Inizializza Color e D.
void BFS (struct Grafo * G, struct Vertice * S); //Breadth First Search: Visita in ampiezza. S è il vertice sorgente.

void StampaPercorsoMinimo (struct Grafo * G, struct Vertice * S, struct Vertice * x);

void Init_DFS (struct Grafo * G);
struct Stack ** DFS (struct Grafo * G);
struct Stack * DFS_Visit (struct Grafo * G, struct Vertice * S);
//ogni volta che chiama DFS_Visit su un vertice sorgente, questo restituisce un albero che contiene tutti i nodi raggiungibili dalla sorgente
//L'insieme di tutti gli alberi generati da una DFS si chiama foresta depth-first.

/////////////////////////////////////////////////////////////////////////////////////////////////
//TEOREMA DELLA STRUTTURA A PARENTESI:

//Dato un grafo G, e dati due vertici V e U appartenenti al grafo
//Al termine di una visita DFS sará possibile UNA SOLA delle seguenti:

//il tempo di visita di un vertice è contenuto nel tempo di visita dell'altro
//  1) T_Scoperta [V] < T_Scoperta [U] < T_Fine [U] < T_Fine [V]
//  2) T_Scoperta [U] < T_Scoperta [V] < T_Fine [V] < T_Fine [U]

//i tempi di visita dei due vertici sono disgiunti
//  3) T_Scoperta [V] < T_Fine [V] < T_Scoperta [U] < T_Fine [U]
//  4) T_Scoperta [U] < T_Fine [U] < T_Scoperta [V] < T_Fine [V]
/////////////////////////////////////////////////////////////////////////////////////////////////
//TEOREMA DEL PERCORSO BIANCO:

//Dato un grafo G, ed eseguita una DFS su G
//PER OGNI coppia di vertici distinti V e U appartenenti al grafo

//U è un discendente di V in un albero della foresta depth-first 
//              SE E SOLO SE
//All'istante T_Scoperta [V] ESISTE un percorso in G fatto di soli vertici bianchi da V a U
/////////////////////////////////////////////////////////////////////////////////////////////////

//Tramite la DFS è possibile partizionare gli archi del grafo in 4 tipi:
//  -Archi di alberi della foresta depth-first
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
struct Stack * OrdinamentoTopologicoDFS_Visit (struct Grafo * G, struct Vertice * W, struct Stack * S);

//Un grafo si dice connesso se non ha vertici isolati
//Un grafo si dice fortemente connesso se tutti i vertici sono reciprocamente raggiungibili

//La raggiungibilitá reciproca è una relazione di equivalenza (riflessiva, simmetrica e transitiva). 
//La raggiungibilitá semplice potrebbe non essere simmetrica.
//Le coppie in relazione di raggiungibilitá reciproca formano un sottoinsieme di quelle in relazione di raggiungibilitá semplice.

//Un grafo non (fortemente) connesso può avere sottografi (fortemente) connessi
//Una componente (fortemente) connessa di un grafo è un sottografo (fortemente) connesso massimale 

//Dati due vertici U e V, 
//U è raggiungibile da V 
//      SE E SOLO SE 
//Esiste un percorso tra un vertice nella componente connessa di U e uno nella componente connessa di V.

//Il problema della raggiungibilità tra due vertici può essere ricondotto al problema della raggiungibilità tra le loro componenti connesse

//Grafo delle componenti (fortemente) connesse: 
//  Ha un vertice per ogni componente connessa
//  Gli archi sono solo quelli che attraversano diverse componenti connesse

//Il grafo delle componenti (fortemente) connesse è sempre aciclico.

//TEOREMA: se due vertici appartengono alla stessa componente connessa, ogni percorso tra i due non esce mai dalla componente connessa.
//TEOREMA: se due vertici appartengono alla stessa componente connessa, allora apparterranno allo stesso albero nella foresta depth-first

//In un grafo non orientato, ogni albero della foresta depth-first è una componente connesa.
//In un grafo orientato, un albero può contenere più componenti connesse.

//Per identificare una componente fortemente connessa, basta capire quali vertici in un albero raggiungono la sua radice.
//Per trovarle tutte, richiamo l'algoritmo sullo stesso albero rimuovendo i vertici di cui ho giá trovato la componente connessa.
 
//Per capire quali vertici in un albero raggiungono la sua radice, effettuo una DFS sul grafo trasposto (ottenuto cambiando il verso degli archi).
//Ogni vertice raggiunto dalla sorgente nel grafo trasposto, raggiunge la sorgente nel grafo di partenza.
//Le componenti fortemente connesse del grafo trasposto sono le stesse del grafo di partenza.
struct Grafo * Trasposto (struct Grafo * G);
//Usiamo una DFS sul grafo trasposto che seleziona le sorgenti in modo da restituire esattamente un albero per ogni componente fortemente connessa.
struct Stack ** DFS_trasposto (struct Grafo * G_trasposto, struct Stack ** Foresta_DF);
struct Stack * DFS_trasposto_visit (struct Grafo * G_trasposto, struct Vertice * S);

struct Stack ** ComponenteFortementeConnessa (struct Grafo * G);

#endif
