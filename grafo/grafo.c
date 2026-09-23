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

// Funções auxiliares para tornar o código mais limpo
void  incrementaContadorVertices(Grafo g) {
    void* dado = Lexamina(g->vertices[0].listaIncidencia, 1);
    if (dado) {
        int* contador = (int*) dado;
        (*contador)++; 
    }
}

void pulaLinha(FILE *f) {
    while (fgetc(f) != '\n' && !feof(f));
}

  // dirigido = 1 -> digraph + "->"; 0 -> graph + "--" */
int GBexportaDot(Grafo g, const char *nome, int dirigido) {
      FILE *f = fopen(nome, "w");
      
      if (!f) return 0;
      
      fprintf(f, "%s g {\n", dirigido ? "digraph" : "graph");
      
      for (int v = GVprimeiroVertice(g); v; v = GVproximoVertice(g, v))
          fprintf(f, "  %d;\n", v);
      
      const char *op = dirigido ? "->" : "--";
      for (int a = GAprimeiraAresta(g); a; a = GAproximaAresta(g, a))
          fprintf(f, "  %d %s %d;\n", GValfa(g, a), op, GVomega(g, a));
    
          fprintf(f, "}\n");
          
    fclose(f);
    return 1;
}

// Operações relacionadas ao grafo
Grafo GGcriaGrafo(int v, int e) {
    if (v <= 0 || e <= 0) {
        return NULL;
    }

    Vertice vetVertice = (Vertice) malloc((v + 1)*sizeof(struct vertice));
    Aresta vetAresta =   (Aresta)  malloc((e + 1)*sizeof(struct aresta));

    Grafo g = (Grafo) malloc(sizeof(struct grafo)); 

    g->vertices = vetVertice;
    g->nvMax = v;
    g->arestas = vetAresta;
    g->naMax = e;

    for (int i = 0; i < v; i++) {
        g->vertices[i].livre = i + 1;
        g->vertices[i].listaIncidencia = NULL;
    }
    g->vertices[v].livre = 0;
    g->vertices[v].listaIncidencia = NULL;

    g->vertices[0].listaIncidencia = Lcria();
    int* contadorInicial = (int*) malloc(sizeof(int));
    *contadorInicial = 0;
    Linsere(g->vertices[0].listaIncidencia, contadorInicial);

    for (int i = 0; i < e; i++) {
        g->arestas[i].omega = i + 1;
    }
    g->arestas[e].omega = 0;
    
    g->arestas[0].alfa = 0;

    return g;
}

void GGdestroiGrafo(Grafo g) {
    if (g == NULL) {
        return; 
    }

    if (g->vertices) {   
        for (int i = 0; i <= g->nvMax; i++) {
            if (g->vertices[i].listaIncidencia) {
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
   if (g->vertices[0].livre != 0 && g->vertices[0].listaIncidencia != NULL) {
        void* ptr =  Lexamina(g->vertices[0].listaIncidencia, 1);
        
        if (ptr != NULL && *(int*)ptr <= g->nvMax) {
            int qualLivre = g->vertices[0].livre;
            int proxLivre = g->vertices[qualLivre].livre;

            g->vertices[qualLivre].listaIncidencia = Lcria();
            incrementaContadorVertices(g);
            g->vertices[0].livre = proxLivre;
            
            return qualLivre;
        }
    }

   return 0;
}
 
int GAcriaAresta(Grafo g, int v1, int v2) {
    if (g->arestas[0].omega != 0 && g->arestas[0].alfa < g->naMax) {
        if (g->vertices[v1].listaIncidencia != NULL && g->vertices[v2].listaIncidencia != NULL) {
            
            int qualLivre = g->arestas[0].omega;
            int prox = g->arestas[qualLivre].omega;

            g->arestas[qualLivre].alfa = v1;
            
            int* alfa = (int*) malloc(sizeof(int));
            *alfa = -qualLivre;
            Linsere(g->vertices[v1].listaIncidencia, alfa);

            g->arestas[qualLivre].omega = v2;

            int* omega = (int*) malloc(sizeof(int));
            *omega = +qualLivre;
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

int GBexisteAresta(Grafo g, int v1, int v2) {
    for (int i = 1; i <= g->arestas[0].alfa; i++) {
        if ((g->arestas[i].alfa == v1 && g->arestas[i].omega == v2) ||
            (g->arestas[i].alfa == v2 && g->arestas[i].omega == v1) ) {
                
                return 1;
        }
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
    for (int i = vertice+1; i <= g->nvMax; i++) {
        if (g->vertices[i].listaIncidencia) {
            return i;
        }
    }

    return 0;
}

int GAprimeiraAresta(Grafo g) {
    for (int i = 1; i <= g->naMax; i++) {
        if (g->arestas[i].alfa) {
            return i;
        }
    }

    return 0;
}

int GAproximaAresta(Grafo g, int aresta) {
    for (int i = aresta+1; i <= g->naMax; i++) {
        if (g->arestas[i].alfa) {
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

int GInumeroArestasMax(Grafo g) {
    return g->naMax;
}

Grafo GGcarregaGrafo(const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "r");
    int numVertices;
    int numArestas;

    if (f) {
        pulaLinha(f);
        pulaLinha(f);
        if (fscanf(f, " \t#nvMax %d", &numVertices) != 1) {
            fclose(f);
            return NULL;
        }   
        if (fscanf(f, " \t#naMax %d", &numArestas) != 1) {
            fclose(f);
            return NULL;
        }

        Grafo g = GGcriaGrafo(numVertices, numArestas);

        if (g) {
            int ver;
            while (fscanf(f, " \t%d;", &ver) == 1) {
                if (GVcriaVertice(g) == 0) {
                    fclose(f);
                    GGdestroiGrafo(g);
                    return NULL;
                }
            }

            int v1, v2;    
            while (fscanf(f, " \t%d -- %d;", &v1, &v2) == 2) {
                if (GAcriaAresta(g, v1, v2) == 0) {
                    fclose(f);
                    GGdestroiGrafo(g);
                    return NULL;
                }
            }

        }      
        fclose(f);
        return g;
    }
    return NULL;
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
                fprintf(f, "\t%d -- %d;\n", g->arestas[i].alfa, g->arestas[i].omega);
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
int GIpegaGrau(Grafo g, int vertice) {
    if (g->vertices[vertice].listaIncidencia) {
        return Ltamanho(g->vertices[vertice].listaIncidencia);
    }

    return 0;
}

int GAprimaAresta(Grafo g, int vertice) {
    if (g->vertices[vertice].listaIncidencia != NULL) {     
        return GAproxAresta(g, vertice, 0);
    }

    return 0;
}

int GAproxAresta(Grafo g, int vertice, int aresta) {
    if (g->vertices[vertice].listaIncidencia != NULL) {
        int tamanho = Ltamanho(g->vertices[vertice].listaIncidencia);

        if (tamanho > 0) {
            int proxAresta = 0;
            int minAbs = 0; 
            int absRef = abs(aresta); 

            for (int i = 1; i <= tamanho; i++) {
                void* ptr = Lexamina(g->vertices[vertice].listaIncidencia, i);

                if (ptr != NULL) {
                    int arestaAtual = *(int*)ptr;
                    int absAtual = abs(arestaAtual); 

                    if (absAtual > absRef) {
                        if (minAbs == 0 || absAtual < minAbs) {
                            minAbs = absAtual;
                            proxAresta = arestaAtual; 
                        }
                    }
                }
            }
            return abs(proxAresta); 
        }
    }
    
    return 0;
}

int GAprimaEntrada(Grafo g, int vertice) {
    if (g->vertices[vertice].listaIncidencia != NULL) {
        int tamanho = Ltamanho(g->vertices[vertice].listaIncidencia);

        if (tamanho > 0) {
            int minAresta = 0;

            for (int i = 1; i <= tamanho; i++) {
                void* ptr = Lexamina(g->vertices[vertice].listaIncidencia, i);

                if (ptr != NULL) {
                    int arestaAtual = *(int*)ptr;

                    if (arestaAtual > 0) {
                        if (minAresta == 0 || arestaAtual < minAresta) {
                            minAresta  = arestaAtual;
                        }
                    }
                }
            }
            return abs(minAresta); 
        }
    }
    
    return 0;
}

int GAproxEntrada(Grafo g, int vertice, int aresta) {
    if (g->vertices[vertice].listaIncidencia != NULL) {
        int tamanho = Ltamanho(g->vertices[vertice].listaIncidencia);

        if (tamanho > 0) {
            int minAresta = 0;

            for (int i = 1; i <= tamanho; i++) {
                void* ptr = Lexamina(g->vertices[vertice].listaIncidencia, i);

                if (ptr != NULL) {
                    int arestaAtual = *(int*)ptr;

                    if (arestaAtual > 0 && arestaAtual > aresta) {
                        if (minAresta == 0 || arestaAtual < minAresta) {
                            minAresta  = arestaAtual;
                        }
                    }
                }
            }
            return abs(minAresta); 
        }
    }
    
    return 0;
}

int GAprimaSaida(Grafo g, int vertice) {
    if (g->vertices[vertice].listaIncidencia != NULL) {
        int tamanho = Ltamanho(g->vertices[vertice].listaIncidencia);

        if (tamanho > 0) {
            int minAresta = 0;

            for (int i = 1; i <= tamanho; i++) {
                void* ptr = Lexamina(g->vertices[vertice].listaIncidencia, i);

                if (ptr != NULL) {
                    int arestaAtual = *(int*)ptr;

                    if (arestaAtual < 0) {
                        if (minAresta == 0 || arestaAtual > minAresta) {
                            minAresta  = arestaAtual;
                        }
                    }
                }
            }
            return abs(minAresta); 
        }
    }
    
    return 0;
}

int GAproxSaida(Grafo g, int vertice, int aresta) {
    if (g->vertices[vertice].listaIncidencia != NULL) {
        int tamanho = Ltamanho(g->vertices[vertice].listaIncidencia);

        if (tamanho > 0) {
            int minAresta = 0;

            for (int i = 1; i <= tamanho; i++) {
                void* ptr = Lexamina(g->vertices[vertice].listaIncidencia, i);

                if (ptr != NULL) {
                    int arestaAtual = *(int*)ptr;

                    if (arestaAtual < 0 && abs(arestaAtual) > aresta) {
                        if (minAresta == 0 || arestaAtual > minAresta) {
                            minAresta  = arestaAtual;
                        }
                    }
                }
            }
            return abs(minAresta); 
        }
    }
    
    return 0;    
}

// Operações relacionadas às arestas do grafo
int GBarestaLaco(Grafo g, int aresta) {
    if (g->arestas[aresta].alfa) {
        if (g->arestas[aresta].alfa == g->arestas[aresta].omega) {
            return 1;
        }
    }

    return 0;
}

int GValfa(Grafo g, int aresta) {
    int alfa = g->arestas[aresta].alfa;

    if (alfa) {
        return alfa;
    }

    return 0;
}

int GVomega(Grafo g, int aresta) {
    int omega = g->arestas[aresta].omega;
    
    if (omega) {
        return omega;
    }

    return 0;
}

int GVvizinho(Grafo g, int aresta, int vertice) {
    if (g->arestas[aresta].alfa) {
        if (g->arestas[aresta].alfa == vertice) {
            return g->arestas[aresta].omega;
        }
        if (g->arestas[aresta].omega == vertice) {
            return g->arestas[aresta].alfa;
        }
    }

    return 0;
}