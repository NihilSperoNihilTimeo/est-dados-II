/*
    Algoritmos sobre grafos - Estrutura de dados II

    Grupo:
        Rayane Kaylla Venâncio Gomes Alves - 0117243
        Mateus Otacílio Silva Gomes - 0117242
*/
// CMC = Caminho mais curto

#include <stdio.h>
#include <stdlib.h>

#include "algoritmos.h"

void CMC(Grafo g, float *pesos, int a, int b)
{
    int maxV = GInumeroVerticesMax(g);
    int maxA = GInumeroArestasMax(g);

    float *d = (float *)malloc((maxV + 1) * sizeof(float));
    int *pi = (int *)malloc((maxV + 1) * sizeof(int));
    char *vis = (char *)malloc((maxV + 1) * sizeof(char));

    for (int i = 0; i <= maxV; i++)
    {
        d[i] = -1;
        pi[i] = 0;
        vis[i] = 0;
    }

    d[a] = 0;

    // ecolhe o vertice mais perto
    while (1)
    {
        int u = 0;
        // percorre os vertices do grafo
        for (int v = GVprimeiroVertice(g); v != 0; v = GVproximoVertice(g, v))
        {

            // escolhe um vertice nao tenha sido visitado e se a distancia for menor que a distancia do vertice atual (a melhor conhecida)
            if (!vis[v] && d[v] != -1 && (u == 0 || d[v] < d[u]))
            {
                u = v;
            }
        }

        if (u == 0 || u == b)
        {
            break;
        }

        vis[u] = 1;

        // percorre os vertices adjacentes ao vertice u
        for (int ar = GAprimaSaida(g, u); ar != 0; ar = GAproxSaida(g, u, ar))
        {
            int v = GVomega(g, ar);
            float nova = d[u] + pesos[ar];

            if (!vis[v] && (d[v] == -1 || nova < d[v]))
            {
                d[v] = nova;
                pi[v] = ar;
            }
        }
    }
    if (d[b] == -1)
    {
        printf("Não existe caminho de v%d até v%d.\n", a, b);
    }
    else
    {
        int *caminho = (int *)malloc((maxA + 1) * sizeof(int));
        int n = 0;

        for (int v = b; v != a; v = GValfa(g, pi[v]))
        {
            caminho[n++] = pi[v];
        }

        printf("v%d", a);
        for (int i = n - 1; i >= 0; i--)
        {
            printf(",a%d,v%d", caminho[i], GVomega(g, caminho[i]));
        }
        printf("\nDistância percorrida: %.2f\n", d[b]);

        free(caminho);
    }

    free(d);
    free(pi);
    free(vis);
}