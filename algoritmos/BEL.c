/*
    Algoritmos sobre grafos - Estrutura de dados II

    Grupo:
        Rayane Kaylla Venâncio Gomes Alves - 0117243
        Mateus Otacílio Silva Gomes - 0117242
*/  
// BEL = Busca em largura (ou BFS - Breadth-first search)
#include <stdio.h>
#include <stdlib.h>

#include "algoritmos.h"

void BEL(Grafo g, int inicio) {
    int maxV = GInumeroVerticesMax(g); 

    char *cor = (char*) malloc((maxV + 1) * sizeof(char));
    int    *d   = (int*)    malloc((maxV + 1) * sizeof(int));
    int    *pi   = (int*)   malloc((maxV + 1) * sizeof(int));

    for (int i = 0; i <= maxV; i++) {
        cor[i] = 'w';
        d[i]    = -1;
        pi[i]   = 0;
    }

    cor[inicio] = 'g';
    d[inicio] =  0;
    pi[inicio] = 0;

    Fila f = Fcria();
    int* num = (int*) malloc(sizeof(int));
    *num = inicio;
    Finsere(f, num);

    printf("v%d", inicio);

    while (!Fvazia(f)) {
        void* item = Fremove(f);
        int x = *(int*) item;
        free(item);

        for (int a = GAprimaSaida(g, x); a != 0; a = GAproxSaida(g, x, a)) {       
            int v = GVomega(g, a);

            if (cor[v] == 'w') {
                printf(",a%d,v%d", a, v);
                cor[v] = 'g';      
                d[v]     = d[x] + 1;  
                pi[v]    = x;   
                int* numV = (int*) malloc(sizeof(int));  
                *numV = v;
                Finsere(f, numV);     
            }
        }

        cor[x] = 'b';
    }

    printf("\n");
    Fdestroi(f);
    free(cor);
    free(d);
    free(pi);
}