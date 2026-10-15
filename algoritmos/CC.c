/*
    Algoritmos sobre grafos - Estrutura de dados II

    Grupo:
        Rayane Kaylla Venâncio Gomes Alves - 0117243
        Mateus Otacílio Silva Gomes - 0117242
*/  
// CC = Componentes conexos, utilizando a BEP
#include <stdio.h>
#include <stdlib.h>

#include "algoritmos.h"

static char *cor = NULL;
static int    *d   = NULL;
static int    *f   = NULL;
static int   *pi  = NULL;
static int  tempo = 0;

void BEP_visita_CC(Grafo g, int u) {
    cor[u] = 'g';      
    tempo++;
    d[u] = tempo;  

    for (int a = GAprimaSaida(g, u); a != 0; a = GAproxSaida(g, u, a)) {       
        int v = GVomega(g, a);

        if (cor[v] == 'w') {
            printf(",a%d,v%d", a, v);
            pi[v] = u;
            BEP_visita_CC(g, v);
        }
    }
    
    cor[u] = 'b';
    tempo++;
    f[u] = tempo;
}

// BEP_CC
void CC(Grafo g) {
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

    // Laço que garante todos os componentes conexos do grafo
    for (int u = 1; u <= maxV; u++) {
        if (GBexisteIdVertice(g, u) && cor[u] == 'w') {
            printf("Componente conexo iniciando em v%d: v%d", u, u);
            BEP_visita_CC(g, u);
            printf("\n");
        }
    }

    printf("\n");
    free(cor);
    free(d);
    free(f);
    free(pi);  
    cor = NULL; d = NULL; f = NULL; pi = NULL;
}