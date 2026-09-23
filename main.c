#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafo/grafo.h"

static void limpaEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int main(void) {
    int nvMax, naMax;
    char nomeArquivo[256];
    char nomeDot[256];
    int dirigido;

    printf("=== Criar grafo e salvar ===\n\n");

    printf("Numero maximo de vertices: ");
    if (scanf("%d", &nvMax) != 1 || nvMax <= 0) {
        printf("Valor invalido.\n");
        return 1;
    }

    printf("Numero maximo de arestas: ");
    if (scanf("%d", &naMax) != 1 || naMax <= 0) {
        printf("Valor invalido.\n");
        return 1;
    }

    Grafo g = GGcriaGrafo(nvMax, naMax);
    if (g == NULL) {
        printf("Falha ao criar o grafo.\n");
        return 1;
    }

    printf("\nQuantos vertices deseja criar agora (1..%d)? ", nvMax);
    int nv;
    if (scanf("%d", &nv) != 1 || nv <= 0 || nv > nvMax) {
        printf("Valor invalido.\n");
        GGdestroiGrafo(g);
        return 1;
    }

    for (int i = 0; i < nv; i++) {
        int id = GVcriaVertice(g);
        if (id == 0) {
            printf("Nao foi possivel criar o vertice %d.\n", i + 1);
            GGdestroiGrafo(g);
            return 1;
        }
        printf("  Vertice criado: %d\n", id);
    }

    printf("\nArestas: informe origem e destino (ex: 1 2).\n");
    printf("Digite 0 0 para terminar.\n");
    printf("Vertices validos: 1..%d | max arestas: %d\n\n", nv, naMax);

    for (;;) {
        if (GInumeroArestas(g) >= naMax) {
            printf("Capacidade de arestas atingida (%d).\n", naMax);
            break;
        }

        int v1, v2;
        printf("Aresta %d (origem destino): ", GInumeroArestas(g) + 1);
        if (scanf("%d %d", &v1, &v2) != 2) {
            printf("Entrada invalida. Use dois inteiros (ou 0 0 para sair).\n");
            limpaEntrada();
            continue;
        }

        if (v1 == 0 && v2 == 0) {
            break;
        }

        if (!GBexisteIdVertice(g, v1) || !GBexisteIdVertice(g, v2)) {
            printf("  Vertice inexistente. Use 1..%d\n", nv);
            continue;
        }

        int a = GAcriaAresta(g, v1, v2);
        if (a == 0) {
            printf("  Falha ao criar aresta (%d,%d).\n", v1, v2);
            continue;
        }

        printf("  Aresta %d criada: %d -> %d\n", a, v1, v2);
    }

    limpaEntrada();

    printf("\nNome do arquivo para salvar (ex: grafo.txt): ");
    if (scanf("%255s", nomeArquivo) != 1) {
        snprintf(nomeArquivo, sizeof(nomeArquivo), "grafo.txt");
        printf("Nome invalido; usando %s\n", nomeArquivo);
    }

    if (!GBsalvaGrafo(g, nomeArquivo)) {
        printf("\nNao foi possivel salvar em \"%s\".\n", nomeArquivo);
        GGdestroiGrafo(g);
        return 1;
    }
    printf("Grafo salvo em \"%s\" (formato proprio / reload).\n", nomeArquivo);

    printf("\nExportar Graphviz DOT? (1=sim, 0=nao): ");
    int querDot;
    if (scanf("%d", &querDot) != 1) {
        querDot = 0;
    }

    if (querDot) {
        printf("Grafo dirigido? (1=sim digraph/-> , 0=nao graph/-- ): ");
        if (scanf("%d", &dirigido) != 1) {
            dirigido = 1;
        }
        dirigido = dirigido ? 1 : 0;

        printf("Nome do arquivo .dot (ex: grafo.dot): ");
        if (scanf("%255s", nomeDot) != 1) {
            snprintf(nomeDot, sizeof(nomeDot), "grafo.dot");
            printf("Nome invalido; usando %s\n", nomeDot);
        }

        if (GBexportaDot(g, nomeDot, dirigido)) {
            printf("DOT exportado em \"%s\"\n", nomeDot);
            printf("Para gerar imagem (CMD):\n");
            printf("  dot -Tpng %s -o grafo.png\n", nomeDot);
        } else {
            printf("Falha ao exportar DOT em \"%s\".\n", nomeDot);
        }
    }

    printf("\nVertices: %d | Arestas: %d\n",
           GInumeroVertices(g), GInumeroArestas(g));

    GGdestroiGrafo(g);
    return 0;
}
