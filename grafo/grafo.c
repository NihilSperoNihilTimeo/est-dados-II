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

    for (int i = 0; i < v; i++) {
        g->vertices[i].livre = i + 1;
    }
    g->vertices[v].livre = 0;

    g->vertices[0].listaIncidencia = Lcria();

    for (int i = 0; i < e; i++) {
        g->arestas[i].omega = i + 1;
    }
    g->arestas[e].alfa = 0;
    g->arestas[0].alfa = 0;

    return g;
}

void* GGdestroiGrafo(Grafo g) {
    if (g == NULL) {
        return; 
    }

    if (g->vertices != NULL) {   
        for (int i = 0; i < g->nvMax; i++) {
            if (g->vertices[i].listaIncidencia != NULL) {
                Ldestroi(g->vertices[i].listaIncidencia); 
            }
        }    
        free(g->vertices);
    }

    if (g->arestas != NULL) {
        free(g->arestas);
    }

    free(g);
}

int GVcriaVertice(Grafo g) {
   if (g->vertices[0].livre != 0 && g->vertices[0].listaIncidencia <= g->nvMax) {

        int qualLivre = g->vertices[0].livre;
        int proxLivre = g->vertices[qualLivre].livre;

        g->vertices[qualLivre].listaIncidencia = Lcria;
        // Incrementar contador listaIncidencia[0] 
        g->vertices[0].livre = proxLivre;
        
        return qualLivre;
   }

   return 0;
}
 
int GAcriaAresta(Grafo g, int v1, int v2) {
    if (g->arestas[0].omega != 0 && g->arestas[0].alfa <= g->naMax) {
        if (g->vertices[v1].listaIncidencia != NULL && g->vertices[v2].listaIncidencia != NULL) {
            
            int qualLivre = g->arestas[0].alfa;
            int prox = g->arestas[qualLivre].alfa;

            g->arestas[qualLivre].alfa = v1;
            g->vertices[v1].listaIncidencia = (int) Linsere(-v1);
            g->arestas[qualLivre].omega = v2;
            g->vertices[v2].listaIncidencia = (int) Linsere(+v2);
            g->arestas[0].alfa++;
            g->arestas[0].alfa = prox;
            
            return qualLivre;
        }
    }

   return 0;
} 

int GBexisteIdVertice(Grafo g, int vertice) {
    if (g->vertices[vertice].listaIncidencia != NULL) {
        return 1;
    }

    return 0;
}

int GBexisteIdAresta(Grafo g, int aresta) {
    if (g->arestas[aresta].alfa != 0) {
        return 1;
    }

    return 0;
}

int GBexisteArestaDir(Grafo g, int v1, int v2) {
    for (int i = 1; i <= g->arestas[0].alfa; i++) {
        if (g->arestas[i].alfa == v1 && g->arestas[i].omega == v2) {
            return 1;
        }
    }

    return 0;
}

int GBexisteAresta(Grafo g, int aresta) {
    if (g->arestas[aresta].alfa != 0) {
        return 1;
    }

    return 0;
}

int GApegaArestaDir(Grafo g, int v1, int v2) {
    for (int i = 1; i <= g->arestas[0].alfa; i++) {
        if (g->arestas[i].alfa == v1 && g->arestas[i].omega == v2) {
            return i;
        }
    }

    return 0;
}

int GApegaAresta(Grafo g, int v1, int v2) {
    int a = GApegaArestaDir(g, v1, v2);
    
    if (a == 0) {
        a = GApegaArestaDir(g, v2, v1);
    }

    return a;
}

int GVprimeiroVertice(Grafo g) {
    for (int i = 1; i <= g->nvMax; i++) {
        if (g->vertices[i].listaIncidencia != NULL) {
            return i;
        }
    }

    return 0;
}

int GVproximoVertice(Grafo g, int vertice) {

}