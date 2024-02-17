/*
Sia dato un albero binario di ricerca T 
(i cui nodi contengono esclusivamente un campo chiave, un campo figlio sinistro e un campo figlio destro).
Il seguente algoritmo ricorsivo calcola la somma delle chiavi dispari in T:
*/

CountOdd (T)
{
    ret = 0;
    if (T != NULL)
    {
        if (T->key % 2 == 1)
        {
            ret = T->key;
        }
        rSx = CountOdd (T->Sx);
        rDx = CountOdd (T->Dx);
        ret = ret + rSx + rDx;
    }
    return ret;
}

/*
scrivere l'algoritmo iterativo CountOddIter (T) che simula precisamente il comportamento di CountOdd (T) sull'albero T
*/

CountOddIter (T)
{
    cT = T;
    stk_T = NULL;
    stk_ret = NULL;
    stk_rSx = NULL;
    
    ret, rSx, rDx;

    start = true;
    last = NULL;

    while (start || stk_T != NULL)
    {
        if (start)
        {
            ret = 0;
            if (cT != NULL)
            {
                if (cT->key % 2 == 1)
                {
                    ret = cT->key;
                }
                push (cT, stk_T);
                push (ret, stk_ret);
                cT = cT->Sx;
            }
            else 
            {
                last = cT;
                start = false;
            }
        }
        else 
        {
            cT = top (stk_T);
            //prima di recuperare il valore di ret della chiamata precedente, salvo il valore corrente del ret in rSx o rDx, a seconda che stia risalendo da sinistra o da destra
            
            if (last != cT->Dx && cT->Dx != NULL) 
            //se cT->Sx e cT->Dx sono entrambi Null, risalire da cT->Dx mi fará scendere di nuovo
            //In genere bisogna imporre che cT->Dx != cT->Sx, oppure aggiungere un controllo ulteriore
            //In questo caso basta controllare che cT->Dx != Null, infatti, se fosse Null, la chiamata ricorsiva non dovrebbe fare nulla
            {
                rSx = ret;
                ret = top (stk_ret);

                push (stk_rSx, rSx);

                cT = cT->Dx;
                start = true;
            }
            else 
            {
                rDx = ret;
                rSx = top (stk_rSx);
                ret = top (stk_ret);
                
                ret = ret + rSx + rDx;
                
                pop (stk_rSx);
                pop (stk_ret);
                pop (stk_T);
                last = cT;
            }
        }
    }
}