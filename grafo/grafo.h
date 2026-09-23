#ifndef GRAFO_H
#define GRAFO_H

struct grafo;
typedef struct grafo* Grafo;

Grafo GGcriaGrafo(int v, int e);
void GGdestroiGrafo(Grafo g);

int GVcriaVertice(Grafo g);
int GAcriaAresta(Grafo g, int v1, int v2);

int GBexisteIdVertice(Grafo g, int vertice);
int GBexisteIdAresta(Grafo g, int aresta);
int GBexisteArestaDir(Grafo g, int v1, int v2);
int GBexisteAresta(Grafo g, int aresta);

int GApegaArestaDir(Grafo g, int v1, int v2);
int GApegaAresta(Grafo g, int v1, int v2);

int GVprimeiroVertice(Grafo g);
int GVproximoVertice(Grafo g, int vertice);
int GAproximaAresta(Grafo g, int aresta);

int GInumeroVertices(Grafo g);
int GInumeroVerticesMax(Grafo g);
int GInumeroArestas(Grafo g);
int GInumeroArestaMax(Grafo g);

Grafo GGcarregaGrafo(const char *nomeArquivo);
int GBsalvaGrafo(Grafo g, const char *nomeArquivo);

int GIpegaGrau(Grafo g, int vertice);
int GAprimaAresta(Grafo g, int vertice);
int GAproxAresta(Grafo g, int vertice, int aresta);

#endif