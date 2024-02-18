/*
Si scriva un algoritmo che, dato in ingresso un grafo orientato G = (V, E),
verifichi in tempo lineare sulla dimensione del grafo se la seguente condizione è soddisfatta:
G contiene tre vertici distinti, di seguito denominati a, b e c tali che:
-a e b sono entrambi raggiungibili da c;
-a e c sono entrambi raggiungibili da b;
-b e c sono entrambi raggiungibili da a;
Notare che i vertici a, b e c non sono input del problema.
*/

//a, b e c sono mutualmente raggiungibili: appartengono a una componente fortemente connessa.
Trasposto (G)
{
    G_tr = (V, E_tr);
    for each v in G.V
    {
        for each u in G.Adj[v]
        {
            Insert (G_tr.Adj[u], v);
        }
    }
    return G_tr;
}

Init (G)
{
    for each v in G.V 
    {
        color [v] = white;
    }
}

DFS (G)
{
    Init (G);
    DF_Forest = NULL;

    for each s in G.V 
    {
        if (color [s] == white)
        {   
            DF_Tree = DFS_Visit (G, s);
            push (DF_Forest, DF_Tree);
        }
    }
    return DF_Forest;
}

DFS_Visit (G, s)
{
    color [s] = gray;

    DF_Tree = NULL;
    for each v in G.Adj[s]
    {
        if (color [v] == white)
        {
            DF_Tree = DFS_Visit (G, v);
        }
    }
    push (DF_Tree, s);

    color [s] = black;
    return DF_Tree;
}

//bisogna solo trovare una componente fortemente connessa con tre vertici distinti
//Il controllo si puó fare in DFS_Visit_Trasposto, guardando se nella stessa CFC ci sono 3 vertici, restituendo immediatamente true in tal caso.
//Questo algoritmo sará quindi una versione modificata di ComponentiFortementeConnesse (G)

Algoritmo (G)
{
    
    DF_Forest = DFS (G);
    G_tr = Trasposto (G);
    ret = DFS_Algoritmo (G_tr, DF_Forest);
    return ret;
}

DFS_Algoritmo (G_tr, DF_Forest)
{
    Init (G_tr);
    while (DF_Forest != NULL)
    {
        DF_Tree = top (DF_Forest);
        pop (DF_Forest);
        s = top (DF_Tree);

        if (color [s] == white)
        {
            ret = DFS_Visit_Algoritmo (G_tr, s, 0);
            if (ret == true)
            {
                return ret;
            }
        }
    }
}

DFS_Visit_Algoritmo (G_tr, s, counter)
{
    if (counter == 3)
    {
        return true;
    }
    else 
    {
        color [s] = gray;

        for each v in G_tr.Adj [s]
        {
            if (color [v] == white)
            {
                counter ++;
                ret = DFS_Visit_Algoritmo (G_tr, v, counter);
            }
        }

        color [s] = black;
        return ret;
    }
}