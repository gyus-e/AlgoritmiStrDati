/*
Si scriva un algoritmo ricorsivo che, dati in ingresso un albero binario T contenente numeri interi e due numeri naturali l1 <= l2,
restituisca la somma dei valori d di tutti quei nodi con d pari e la cui profonditá p non sia compresa tra l1 e l2.
Tale algoritmo dovrà essere efficiente e non far uso né di variabili globali, né di parametri passati per riferimento.
Si scriva infine un algoritmo iterativo che simuli precisamente l'algoritmo ricorsivo di cui sopra.
*/

ALG (T, l1, l2, p)
{
    ret = 0;
    if (T != NULL)
    {
        ret += ALG (T->Sx, l1, l2, p+1);
        ret += ALG (T->Dx, l1, l2, p+1);
        if ((T->d % 2 == 0) && !(l1 <= p && p <= l2))
        {
            ret += T->d;
        }
    }
    return ret;
}

ALG_ITERATIVO (T, l1, l2, p)
{
    cT = T; cp = p; ret = 0;
    //stack_ret = NULL;
    stack_T = NULL;
    last = NULL;
    start = true;

    while (start || stack_T != NULL)
    {
        if (start)
        {
            //ret = 0;
            if (cT != NULL)
            {
                //push (stack_ret, ret);
                push (stack_T, cT);
                cT = cT->Sx;
                cp = cp + 1;
            }
            else 
            {
                start = false;
                last = cT;
            }
        }
        else 
        {
            //ret += pop (stack_ret);
            cT = pop (stack_T);
            cp = cp - 1;
            if (last != cT->Dx && cT->Dx != NULL) //bisogna controllare che cT->Dx non sia NULL per fare la chiamata a destra
            {
                //push (stack_ret, ret);
                push (stack_T, cT);
                cT = cT->Dx;
                cp = cp + 1;
                start = true;
            }
            else 
            {
                if ((T->d % 2 == 0) && !(l1 <= p <= l2))
                {
                    ret += T->d;
                    last = cT;
                }
            }
        }
    }
    return ret;
}