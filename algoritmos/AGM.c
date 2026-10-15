/*
    Algoritmos sobre grafos - Estrutura de dados II

    Grupo:
        Rayane Kaylla Venâncio Gomes Alves - 0117243
        Mateus Otacílio Silva Gomes - 0117242
*/  
// AGM = Árvore Geradora Mínima com Algoritmo de Prim (ou MST - Minimum spanning tree)
#include <stdio.h>
#include <stdlib.h>
#include <float.h> //  para usar o INT_MAX 

#include "algoritmos.h"

void AGM(Grafo g, float* pesos) {
    int maxV = GInumeroVerticesMax(g); 

    char  *cor    =  (char*)  malloc((maxV + 1) * sizeof(char));
    int   *pi        = (int*)     malloc((maxV + 1) * sizeof(int));
    float *chave = (float*)   malloc((maxV + 1) * sizeof(float)); 

    for (int i = 0; i <= maxV; i++) {
        cor[i]   = 'w';
        pi[i]    = 0;
        chave[i] = FLT_MAX; 
    }

    int inicio = GVprimeiroVertice(g);
    if (inicio != 0) {
        chave[inicio] = 0.0;
    }

    for (int iter = 1; iter <= maxV; iter++) {
        int u = 0;
        float minChave = FLT_MAX; 

        for (int i = 1; i <= maxV; i++) {
            if (cor[i] == 'w' && chave[i] < minChave) {
                minChave = chave[i];
                u = i;
            }
        }
       
        if (u == 0 ) {
            break;
        } 

        cor[u] = 'b';

        for (int a = GAprimaAresta(g, u); a != 0; a = GAproxAresta(g, u, a)) {
            int v = GVvizinho(g, a, u);
            
            if (cor[v] == 'w' && pesos[a] < chave[v]) {
                chave[v] = pesos[a]; 
                pi[v] = u;          
            }
        }
    }

    printf("Lista de arestas que formam a AGM:\n");
    float custoTotal = 0.0;
    
    for (int i = 1; i <= maxV; i++) {
        if (pi[i] != 0) {
            printf("Aresta: %d -- %-2d | Peso: %.2f\n", pi[i], i, chave[i]);
            custoTotal += chave[i];
        }
    }
    printf("\tCusto total: %.2f\n", custoTotal);

    free(cor);
    free(pi);
    free(chave);
}