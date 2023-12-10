#include "stdio.h"
#include "stdlib.h"
#include "AlberiRB.h"

//Per non violare le proprietá dell'albero, coloreremo il nuovo nodo di rosso.
//In questo modo saremo certi di poter generare una violazione solo se il padre del nuovo nodo è rosso. (Cioé, se il padre è nero non dobbiamo preoccuparci di bilanciare l'altezza nera)
struct Tree * NewNode (TIPO k)
{
    struct Tree * T = malloc (sizeof (struct Tree));
    T->key = k;
    T->color = red;

    //i figli del nuovo nodo puntano al nodo Nil
    T->left = &Nil;
    T->right = &Nil;

    return T;
}


//Inserimento: analogo alla versione per alberi AVL.
//Il bilanciamento viene effettuato a ogni chiamata ricorsiva.
//Tempo lineare sull'altezza.
struct Tree * InsertRB (struct Tree * T, TIPO k)
{
    if (T == & Nil) //T punta al nodo Nil, siamo in una foglia
    {
        T = NewNode (k); //T ora punterá al nuovo nodo allocato
    }
    else
    {
        if (T->key < k)
        {
            T->right = InsertRB (T->right, k);
            T = BilanciaDx (T);
        }
        else if (T->key > k)
        {
            T->left = InsertRB (T->left, k);
            T = BilanciaSx (T);
        }
    }
    return T;
}

//L'algoritmo di bilanciamento prevede tre casi diversi.
//Usa una funzione ausiliaria per determinare quello su cui operare, oltre alle due funzioni di rotazione.
struct Tree * BilanciaSx (struct Tree * T)
{
    switch (ViolazioneSx (T)) //Se si accorge di una violazione, allora T è nero
    {
        case 1: //T->left e T->right sono rossi e uno dei figli di T->left è rosso
        //Soluzione: Colora T di rosso e i suoi figli di nero. L'altezza nera di ogni nodo non cambia e le proprietá sono rispettate.
        T->color = red;
        T->left->color = black;
        T->right->color = black;
        break;

        //nei casi 2 e 3, T->right è nero
        case 2: //T->left è rosso e il suo figlio sinistro è rosso (il destro sará per forza nero)
        T = RotazioneSx (T); //T, nero, viene sostituito dal figlio sinistro, rosso
        T->color = black;
        //ora il figlio destro è la vecchia radice, nera, e va colorato di rosso per preservare l'altezza nera
        T->right->color = red; 
        //Possiamo colorare il nuovo T->right di rosso perché i suoi figli saranno:
        //* Il vecchio T->right (nero, perché altrimenti saremmo nel caso 1);
        //* Il vecchio T->left->right (nero, perché altrimenti avremmo piú di una violazione).
        break;
        
        case 3: //T->left è rosso e il suo figlio destro è rosso (il sinistro sará per forza nero)
        T->left = RotazioneDx (T->left); //Ci riconduce al caso 2
        T = RotazioneSx (T);
        T->color = black;
        T->right->color = red;
        break;
    }

    return T;
}

//Restituisce un numero diverso a seconda del tipo di violazione.
//La violazione è solo del tipo: nodo rosso con un figlio rosso.
//Un inserimento genera al piú una violazione.
//Il nodo che si accorge della violazione è sempre nero.
//Il tempo è costante.
int ViolazioneSx (struct Tree * T)
{
    int violazione = 0;
    struct Tree * L = T->left; //Abbiamo inserito a sinistra, quindi la violazione è a sinistra.
    if (L->color == red) //La violazione c'è solo se L è rosso e ha un figlio rosso.
    //Poiché la violazione sará al piú una, non avrá mai entrambi i figli rossi.
    //Se L è rosso e ha un figlio rosso, T sará nero (altrimenti ci sarebbe piú di una violazione).
    {   
        //Caso 1: T->right (il "fratello" di L) è rosso.
        if (T->right->color == red)
        {
            if (L->left->color == red || L->right->color == red) //uno qualsiasi dei figli di L è rosso
            {
                violazione = 1;
            }
        }
        else //T->right è nero: due casi diversi a seconda di quale figlio di L è rosso.
        {
            //Caso 2:
            if (L->left->color == red)
            {
                violazione = 2;
            }
            //Caso 3:
            else if (L->right->color == red)
            {   
                violazione = 3;
            }
        }
    }
    //Se L è nero, oppure L è rosso ma ha solo figli neri, non c'è nessuna violazione.
    return violazione;
}


struct Tree * BilanciaDx (struct Tree * T)
{
    switch (ViolazioneDx (T))
    {
        case 1: //T->right e T->left sono rossi, uno dei figli di T->right è rosso
        T->color = red;
        T->left->color = black;
        T->right->color = black;
        break;

        case 2: //T->right e il suo figlio destro sono rossi
        T = RotazioneDx (T);
        T->color = black;
        T->left->color = red; 
        break;
        
        case 3: //T->right e il suo figlio sinistro sono rossi
        T->right = RotazioneSx (T->left); //Ci riconduce al caso 2
        T = RotazioneDx (T);
        T->color = black;
        T->left->color = red;
        break;
    }

    return T;
}

int ViolazioneDx (struct Tree * T)
{
    int violazione = 0;
    struct Tree * R = T->right; //Abbiamo inserito a destra, quindi la violazione è a destra.
    if (R->color == red)
    {   
        //Caso 1:
        if (T->left->color == red)
        {
            if (R->left->color == red || R->right->color == red) //uno qualsiasi dei figli di R è rosso
            {
                violazione = 1;
            }
        }
        else
        {
            //Caso 2:
            if (R->right->color == red)
            {
                violazione = 2;
            }
            //Caso 3:
            else if (R->left->color == red)
            {
                violazione = 3;
            }
        }
    }
    //Se L è nero, oppure L è rosso ma ha solo figli neri, non c'è nessuna violazione.
    return violazione;
}

//Le funzioni di rotazione sono analoghe alla versione per alberi AVL.
//Il cambio dei colori viene gestito dalla funzione di bilanciamento.
struct Tree * RotazioneSx (struct Tree * A)
{
    struct Tree * B = A->left; 
    A->left = B->right; 
    B->right = A; 
        
    return B;
}

struct Tree * RotazioneDx (struct Tree * A)
{
    struct Tree * B = A->right;
    A->right = B->left;
    B->left = A;
        
    return B;
}