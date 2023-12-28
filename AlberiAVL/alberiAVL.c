#include "stdio.h"
#include "stdlib.h"
#include "alberiAVL.h"

//L'inserimento è analogo alla versione su alberi binari di ricerca. Bisogna solo assicurarsi di bilanciare il sottoalbero modificato.
//Fa uso di due funzioni ausiliarie: BilanciaSX e BilanciaDX. 
//Le funzioni vengono chiamate a ogni chiamata ricorsiva, ma non hanno bisogno di effettuare operazioni dopo aver bilanciato l'albero la prima volta.
//Il tempo è lineare sull'altezza.
struct Tree * InsertAVL (struct Tree * T, TIPO k)
{
    if (T == NULL)
    {
        T = NewNodeAVL (k);
    }
    else
    {
        if (T->key < k)
        {
            T->right = InsertAVL (T->right, k);
            T = BilanciaDx (T);
        }
        else if (T->key > k)
        {
            T->left = InsertAVL (T->left, k);
            T = BilanciaSx (T);
        }
    }
    return T;
}

//I due algoritmi di bilanciamento fanno uso di funzioni ausiliarie di rotazione.
//Se la rotazione viene chiamata in caso di violazione, l’altezza dell’albero tornerá uguale a quella che aveva prima dell’inserimento.
//Segue che bisogna effettuare la rotazione solo sul nodo in cui è stata scoperta la violazione.
//Poiché le rotazioni hanno tempo costante, anche questi algoritmi hanno tempo costante.
struct Tree * BilanciaSx (struct Tree * T) 
{
    if (T != NULL)
    {
        if ((height(T->left) - height(T->right)) > 1) //Abbiamo inserito in T->left, quindi sará lui ad avere l'altezza piú grande
        {
            //Sappiamo giá che T->left sará diverso da Null
            if (height(T->left->left) > height(T->left->right)) //La violazione viene da un inserimento nel sottoalbero sinistro di T->left
            {
                T = RotazioneSx (T);
            }
            else  //La violazione viene da un inserimento nel sottoalbero destro di T->left
            {
                T->left = RotazioneDx (T->left); //In T->left, spostiamo il peso del sottoalbero destro in quello sinistro
                T = RotazioneSx (T); //Possiamo operare come nel caso precedente
            }
        }
        else //non c'è violazione
        {
            T->h = 1 + sup (height(T->left), height(T->right));
            return T;
        }
    }
}

struct Tree * BilanciaDx (struct Tree * T) 
{
    if (T != NULL)
    {
        if ((height(T->right) - height(T->left)) > 1)
        {
            if (height(T->right->right) > height(T->right->left))
            {
                T = RotazioneDx (T);
            }
            else 
            {
                T->right = RotazioneSx (T->right);
                T = RotazioneDx (T);
            }
        }
        else
        {
            T->h = 1 + sup (height(T->left), height(T->right));
            return T;
        }
    }
}

//Sposta il peso da sinistra a destra.
//Le proprietá di ordinamento sono rispettate.
//Tempo costante.
struct Tree * RotazioneSx (struct Tree * A)
{
    //A è la vecchia radice, B sará la nuova

    struct Tree * B = A->left; //B è il figlio sinistro di A 
    //Il valore di A è maggiore di quello di B

    A->left = B->right; //Il figlio destro di B diventa il figlio sinistro di A 
    //Ordine rispettato: ogni elemento del sottoalbero destro di B ha un valore compreso tra B e A

    B->right = A; //A diventa il figlio destro di B 
    //Ordine rispettato: i valori di A e di tutti i suoi figli sono piú grandi del valore di B
    
    A->h = 1 + sup(height (A->left), height (A->right));
    B->h = 1 + sup(height (B->left), height (B->right));
    
    return B;
}

struct Tree * RotazioneDx (struct Tree * A)
{
    struct Tree * B = A->right;
    A->right = B->left;
    B->left = A;
    
    A->h = 1 + sup(height (A->left), height (A->right));
    B->h = 1 + sup(height (B->left), height (B->right));
    
    return B;
}

//La cancellazione è analoga alla versione su alberi binari di ricerca. Ma bisogna assicurarsi che l'albero sia bilanciato.
//In questo caso non ci sono garanzie che una violazione non venga trasmessa al padre dopo un'operazione di bilanciamento.
//Dopo la cancellazione di un elemento, l'altezza dell'albero ruotato viene diminuita di 1.
//Quindi l'altezza non torna al valore precedente.
//Ne segue che le operazioni di bilanciamento potrebbero doversi ripetere a ogni chiamata ricorsiva.
//Nel caso peggiore, il numero di operazioni di bilanciamento necessarie sará lineare sull'altezza.
struct Tree * DeleteAVL (struct Tree * T, TIPO k)
{
    if (T != NULL)
    {
        if (k == T->key)
        {
            T = DeleteRootAVL(T); //l'operazione di bilanciamento viene fatta in DeleteRootAVL
        }
        else if (k > T->key) //cancello a destra
        {
            T->right = DeleteAVL (T->right, k);
            T = BilanciaSx (T); //il peso è a sinistra: BilanciaSx
        }
        else if (k < T->key) //cancello a sinistra
        {
            T->left = DeleteAVL (T->left, k);
            T = BilanciaDx (T); //il peso è a destra: BilanciaDx
        }
    }
    return T;
}

//L'unica differenza rispetto alla versione per alberi binari di ricerca è che bisogna bilanciare.
struct Tree * DeleteRootAVL (struct Tree * T)
{
        struct Tree * toDelete = T;

        if (T->left == NULL) 
        {   
            T = T->right;
        }
        else if (T->right == NULL) 
        {
            T = T->left;
        }
        else 
        {
            toDelete = StaccaMinAVL (T->right, T); //Ora T ha altezza ridotta!
            T->key = toDelete->key;
            //T->right = BilanciaDx (T->right); 
            //Questo è stato fatto in StaccaMinAVL
            T = BilanciaSx (T); //La violazione sul padre sará a sinistra perché abbiamo rimosso un elemento a destra
        }
        free (toDelete);
        toDelete = NULL;
        return T;
}

//In StaccaMin, bisogna bilanciare l'albero al ritorno di ogni chiamata ricorsiva.
//Gli algoritmi di bilanciamento possono cambiare la radice dell'albero.
//Occorre usare una variabile temporanea.
struct Tree * StaccaMinAVL (struct Tree * T, struct Tree * Pred)
{
    struct Tree * min = T;
    if (T != NULL)
    {
        if (T->left != NULL)
        {
            min = StaccaMinAVL (T->left, T); //salva il minimo in min e lo elimina da T
            T = BilanciaDx (T); //bilancia l'albero, riducendone l'altezza, e salva la nuova radice
        } 
        else 
        {
            min = T;
            if (Pred != NULL) 
            {
                if (min == Pred->left)
                {
                    Pred->left = min->right; 
                }
                else
                {  
                    Pred->right = min->right;
                }
            }
        }
    }
    return min;
}

struct Tree * NewNodeAVL (TIPO k)
{
    struct Tree * nuovo = (struct Tree *) malloc (sizeof(struct Tree));
    nuovo->key=k;
    nuovo->left=NULL;
    nuovo->right=NULL;
    nuovo->h=0;
    return nuovo;
}

int height (struct Tree * T){
    if (T == NULL)
    {
        return -1;
    }
    else
    {
        return T->h;
    }
}

unsigned int sup (unsigned int A, unsigned int B)
{
    if (A > B)
    {
        return A;
    }
    else
    {
        return B;
    }
}