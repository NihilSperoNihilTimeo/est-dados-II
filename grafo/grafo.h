#ifndef GRAFO_H
#define GRAFO_H

struct grafo;
struct aresta;
struct vertice;
typedef struct grafo* Grafo;

Grafo GGcriaGrafo(int v, int e);

void* GGdestroiGrafo(Grafo g) ;




#endif