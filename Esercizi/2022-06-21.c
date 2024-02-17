/*
Si scriva un algoritmo ricorsivo che, dati in ingresso un albero binario di ricerca su interi T
e due valori k1, k2 appartenenti a N,
inserisca in una lista L le chiavi k contenute in T comprese tra k1 e k2 (k1 <= k <= k2),
in modo che al termine L contenga valori ordinati in modo decrescente.
Tale algoritmo dovrá avere complessitá lineare nella dimensione dell'albero.
Infine si scriva un algoritmo iterativo che simuli precisamente l'algoritmo di cui sopra.
*/

ALG (T, k1, k2)
{
    if (T != NULL)
    {
        //scendo a destra per trovare il massimo
        ALG (T->Dx, k1, k2);

        //visita in order
        if (k1 <= T->k && T->k <= k2)
        {
            L = Insert (L, T->k);
        }

        //prima di risalire scendo a sinistra
        ALG (T->Sx, k1, k2);
    }
}

ALG_ITERATIVO (T, k1, k2)
{
    cT = T;
    stack_T = NULL;
    start = true;
    last = NULL;

    while (start || stack_T != NULL)
    {
        if (start)
        {
            if (T != NULL)
            {
                push (stack_T, cT);
                cT = cT->Dx;
            }
            else 
            {
                start = false;
                last = cT;
            }
        }
        else 
        {
            cT = top (stack_T);

            if (last != cT->Sx )
            {
                if (k1 <= cT->k && cT->k <= k2)
                {
                    L = Insert (L, cT->k);
                }
                if (cT->Sx != NULL)
                {    
                    cT = cT->Sx;
                    start = true;
                }
            }
            else 
            {
                last = cT;
                pop (stack_T);
            }
        }
    }
}