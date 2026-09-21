#include <stdlib.h>
#include <stdio.h>

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

// Operações relacionadas ao grafo
void  incrementaContadorVertices(Grafo g) {
    void* dado = Lexamina(g->vertices[0].listaIncidencia, 1);
    if (dado) {
        int* contador = (int*) dado;
        (*contador)++; 
    }
}

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
    int* contadorInicial = (int*) malloc(sizeof(int));
    *contadorInicial = 0;
    Linsere(g->vertices[0].listaIncidencia, contadorInicial);

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

    if (g->vertices) {   
        for (int i = 0; i < g->nvMax; i++) {
            if (g->vertices[i].listaIncidencia != NULL) {
                Ldestroi(g->vertices[i].listaIncidencia); 
            }
        }    
        free(g->vertices);
    }

    if (g->arestas) {
        free(g->arestas);
    }

    free(g);
}

int GVcriaVertice(Grafo g) {
   if (g->vertices[0].livre != 0 && g->vertices[0].listaIncidencia <= g->nvMax) {

        int qualLivre = g->vertices[0].livre;
        int proxLivre = g->vertices[qualLivre].livre;

        g->vertices[qualLivre].listaIncidencia = Lcria;
        incrementaContadorVertices(g);
        g->vertices[0].livre = proxLivre;
        
        return qualLivre;
   }

   return 0;
}
 
int GAcriaAresta(Grafo g, int v1, int v2) {
    if (g->arestas[0].omega != 0 && g->arestas[0].alfa <= g->naMax) {
        if (g->vertices[v1].listaIncidencia != NULL && g->vertices[v2].listaIncidencia != NULL) {
            
            int qualLivre = g->arestas[0].omega;
            int prox = g->arestas[qualLivre].omega;

            g->arestas[qualLivre].alfa = v1;
            
            int* alfa = (int*) malloc(sizeof(int));
            *alfa = -v1;
            Linsere(g->vertices[v1].listaIncidencia, alfa);

            g->arestas[qualLivre].omega = v2;

            int* omega = (int*) malloc(sizeof(int));
            *omega = +v2;
            Linsere(g->vertices[v2].listaIncidencia, omega);

            g->arestas[0].alfa++;
            g->arestas[0].omega = prox;
            
            return qualLivre;
        }
    }

   return 0;
} 

int GBexisteIdVertice(Grafo g, int vertice) {
    if (g->vertices[vertice].listaIncidencia) {
        return 1;
    }

    return 0;
}

int GBexisteIdAresta(Grafo g, int aresta) {
    if (g->arestas[aresta].alfa) {
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
        if (g->vertices[i].listaIncidencia) {
            return i;
        }
    }

    return 0;
}

int GVproximoVertice(Grafo g, int vertice) {
    for (int i = vertice; i <= g->nvMax; i++) {
        if (g->vertices[i].listaIncidencia) {
            return i;
        }
    }

    return 0;
}

int GAproximaAresta(Grafo g, int aresta) {
    for (int i = aresta; i <= g->naMax; i++) {
        if (g->arestas[i].alfa != 0 || g->arestas[i].alfa != NULL) {
            return i;
        } 
    }

    return 0;
}

int GInumeroVertices(Grafo g) {
    return *(int*) Lexamina(g->vertices[0].listaIncidencia, 1);
}

int GInumeroVerticesMax(Grafo g) {
    return g->nvMax;
}

int GInumeroArestas(Grafo g) {
    return g->arestas[0].alfa;
}

int GInumeroArestaMax(Grafo g) {
    return g->naMax;
}

Grafo GGcarregaGrafo(const char *nomeArquivo) {
      FILE *f = fopen(nomeArquivo, "r");
      if (f) {
        //...
      }


}

int GBsalvaGrafo(Grafo g, const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "w");
    if (f) {
       fprintf(f, "graph g \n{\n");
       fprintf(f, "\t#nvMax %d\n", g->nvMax);
       fprintf(f, "\t#naMax %d\n", g->naMax);

       for (int i = 1; i <=g->nvMax; i++) {
            if (g->vertices[i].listaIncidencia) {
                fprintf(f, "\t%d;\n", i);
            }
       }

       for (int i = 1; i <=g->naMax; i++) {
            if (g->arestas[i].alfa) {
                fprintf(f, "\t%d -- %d\n", g->arestas[i].alfa, g->arestas[i].omega);
            }
       }

       fprintf(f, "}\n");

       fclose(f);
       return 1;

    } else {
        return 0;
    }  
}

// Funções relacionadas aos vértices do grafo