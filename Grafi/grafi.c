#include "grafi.h"
#include "queue_grafi.h"
#include "stdio.h"

void Init_BFS (struct Grafo * G)
{
    Color = (char) malloc (G->V_Sz * sizeof(char));
    Distance = (int) malloc (G->V_Sz * sizeof (int));
    Pred = (struct Vertice *) malloc (G->V_Sz * sizeof (struct Vertice *));

    for (int i = 0; i < G->V_Sz; i++) //per ogni vertice del grafo
    {
        G->v[i]->key = i;
    
        Color [i] = white;
        Distance [i] = infinity;
    }
}

//I vertici non visitati sono bianchi. I vertici in coda sono grigi. I vertici visitati sono neri.
//Aggiunge tutti i vertici adiacenti bianchi a una coda, settando il loro colore a grigio
//Poi setta il colore del vertice visitato a nero e lo rimuove dalla coda.
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
        G->v[i]->key = i;

        Color[i] = white;
        Pred[i] = NULL;
    }
    tempo = 1;
}

//Costo lineare sulla dimensione del grafo (vertici + archi)
void DFS (struct Grafo * G)
{
    Init_DFS (G);
    for (int i = 0; i < G->V_Sz; i++) //per ogni vertice del grafo
    {
        if (Color[i] == white)
        {
            DFS_Visit (G, G->v[i]); //DFS_Visit sul vertice
        }
    }
}

//Opzionalmente, salviamo il tempo di scoperta e di fine visita di ogni vertice in due array, e l'array dei predecessori. 
void DFS_Visit (struct Grafo * G, struct Vertice * S)
{
    Color [S->key] = gray;
    T_Scoperta [S->key] = tempo++; //Salva il momento in cui la visita su S è iniziata. La variabile tempo va incrementata ogni volta che viene utilizzata.

    for (struct Vertice * W = S->next; W != NULL; W = W->next) //per ogni vertice adiacente a S
    {
        if (Color [W->key] == white) //se il vertice non è stato visitato
        {
            Pred[W->key] = S; //salva il predecessore
            DFS_Visit (G, W); //effettua la visita sul vertice
        }
    }

    T_Fine [S->key] = tempo++; //Salva il momento in cui la visita su S è terminata.
    Color [S->key] = black;
}

//Esempio di DFS
void PartizionaArchi (struct Grafo * G, struct Vertice * S)
{
    Color [S->key] = gray;
    T_Scoperta [S->key] = tempo++;

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
    
    T_Fine [S->key] = tempo++;
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
            if (Aciclico_Visit (G, G->v[i]) == false)
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
        struct Vertice * J = G->v[j];
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
            Q = enqueue (Q, G->v[i]); //accoda i vertici con grado entrante 0
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
