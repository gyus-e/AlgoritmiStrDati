/*
//Esame 19/11/2022

Si scriva un algoritmo ricorsivo che, dati in ingresso un albero  binario di ricerca T e un intero positivo k,
cancelli da T tutti i nodi che si trovano in posizioni multiple di k nell'ordinamento totale delle chiavi dell'albero.
Tale algoritmo dovrá essere efficiente e non far uso né di variabili globali dné di parametri passati per riferimento.
Infine, si scriva un algoritmo iterativo che simuli precisamente l'algoritmo ricorsivo di cui sopra.
*/

//Si assume che pos venga inizialmente passata uguale a 0;
Alg (T, k, pos)
{ 
    ret = pos;
    if (T != NULL)
    {
        //La visita a sinistra restituisce il numero di nodi precedenti a T
        ret = Alg (T->Sx, k, pos);

        //In order, si aggiorna la posizione di T
        pos = ret + 1;
        
        //La visita a destra fornisce il valore di ritorno per il padre di T, cioé
        //il numero di nodi precedenti di Pred (se T è il figlio sinistro)
        //il numero di nodi esplorati da Pred (se T è il figlio destro)
        ret = Alg (T->Dx, k, pos);
        
        //In post order, si cancella T
        if (pos % k == 0)
        {
            T = DeleteRoot (T);
        }
    }
    return ret;
}

Alg_Iterativo (T, k, pos)
{
    cT = T; 
    cpos = pos;
    stk_T = NULL;
    start = true;
    last = NULL;

    while (start || stk_T != NULL)
    {
        if (start)
        {
            ret = cpos;
            if (cT != NULL)
            {
                push (cT, stk_T);
                cT = cT->Sx;
            }
            else //caso base 
            {
                last = cT;
                start = false;
            }
        }
        else 
        {
            cT = top (stk_T);
            
           
            //Ponendo come condizione (last != cT->Dx), se sono in una foglia, l'if non viene eseguito perché last = cT->Dx = NULL
            //Alcune delle operazioni vanno eseguite anche se cT->Dx == NULL
            //Devo discriminare in un altro modo:
            if (last == cT->Sx) //Assumo che, se last == NULL, sto tornando da sinistra         
            {
                //queste operazioni vanno eseguite anche se cT->Dx == NULL
                cpos = ret + 1;
                //Devo scendere a destra se cT->Dx != NULL
                if (cT->Dx != NULL) 
                {
                    cT = cT->Dx;
                    start = true;
                }
                //Ora posso eseguire le istruzioni in post-order
                if (cpos % k == 0)
                {
                    cT = DeleteRoot (cT);
                    last = cT;
                    pop (stk_T);
                }
            }
            else //last != NULL
            {
                if (cpos % k == 0)
                {
                    cT = DeleteRoot (cT);
                    last = cT;
                    pop (stk_T);
                }
            }
        }
    }
}

DeleteRoot (T)
{
    if (T->Sx == NULL)
    {
        toDelete = T;
        T = T->Dx;
    } 
    else if (T->Dx == NULL)
    {
        toDelete = T;
        T = T->Sx;
    }
    else 
    {
        toDelete = StaccaMin (T->Dx, T);
        T->key = toDelete->key;
    }
    free (toDelete);
    return T;
}

StaccaMin (T, Pred)
{
    if (T->Sx != NULL)
    {
        return StaccaMin (T->Sx, T);
    }
    if (Pred != NULL)
    {
        if (T != Pred->Dx)
        {
            Pred->Sx = T->Dx;
        }
        else
        {
            Pred->Dx = T->Dx;
        }
    }
    return T;
}