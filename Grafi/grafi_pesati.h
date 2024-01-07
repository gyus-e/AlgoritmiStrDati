#include "grafi.h"

#ifndef GRAFI_PESATI_H_
#define GRAFI_PESATI_H_

int Weight (struct Vertice * U, struct Vertice * W); //Restituisce il peso di un arco
void Init_Distance (struct Grafo * G, struct Vertice * S); //Inizializza la distanza di S a 0 e quella degli altri vertici a infinito

void Relax (struct Vertice * U, struct Vertice * W); //Dato un arco (U, V), cerca di trovare una stima migliore della distanza di U dalla sorgente S

//Chiamiamo d (V, U) il peso del percorso minimo tra V ed U, mentre Distance [V] la distanza stimata da Relax (V, W) di V dalla sorgente S

//Lemma 1
//Sia V_1, V_2, ..., V_k un percorso minimo
//Per ogni i compreso tra 1 e K
//V_i, ..., V_k sará un percorso minimo

//Corollario 1
//Sia S, V_2, ..., V_k un percorso minimo
//d (V_1, V_k) = d (V_1, V_(k-1)) + Weight (V_(k-1), V_k)

//Lemma 2
//Sia S il vertice sorgente
//Per ogni arco (U, V) del grafo
//d (S, V) <= d (S, U) + Weight (U, V)

//Lemma 3
//Sia (U, V) un arco del grafo
//Dopo un'esecuzione di Relax (U, V), varrá sempre 
//Distance [V] <= Distance [U] + Weight (U, V)

//Lemma 4
//Sia Distance [S] = 0 e, per ogni vertice V diverso da S, Distance [V] = infinity
//Dopo un qualsiasi numero di esecuzioni di Relax, varrá sempre 
//Distance [V] >= d (S, V)

//Corollario 2
//Sia V un vertice non raggiungibile dalla sorgente S (cioé d(S,V) = infinity), Distance [S] = 0 e Distance [V] = infinity
//Dopo un qualsiasi numero di esecuzioni di Relax, varrá sempre
//Distance [V] = infinity

//Lemma 5
//Sia S, V_2, ..., V_k un percorso minimo, Distance [S] = 0 e, per ogni vertice V_i diverso da S, Distance[V_i] = infinity
//Se vale Distance [V_(k-1)] = d (S, V_k-1)
//Effettuando Relax (V_(k-1), V_k)
//Allora varrá Distance [V_k] = d (S, V_k)

bool BellmanFord (struct Grafo * G, struct Vertice * S); //Trova i percorsi minimi e individua cicli negativi

struct Vertice * ExtractMin (struct Queue * Q, struct Vertice * S);
void Dijkstra (struct Grafo * G, struct Vertice * S); //Trova i percorsi minimi in grafi senza percorsi negativi.

#endif