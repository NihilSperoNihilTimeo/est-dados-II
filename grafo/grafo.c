#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"
#include "../lista/lista.h"

struct vertice {
    Lista listaIncidencia;
    int livre;
};
typedef struct vertice* Vertice;

struct aresta {
        int alfa;
        int omega;
};
typedef struct aresta* Aresta;

struct grafo {
    int nvMax;
    int naMax;

    Vertice vertices;
    Aresta arestas;
};

Grafo GGcriaGrafo(int v, int e) {
    if (v <= 0 || e <= 0) {
        return NULL;
    }

    Vertice vetVertice = (Vertice) malloc((v + 1)*sizeof(Aresta));
    Aresta vetAresta =   (Aresta)  malloc((e + 1)*sizeof(Aresta));

    Grafo g = (Grafo) malloc(sizeof(struct grafo)); 

    g->vertices = vetVertice;
    g->nvMax = v;
    g->arestas = vetAresta;
    g->naMax = e;

    for(int i = 0; i < v; i++) {
        g->vertices[i].livre = i + 1;
    }
  //AQUI: Lista[v] com apenas um node com o número de vertices criados

    for(int i = 0; i < e; i++) {
        g->arestas[i].omega = i + 1;
    }
    g->arestas[e].alfa = 0;

    return g;
}

void* GGdestroiGrafo(Grafo g) {
    if (g == NULL) {
        return; 
    }

    if (g->vertices != NULL) {   
        for (int i = 0; i < g->nvMax; i++) {
            if (g->vertices[i].listaIncidencia != NULL) {
                //destroi_lista(g->vertices[i].listaIncidencia); 
            }
        }    
        free(g->vertices);
    }

    if (g->arestas != NULL) {
        free(g->arestas);
    }

    free(g);
}