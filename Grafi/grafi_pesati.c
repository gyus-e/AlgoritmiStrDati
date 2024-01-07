#include "grafi.h"
#include "stdio.h"

//La funzione Weight restituisce il peso di un arco. Per semplicitá quest'implementazione presuppone un grafo non pesato.
int Weight (struct Vertice * U, struct Vertice * W)
{
    return 1;
}

//Inizializza la distanza di S a 0 e quella degli altri vertici a infinito
void Init_Distance (struct Grafo * G, struct Vertice * S)
{   
    S->key = 0;
    Distance [S->key] = 0;
    for (int i = 1; i < G->V_Sz && G->V[i] != S; i++)
    {
        G->V[i]->key = i;
        Distance [G->V[i]->key] = infinity;
    }
}

//Dato un arco (U, V), cerca di trovare una stima migliore della distanza di U dalla sorgente S
void Relax (struct Vertice * U, struct Vertice * W)
{
    if (Distance [U->key] > (Distance [W->key] + Weight (U, W)))
    {
        Distance [U->key] = Distance [W->key] + Weight (U, W);
        Pred [U->key] = W;
    }
}

//L'algoritmo di Bellman-Ford trova la distanza di ogni vertice dalla sorgente e individua cicli negativi
//Tempo proporzionale al numero di vertici e al numero di archi: |V|*|E|
bool BellmanFord (struct Grafo * G, struct Vertice * S)
{
    Init_Distance (G, S);
    //ripetere V_sz - 1 volte: l'algoritmo rilassa piú volte gli stessi archi.
    //A ogni iterazione di questo ciclo, un vertice otterrá la stima corretta. 
    for (int i = 1; i < G->V_Sz - 1; i++) 
    {
        //per ogni arco del grafo (utilizzo due for)
        for (int k = 0; k < G->V_Sz; k++) 
        {
            struct Vertice * V = G->V[k];
            for (struct Vertice * U = V->next; U != NULL; U = U->next)
            {
                Relax (U, V);
            }
        }
    }
    //Adesso Distance contiene il peso dei percorsi minimi da S verso ogni vertice 

    //Individuare la presenza di cicli negativi
    //per ogni arco (V, U) del grafo
    for (int k = 0; k < G->V_Sz; k++)
    {
        struct Vertice * V = G->V[k];
        for (struct Vertice * U = V->next; U != NULL; U = U->next)
        {
            //Se la distanza di V dalla sorgente è maggiore della distanza di U piú il peso dell'arco
            if (Distance [V->key] > Distance [U->key] + Weight (U, V))
            {
                //allora esiste un ciclo a peso negativo che ha ridotto il valore della distanza di U
                return false;
            }
        }
    }
    return true;
}

struct Vertice * ExtractMin (struct Queue * Q, struct Vertice * S)
{
    int ret_weight = 0;
    struct Vertice * ret;
    for (struct Vertice * V = getHead(Q); Q != NULL; Q = getNext(Q))
    {
        if (Weight (S, V) < ret_weight)
        {
            ret_weight = Weight (S, V);
            ret = V;
        }
    }
    return ret;
}

//L'algoritmo di Dijkstra trova i percorsi minimi in grafi senza percorsi negativi.
void Dijkstra (struct Grafo * G, struct Vertice * S)
{
    Init_Distance (G, S);
    struct Stack * Stk = NULL;
    struct Queue * Q = fill (G); //riempie Q con tutti i vertici del grafo
    while (Q != NULL)
    {
        struct Vertice * U = ExtractMin (Q, S); //U è il vertice nella coda con distanza minore da S
        Stk = push (U);
        Q = delete (Q, U);
        for (struct Vertice * W = U->next; W != NULL; W = W->next) //per ogni vertice adiacente a U
        {
            Relax (U, W);
        }
    }
}