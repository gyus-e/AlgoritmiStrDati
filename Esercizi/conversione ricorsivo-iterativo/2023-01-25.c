Algoritmo (T, h)
{
    if (T == NULL)
    {
        return Z (0, h);
    }
    else 
    {
        a = 0;
        if (T->key % 2 == 0)
        {
            a = a + Algoritmo (T->dx, 2*h);
        }
        if (T->key % 3 == 1)
        {
            a = a - Algoritmo (T->sx, 3*h);
        }
        return Z (T->key, a);
    }
}

Algoritmo_Iterativo (T, h)
{
    cT = T;
    ch = h;

    stk_T = NULL;
    stk_a = NULL;
    
    last = NULL;
    start = true;

    while (start | stk_T != NULL)
    {
        if (start)
        {
            if (cT == NULL) //caso base 1
            {
                ret = Z (0, ch);

                last = cT;
                start = false;
            }
            else
            {
                a = 0;
                if (cT->key % 2 == 0) //prima chiamata
                {
                    push (stk_T, cT);
                    push (stk_a, a);

                    cT = cT->Dx;
                    ch = 2*ch;
                }
                else 
                {
                    if (cT->key % 3 == 1) //seconda chiamata
                    {
                        push (stk_T, cT);
                        push (stk_a, a);

                        cT = cT->Sx;
                        ch = 3*ch;
                    }
                    else //caso base 2
                    {
                        ret = Z (cT->key, a);

                        last = cT;
                        start = false;
                    }
                }
            }
        }
        else 
        {
            cT = top (stk_T);
            a = top (stk_a);
            //il valore di ch puó essere recuperato senza usare stack, dividendolo per 2 o per 3 a seconda della chiamata da cui si sta tornando

            //il valore corrente di a verrá sovrascritto o non verrá piú utilizzato
            pop (stk_a);

            if  (last != cT->Sx && cT->Sx != NULL) //torno dalla prima chiamata
            {
                ch = ch / 2; //recupero ch

                a = a + ret;

                if (cT->key % 3 == 1) //effettuo la seconda chiamata
                {
                    push (stk_a, a); //salvo il valore di a calcolato al ritorno dalla prima chiamata
                    cT = cT->Sx;
                    ch = 3*ch;

                    start = true;
                }
                else //risalgo senza effettuare la seconda chiamata
                {           
                    ret = Z (cT->key, a);

                    last = cT;
                    start = false;
                    pop (stk_T);
                }
                
            }
            else //torno dalla seconda chiamata
            {
                ch = ch / 3; //recupero ch

                a = a - ret;

                ret = Z (cT->key, a);

                last = cT;
                start = false;
                pop (stk_T);
            }
        }
    }
    return ret;
}