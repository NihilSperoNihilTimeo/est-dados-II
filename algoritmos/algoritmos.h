#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "grafo/grafo.h"
#include "fila/fila.h"

// Busca em largura a partir de um vértice inicial (2)
void BEL(Grafo g, int inicio);

// Busca em profundidade a partir de um vértice inicial (3)
void BEP(Grafo g, int inicio);

// Componentes conexos, utilizando BEP (5)
void CC(Grafo g);

#endif