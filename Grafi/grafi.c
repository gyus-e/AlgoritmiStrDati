#include "grafi.h"
#include "queue_grafi.h"
#include "stack_grafi.h"
#include "stdio.h"

void Init_BFS (struct Grafo * G)
{
    Color = (char) malloc (G->V_Sz * sizeof(char));
    Distance = (int) malloc (G->V_Sz * sizeof (int));
    Pred = (struct Vertice *) malloc (G->V_Sz * sizeof (struct Vertice *));

    for (int i = 0; i < G->V_Sz; i++) //per ogni vertice del grafo
    {
        G->V[i]->key = i;
    
        Color [i] = white;
        Distance [i] = infinity;
    }
}

//Similmente alla BFS per gli alberi, sfrutta una coda. Ma deve poter riconoscere i vertici giá visitati.
//Partendo da un vertice sorgente, aggiunge tutti i vertici adiacenti bianchi a una coda, settando il loro colore a grigio.
//Poi setta il colore della sorgente a nero e la rimuove dalla coda.
//Ripete l'operazione sul prossimo vertice in coda, finché la coda non si svuota.
//Costo lineare sulla dimensione del grafo (vertici + archi)
void BFS (struct Grafo * G, struct Vertice * S)
{
    Init_BFS (G);
    struct Queue * Q = enqueue (Q, S);
    Color [S->key] = gray;
    Distance [S->key] = 0; //La sorgente ha distanza 0 da se stessa.

    while (Q != NULL)
    {
        struct Vertice * U = getHead (Q);
        for (struct Vertice * W = U->next; W != NULL; W = W->next) //per ogni vertice adiacente a U
        {
            if (Color [W->key] == white)
            {
                Q = enqueue (Q, W);
                Color [W->key] = gray;
                Distance [W->key] = Distance [U->key] + 1; //La distanza di un vertice adiacente che non è ancora stato visitato sará 1 + la distanza del vertice che stiamo visitando
                Pred [W->key] = U; //viene salvato un predecessore
            }
        }
        Q = dequeue (Q);
        Color [U->key] = black;
    }
}

//Dopo una BFS, l'array dei predecessori permetterá di trovare un percorso minimo tra la sorgente e un vertice.
void StampaPercorsoMinimo (struct Grafo * G, struct Vertice * S, struct Vertice * x)
{
    if (x != S)
    {
        PercorsoMinimo (G, S, Pred [x->key]);
    }
    printf ("%d \n", x->val);
}

void Init_DFS (struct Grafo * G)
{
    Pred = (struct Vertice *) malloc (G->V_Sz * sizeof (struct Vertice *));
    T_Scoperta = (int) malloc (G->V_Sz * sizeof (int));
    T_Fine = (int) malloc (G->V_Sz * sizeof (int));
    
    for (int i = 0; i < G->V_Sz; i++) //per ogni vertice del grafo
    {
        G->V[i]->key = i;

        Color[i] = white;
        Pred[i] = NULL;
    }
    tempo = 1;
}

//Costo lineare sulla dimensione del grafo (vertici + archi)
struct Stack * DFS (struct Grafo * G)
{
    struct Stack * DFS_Forest = NULL;
    
    Init_DFS (G);

    for (int i = 0; i < G->V_Sz; i++) //per ogni vertice del grafo
    {
        if (Color[i] == white) //se non è stato visitato
        {
            DFS_Forest = DFS_Visit (G, G->V[i]); //DFS_Visit sul vertice
        }
    }

    return DFS_Forest;
}

struct Stack * DFS_Visit (struct Grafo * G, struct Vertice * S)
{
    struct Stack * DFS_Tree = NULL;
    Color [S->key] = gray; //la visita sul vertice è in corso

    for (struct Vertice * W = S->next; W != NULL; W = W->next) //per ogni vertice adiacente a S
    {
        if (Color [W->key] == white) //se il vertice non è stato visitato
        {
            Pred[W->key] = S; //salva il predecessore
            DFS_Tree = DFS_Visit (G, W, DFS_Tree); //effettua la visita sul vertice
        }
    }
    DFS_Tree = push (DFS_Tree, S); //Terminata l'esplorazione della sorgente, la inserisce nello Stack

    Color [S->key] = black; //la visita sul vertice è terminata

    return DFS_Tree; //Lo stack è un albero della Foresta Depth-First: contiene in cima la sorgente, e a seguire i nodi esplorati a partire da essa.
}

//Esempio di DFS. Salviamo il tempo di scoperta e di fine visita di ogni vertice in due array.
void PartizionaArchi (struct Grafo * G, struct Vertice * S)
{
    Color [S->key] = gray;
    T_Scoperta [S->key] = tempo++; //Salva il momento in cui la visita su S è iniziata. La variabile tempo va incrementata ogni volta che viene utilizzata.

    for (struct Vertice * W = S->next; W != NULL; W = W->next) //per ogni vertice adiacente a S
    {
        if (Color [W->key] == white) //W viene visitato per la prima volta partendo da S
        {
            Pred[W->key] = S;
            printf("(%d, %d) Arco dell'albero.\n", S->val, W->val); //l'arco (S, W) si troverá in un albero Depth-First.

            PartizionaArchi (G, W);
        }
        else 
        {
            if (Color [W->key] == gray) //La visita su W è rimasta in sospeso
            {
                printf("(%d, %d) Arco all'indietro.\n", S->val, W->val); //Sono arrivato a S partendo da W, e ora ritorno a W: esistono cicli.
            }

            //Nei casi successivi W è nero, la visita su di esso è giá terminata.
            else if (T_Scoperta [S->key] < T_Scoperta [W->key]) //Se S è stato scoperto prima di W
            {
                printf("(%d, %d) Arco in avanti.\n", S->val, W->val); //W è giá stato scoperto da un vertice successivo a S, l'arco (S, W) salterebbe un livello dell'albero.
            }
            else //Se W è stato scoperto prima di S
            {
                printf("(%d, %d) Arco di attraversamento.\n", S->val, W->val); //L'arco (S, W) attraversa due diversi alberi Depth-First.
            }
        }   
    }
    
    T_Fine [S->key] = tempo++; //Salva il momento in cui la visita su S è terminata.
    Color [S->key] = black;
}

//Altro esempio di DFS
bool Aciclico (struct Grafo * G)
{
    Init_DFS (G);
    for (int i = 0; i < G->V_Sz; i++) //per ogni vertice del grafo
    {
        if (Color[i] == white)
        {
            if (Aciclico_Visit (G, G->V[i]) == false)
            {
                return false;
            }
        }
    }
    return true;
}

bool Aciclico_Visit (struct Grafo * G, struct Vertice * S)
{
    bool ret = true;
    Color [S->key] = gray;

    for (struct Vertice * W = S->next; W != NULL; W = W->next) //per ogni vertice adiacente a S
    {
        if (Color [W->key] == white) //W viene visitato per la prima volta partendo da S
        {
            ret = Aciclico_Visit (G, W);
        }
        else 
        {
            if (Color [W->key] == gray) //La visita su W è rimasta in sospeso
            {
                ret = false; //Sono arrivato a S partendo da W, e ora ritorno a W: esistono cicli.
            }
            //Se W è nero, non ci sono cicli perché W non ha raggiunto S 
        } 
    }
    Color [S->key] = black;
    return ret;
}

int * GradoEntrante (struct Grafo * G)
{
    int * GE = (int) malloc (G->V_Sz * sizeof (int));
    //inizializzazione array
    for (int i = 0; i < G->V_Sz; i++)
    {
        GE[i] = 0;
    }
    //calcolo grado entrante
    for (int j = 0; j < G->V_Sz; j++) //per ogni vertice del grafo
    {
        struct Vertice * J = G->V[j];
        for (struct Vertice * U = J->next; U != NULL; U = U->next) //per ogni vertice adiacente a J
        {
            GE[U->key]++; //ogni volta che trovo U, incremento il suo grado entrante di 1
        }
    }
    return GE;
}

//Se un grafo è aciclico, esisterá almeno un vertice con grado entrante 0. Questo sará il primo vertice dell'ordinamento.
//Togliendo quel vertice, il risultato sará un sottografo aciclico con un nuovo vertice di grado entrante 0.
void OrdinamentoTopologico (struct Grafo * G)
{
    int * GE = GradoEntrante (G);
    struct Queue * Q = NULL;
    
    for (int i = 0; i < G->V_Sz; i++) //per ogni vertice dell'albero
    {
        if (GE[i] == 0)
        {
            Q = enqueue (Q, G->V[i]); //accoda i vertici con grado entrante 0
        }
    }

    while (Q != NULL)
    {
        struct Vertice * W = getHead (Q);
        printf("%d\n", W->val);
        for (struct Vertice * U = W->next; U != NULL; U = U->next) //per ogni vertice adiacente a W
        {
            GE[U->key]--; //riduci il grado entrante
            if (GE[U->key] == 0)
            {
                Q = enqueue (Q, U); //se è arrivato a 0, accoda
            }
        }
        Q = dequeue (Q);
    }
}

void OrdinamentoTopologicoDFS (struct Grafo * G)
{
    Init_DFS (G);
    struct Stack * S = NULL;
    for (int i = 0; i < G->V_Sz; i++) //per ogni vertice del grafo
    {
        if (Color[i] == white)
        {
            S = OrdinamentoTopologicoDFS_Visit (G, G->V[i], S);
        }
    }
    PrintStack (S);
}

struct Stack * OrdinamentoTopologicoDFS_Visit (struct Grafo * G, struct Vertice * W, struct Stack * S)
{
    Color [W->key] = gray;
    T_Scoperta [W->key] = tempo++;
    for (struct Vertice * U = W->next; U != NULL; U = U->next) //per ogni vertice adiacente a W
    {
        if (Color [U->key] == white)
        {
            S = OrdinamentoTopologicoDFS_Visit (G, U, S);
        }
    }
    Color [W->key] = black;
    S = push (S, W);
    T_Fine [W->key] = tempo++;
    return S;
}

//Per identificare una componente fortemente connessa, basta capire quali vertici in un albero raggiungono la sua radice.
//Per trovarle tutte, richiamo l'algoritmo sullo stesso albero rimuovendo i vertici di cui ho giá trovato la componente connessa.
 
//Per capire quali vertici in un albero raggiungono la sua radice, effettuo una DFS sul grafo trasposto (ottenuto cambiando il verso degli archi).
//Ogni vertice raggiunto dalla sorgente nel grafo trasposto, raggiunge la sorgente nel grafo di partenza.
//Le componenti fortemente connesse del grafo trasposto sono le stesse del grafo di partenza.

struct Grafo * Trasposto (struct Grafo * G)
{
    //copia dei vertici in un nuovo array per il grafo trasposto
    struct Vertice ** v_trasposto = malloc (G->V_Sz * sizeof(struct Vertice *)); 
    for (int i = 0; i < G->V_Sz; i++) //per ogni vertice nel grafo
    {
        v_trasposto [i] = G->V[i];
    }
    //Inversione degli archi
    for (int i = 0; i < G->V_Sz; i++) //per ogni vertice nel grafo
    {
        for (struct Vertice * U = G->V[i]->next; U != NULL; U = U->next) //per ogni U raggiunto da i
        {
            v_trasposto [U->key]->next = G->V[i]; //U raggiungerá i
        }
    }
    
    struct Grafo * G_trasposto;
    G_trasposto->V = v_trasposto;
    G_trasposto->V_Sz = G->V_Sz;

    return G_trasposto;
}

//Usiamo una DFS sul grafo trasposto che seleziona le sorgenti in modo da restituire esattamente un albero per ogni componente fortemente connessa.

struct Stack ** DFS_trasposto (struct Grafo * G_trasposto, struct Stack * Foresta_DF)
{
    struct Stack * CFC_Graph = NULL;
    Init_DFS (G_trasposto);

    for (int i = 0; Foresta_DF [i] != NULL; i++) //Le sorgenti sono selezionate nell'ordine in cui appaiono nella foresta depth-first
    {
        struct Vertice * S = top (Foresta_DF);
        Foresta_DF = pop (Foresta_DF);
        if (Color [S->key] == white)
        {
            //Nello stack vengono salvati i vertici raggiunti dalla sorgente nel trasposto (quindi quelli che raggiungono la sorgente nel grafo di partenza)
            //Ma poiché sono selezionati in ordine inverso, resteremo sempre nello stesso albero, radicato nella sorgente.
            //Quindi tutti i nodi trovati saranno mutualmente raggiungibili, formando una componente fortemente connessa. 
            CFC_Graph = DFS_trasposto_visit (G_trasposto, S); 
        }
    }
    
    return CFC_Graph;
}

struct Stack * DFS_trasposto_visit (struct Grafo * G_trasposto, struct Vertice * S)
{
    struct Stack * CFC = NULL;
    Color [S->key] = gray;
    for (struct Vertice * U = S->next; U != NULL; U = U->next) //per ogni vertice adiacente a S
    {
        if (Color [U->key] == white)
        {
            Pred [U->key] = S;
            CFC = DFS_trasposto_visit (G_trasposto, U);
        }
    }
    CFC = push (CFC, S);
    return CFC;
}

struct Stack ** ComponenteFortementeConnessa (struct Grafo * G)
{
    struct Stack ** Foresta_DF = DFS (G); //DFS mi restituisce la foresta depth first
    struct Grafo * G_trasposto = Trasposto (G);
    struct Stack ** CFC_Graph = DFS_trasposto (G_trasposto, Foresta_DF); //DFS sul grafo trasposto restituisce le componenti connesse
    return CFC_Graph;
}