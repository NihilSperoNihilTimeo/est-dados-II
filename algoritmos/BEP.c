/*
    Algoritmos sobre grafos - Estrutura de dados II

    Grupo:
        Rayane Kaylla Venâncio Gomes Alves - 0117243
        Mateus Otacílio Silva Gomes - 0117242
*/  
// BEP = Busca em profundidade (ou DFS - Depth-first search)
#include <stdio.h>
#include <stdlib.h>

#include "algoritmos.h"

static char *cor = NULL;
static int    *d   = NULL;
static int    *f   = NULL;
static int   *pi  = NULL;
static int  tempo = 0;

void BEP_visita(Grafo g, int u) {
    cor[u] = 'g';      
    tempo++;
    d[u] = tempo;  

    for (int a = GAprimaSaida(g, u); a != 0; a = GAproxSaida(g, u, a)) {       
        int v = GVomega(g, a);

        if (cor[v] == 'w') {
            printf(",a%d,v%d", a, v);
            pi[v] = u;
            BEP_visita(g, v);
        }
    }
    
    cor[u] = 'b';
    tempo++;
    f[u] = tempo;
}

void BEP(Grafo g, int inicio) {
    int maxV = GInumeroVerticesMax(g); 

    cor = (char*) malloc((maxV + 1) * sizeof(char));
    d    = (int*)    malloc((maxV + 1) * sizeof(int));
    f     = (int*)    malloc((maxV + 1) * sizeof(int));
    pi   = (int*)    malloc((maxV + 1) * sizeof(int));

    for (int i = 0; i <= maxV; i++) {
        cor[i] = 'w';
        pi[i]   = 0;
    }

    tempo = 0;

    if (cor[inicio] == 'w') {
        printf("v%d", inicio);
        BEP_visita(g, inicio);
    }
    
    printf("\n");
    free(cor);
    free(d);
    free(f);
    free(pi);  
    cor = NULL; d = NULL; f = NULL; pi = NULL;
}