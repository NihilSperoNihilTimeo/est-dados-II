#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "grafo/grafo.h"
#include "fila/fila.h"

// Árvore geradora mínima, utilizando algoritmo de Prim (1)
void AGM(Grafo g, float* pesos);

// Busca em largura a partir de um vértice inicial (2)
void BEL(Grafo g, int inicio);

// Busca em profundidade a partir de um vértice inicial (3)
void BEP(Grafo g, int inicio);

// Componentes conexos, utilizando BEP (5)
void CC(Grafo g);

// Caminho mais curto de a até b, utilizando algoritmo de Dijkstra (4)
void CMC(Grafo g, float* pesos, int a, int b);

#endif