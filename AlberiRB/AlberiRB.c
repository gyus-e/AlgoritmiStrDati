#include "stdio.h"
#include "stdlib.h"
#include "AlberiRB.h"

//Per non violare le proprietá dell'albero, coloreremo il nuovo nodo di rosso.
//In questo modo saremo certi di poter generare una violazione solo se il padre del nuovo nodo è rosso. (Cioé, se il padre è nero non dobbiamo preoccuparci di bilanciare l'altezza nera)
struct Tree * NewNodeRB (TIPO k)
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
        T = NewNodeRB (k); //T ora punterá al nuovo nodo allocato
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
    //Se R è nero, oppure R è rosso ma ha solo figli neri, non c'è nessuna violazione.
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

//Cancellazione: analoga alla versione per alberi AVL
//Stavolta bisogna bilanciare dallo stesso lato in cui si è fatta la cancellazione, perché è lí che troveremo la violazione (nodo doppio nero).
struct Tree * DeleteRB (struct Tree * T, TIPO k)
{
    if (T != & Nil)
    {
        if (k == T->key)
        {
            T = DeleteRootRB(T); //l'operazione di bilanciamento viene fatta in DeleteRootRB
        }
        else if (k > T->key) //cancello a destra
        {
            T->right = DeleteRB (T->right, k);
            T = BilanciaDx (T); //il doppio nero è a destra
        }
        else if (k < T->key) //cancello a sinistra
        {
            T->left = DeleteRB (T->left, k);
            T = BilanciaSx (T); //il doppio nero è a sinistra
        }
    }
    return T;
}

//Analogo alla versione per alberi AVL
//Se ho cancellato un nodo nero, devo propagare il colore nero al nodo che lo sostituisce.
//Funzione ausiliaria PropagateBlack: se il nodo è rosso, lo coloro di nero. Se è nero, diventerá DOPPIO NERO (provvisoriamente, fino al bilanciamento).
struct Tree * DeleteRootRB(struct Tree * T)
{

    struct Tree * toDelete = T;
    
    if (T->left == &Nil)
    {
        T = T->right;
        if (toDelete->color == black)
        {
            PropagateBlack (T);
            //Posso avere un doppio nero in T
            //La violazione verrá rilevata dal padre di T nella prossima chiamata ricorsiva di DeleteRB.
            //Se T è la radice, non importa che sia nero o doppio nero
        }
    }

    else if (T->right == &Nil)
    {
        T = T->left;
        if (toDelete->color == black)
        {
            PropagateBlack (T);
        }
    }
    
    else
    {
        toDelete = StaccaMinRB (T->right, T);
        //Abbiamo giá propagato il nero e bilanciato fino a T->right in StaccaMin
        T->key = toDelete->key;
        T = BilanciaDeleteDx (T);
    }

    free (toDelete);
    toDelete = NULL;
    
    return T;
}

//Analogo alla versione per alberi RB.
//Devo propagare il nero sul figlio del minimo, quindi bilanciare.
struct Tree * StaccaMinRB (struct Tree * T, struct Tree * Pred)
{
    struct Tree * min = T;
    if (T != &Nil)
    {
        if (T->left != &Nil)
        {
            min = StaccaMinRB (T->left, T);
            if (T == Pred->left) //Sempre?
            {
                T = BilanciaDeleteSx (T);
            }
            else //T == Pred->right. Ma quando succede? Inserito comunque per robustezza?
            {
                T = BilanciaDeleteDx (T);
            }
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

                //Se min è nero, devo propagare il nero.
                if (min->color == black)
                {
                    PropagateBlack (min->right);
                    //Posso avere un doppio nero in min->right
                    //Quindi devo chiamare BilanciaDeleteDx su min prima di cancellarlo
                    min = BilanciaDeleteDx (min);
                }
            //Il bilanciamento a sinistra su Pred viene eseguito al ritorno della chiamata ricorsiva.
            //Se è stato eseguito subito il caso base, Pred viene bilanciato in DeleteRootRB.
            }
        }
    }
    return min;
}

void PropagateBlack (struct Tree * T)
{
    if (T->color == red)
    {
        T->color = black;
    }
    else
    {
        T->color = double_black;
    }
}

int ViolazioneDeleteSx (struct Tree * Sx, struct Tree * Dx)
{
    //Quando trovo un nodo doppio nero, controllo il fratello
    int violazione = 0;
    if (Sx->color == double_black);
    {
        //Caso 1: il fratello è rosso
        if (Dx->color == red)
        {
            violazione = 1;
        }
        //Altrimenti: il fratello è nero e...
        //Caso 2: i suoi figli sono entrambi neri
        else if (Dx->left->color == black && Dx->right->color == black)
        {
            violazione = 2;
        }
        //Caso 3: solo il suo figlio destro è nero (il sinistro è rosso)
        else if (Dx->right->color == black) //Sx->left->color == red
        {
            violazione = 3;
        }
        //Caso 4: il suo figlio destro è rosso (il sinistro puó essere sia rosso che nero)
        else //Dx->right->color == red
        {
            violazione = 4;
        }
    }
    return violazione;
}

struct Tree * BilanciaDeleteSx (struct Tree * T)
{
    //Non importa di che colore sia T. 
    //La violazione viene rilevata quando T->left è doppio nero.
    if (T->right != &Nil)
    {
        switch (ViolazioneDeleteSx (T->left, T->right))
        {
            case 1: //T->right è rosso (quindi suo padre T e i suoi figli sono per forza neri)
            //La rotazione a destra sposta il doppio nero piú in basso lungo il sottoalbero sinistro.
            T=RotazioneDx (T); 
            T->left->color = red; //il nuovo T->left è il vecchio T, nero. Possiamo colorarlo di rosso perché i suoi figli sono il nodo doppio nero e uno dei figli del vecchio T->right.
            T->color = black; //il nuovo T è il vecchio T->right, rosso. Dobbiamo colorarlo di nero.
            //Devo richiamare l'algoritmo sul nuovo T->left.
            T->left = BilanciaDeleteSx (T->left);
            break;
            
            //T->right è nero e...
            case 2: //ha entrambi i figli neri
            //Spostiamo il nero da T->left a T. Se T diventa doppio nero, l'algoritmo verrá richiamato piú avanti.
            PropagateBlack (T);
            T->left->color = black;
            //Coloriamo T->right di rosso (perché ha due figli neri), in modo da mantenere l'altezza nera dei nodi del sottoalbero destro.
            T->right->color = red; 
            break;

            case 3: //il suo figlio destro è nero, il suo figlio sinistro è rosso
            //Rotazione e cambio colori per ricondurre al caso 4
            T->right = RotazioneSx (T->right);
            T->right->color = black;
            T->right->right->color = red;
            //siamo nel caso 4
            T = RotazioneSx (T);
            T->right->color = black;
            T->color = T->left->color;
            T->left->color = black;
            T->left->left->color = black;
            break;

            case 4: //il suo figlio destro è rosso
            T = RotazioneSx (T); 
            T->right->color = black; //Cioé T->color. La rotazione ha tolto un nero dal sottoalbero destro
            T->color = T->left->color; //T, che è nero, prende il colore di T->left, la vecchia radice
            T->left->color = black; //Lo scopo della rotazione era aggiungere un nero al sottoalbero sinistro. Se T->left era rosso, lo coloro di nero.
            T->left->left->color = black; //il nodo doppio nero a questo punto puó tornare nero.
            break;
        }
    }
    return T;
}

int ViolazioneDeleteDx (struct Tree * Sx, struct Tree * Dx)
{
    //Quando trovo un nodo doppio nero, controllo il fratello
    int violazione = 0;
    if (Dx->color == double_black);
    {
        //Caso 1: il fratello è rosso
        if (Sx->color == red)
        {
            violazione = 1;
        }
        //Altrimenti: il fratello è nero e...
        //Caso 2: i suoi figli sono entrambi neri
        else if (Sx->left->color == black && Sx->right->color == black)
        {
            violazione = 2;
        }
        //Caso 3: solo il suo figlio sinistro è nero (il destro è rosso)
        else if (Sx->right->color == black) //Dx->left->color == red
        {
            violazione = 3;
        }
        //Caso 4: il suo figlio sinistro è rosso (il destro puó essere sia rosso che nero)
        else //Sx->right->color == red
        {
            violazione = 4;
        }
    }
    return violazione;
}

struct Tree * BilanciaDeleteDx (struct Tree * T)
{
    //Non importa di che colore sia T. 
    //La violazione viene rilevata quando T->right è doppio nero.
    if (T->right != &Nil)
    {
        switch (ViolazioneDeleteDx (T->left, T->right))
        {
            case 1: //T->left è rosso
            //La rotazione a sinistra sposta il doppio nero piú in basso lungo il sottoalbero destro.
            T=RotazioneSx (T); 
            T->right->color = red;
            T->color = black;
            T->right = BilanciaDeleteDx (T->right);
            break;
            
            //T->left è nero e...
            case 2: //ha entrambi i figli neri
            //Spostiamo il nero da T->right a T.
            PropagateBlack (T);
            T->right->color = black;
            //Coloriamo T->left di rosso (perché ha entrambi i figli neri)
            T->left->color = red; 
            break;
            
            case 3: //il suo figlio sinistro è nero, il suo figlio destro è rosso
            //Rotazione e cambio colori per ricondurre al caso 4
            T->left = RotazioneDx (T->left);
            T->left->color = black;
            T->left->left->color = red;
            //siamo nel caso 4
            T = RotazioneSx (T);
            T->right->color = black;
            T->color = T->left->color;
            T->left->color = black;
            T->left->left->color = black;
            break;

            case 4: //il suo figlio sinistro è rosso
            T = RotazioneSx (T); //ora T è nero, T->left è rosso, T->right->right è il doppio nero
            T->left->color = black; //Cioé T->color: la rotazione ha tolto un nero dal sottoalbero sinistro
            T->color = T->left->color; //T, che è nero, prende il colore di T->left, la vecchia radice
            T->right->color = black; //Lo scopo della rotazione era aggiungere un nero al sottoalbero destro. Se T->right era rosso, lo coloro di nero.
            T->right->right->color = black; //il nodo doppio nero a questo punto puó tornare nero.
            break;
        }
    }
    return T;
}