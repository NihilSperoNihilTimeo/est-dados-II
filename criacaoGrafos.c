/*
    Grafo - Estrutura de dados II
    
    Grupo:
        Rayane Kaylla Venâncio Gomes Alves - 0117243
        Mateus Otacílio Silva Gomes - 0117242    
*/  
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
    int opcao;

    printf("=== Gerenciador de Grafos ===\n");
    printf("1. Criar grafo manualmente e salvar\n");
    printf("2. Carregar grafo de arquivo e exportar para Graphviz (.dot)\n");
    printf("Escolha uma opcao (1 ou 2): ");
    
    if (scanf("%d", &opcao) != 1) {
        printf("Opção inválida.\n");
        return 1;
    }

    if (opcao == 1) {
        int nvMax, naMax;
        char nomeArquivo[256];
        char nomeDot[256];
        int dirigido;

        printf("\n=== Criar grafo e salvar ===\n\n");

        printf("Número máximo de vértices: ");
        if (scanf("%d", &nvMax) != 1 || nvMax <= 0) {
            printf("Valor inválido.\n");
            return 1;
        }

        printf("Número máximo de arestas: ");
        if (scanf("%d", &naMax) != 1 || naMax <= 0) {
            printf("Valor inválido.\n");
            return 1;
        }

        Grafo g = GGcriaGrafo(nvMax, naMax);

        if (g == NULL) {
            printf("Falha ao criar o grafo.\n");
            return 1;
        }

        printf("\nQuantos vértices deseja criar agora (1..%d)? ", nvMax);
        int nv;
        if (scanf("%d", &nv) != 1 || nv <= 0 || nv > nvMax) {
            printf("Valor inválido.\n");
            GGdestroiGrafo(g);
            return 1;
        }

        for (int i = 0; i < nv; i++) {
            int id = GVcriaVertice(g);
            if (id == 0) {
                printf("Não foi possível criar o vértice %d.\n", i + 1);
                GGdestroiGrafo(g);
                return 1;
            }
            printf("  Vértice criado: %d\n", id);
        }

        printf("\nArestas: informe origem e destino (ex: 1 2).\n");
        printf("Digite 0 0 para terminar.\n");
        printf("Vértices válidos: 1..%d | max arestas: %d\n\n", nv, naMax);

        for (;;) {
            if (GInumeroArestas(g) >= naMax) {
                printf("Capacidade de arestas atingida (%d).\n", naMax);
                break;
            }

            int v1, v2;
            printf("Aresta %d (origem destino): ", GInumeroArestas(g) + 1);
            if (scanf("%d %d", &v1, &v2) != 2) {
                printf("Entrada inválida. Use dois inteiros (ou 0 0 para sair).\n");
                limpaEntrada();
                continue;
            }

            if (v1 == 0 && v2 == 0) {
                break;
            }

            if (v1 < 1 || v1 > GInumeroVerticesMax(g) ||
                v2 < 1 || v2 > GInumeroVerticesMax(g) ||
                !GBexisteIdVertice(g, v1) || !GBexisteIdVertice(g, v2)) {
                printf("  Vértice inexistente. Use 1..%d\n", nv);
                continue;
            }

            int a = GAcriaAresta(g, v1, v2);
            if (a == 0) {
                printf("  Falha ao criar aresta (%d,%d).\n", v1, v2);
                continue;
            }

            printf("  Aresta %d criada: %d -> %d\n", a, v1, v2);
        }

        int opcaoRemocao = 0;
        do {
            printf("\n=== Remover elementos do grafo ===\n");
            printf("1. Remover vértice (e suas arestas incidentes)\n");
            printf("2. Remover aresta\n");
            printf("3. Continuar para salvar\n");
            printf("Escolha uma opção: ");

            if (scanf("%d", &opcaoRemocao) != 1) {
                printf("Opção inválida.\n");
                limpaEntrada();
                continue;
            }

            if (opcaoRemocao == 1) {
                int vertice;
                printf("ID do vértice a remover: ");
                if (scanf("%d", &vertice) != 1) {
                    printf("ID inválido.\n");
                    limpaEntrada();
                } else if (vertice < 1 || vertice > GInumeroVerticesMax(g) ||
                           !GBexisteIdVertice(g, vertice)) {
                    printf("Vértice %d não existe no grafo.\n", vertice);
                } else {
                    removeVertice(g, vertice);
                    printf("Vértice %d e suas arestas incidentes foram removidos.\n", vertice);
                }
            } else if (opcaoRemocao == 2) {
                int aresta;
                printf("ID da aresta a remover: ");
                if (scanf("%d", &aresta) != 1) {
                    printf("ID inválido.\n");
                    limpaEntrada();
                } else if (aresta < 1 || aresta > GInumeroArestasMax(g) ||
                           !GBexisteIdAresta(g, aresta)) {
                    printf("Aresta %d não existe no grafo.\n", aresta);
                } else {
                    removeAresta(g, aresta);
                    printf("Aresta %d removida.\n", aresta);
                }
            } else if (opcaoRemocao != 3) {
                printf("Opção inválida.\n");
            }
        } while (opcaoRemocao != 3);

        limpaEntrada();

        printf("\nNome do arquivo para salvar (ex: grafo.txt): ");
        if (scanf("%255s", nomeArquivo) != 1) {
            snprintf(nomeArquivo, sizeof(nomeArquivo), "grafo.txt");
            printf("Nome inválido; usando %s\n", nomeArquivo);
        }

        if (!GBsalvaGrafo(g, nomeArquivo)) {
            printf("\nNão foi possível salvar em \"%s\".\n", nomeArquivo);
            GGdestroiGrafo(g);
            return 1;
        }
        printf("Grafo salvo em \"%s\" (formato próprio / reload).\n", nomeArquivo);

        printf("\nExportar Graphviz DOT? (1=sim, 0=não): ");
        int querDot;
        if (scanf("%d", &querDot) != 1) {
            querDot = 0;
        }

        if (querDot) {
            printf("Grafo dirigido? (1=sim digraph/-> , 0=não graph/-- ): ");
            if (scanf("%d", &dirigido) != 1) {
                dirigido = 1;
            }
            dirigido = dirigido ? 1 : 0;

            printf("Nome do arquivo .dot (ex: grafo.dot): ");
            if (scanf("%255s", nomeDot) != 1) {
                snprintf(nomeDot, sizeof(nomeDot), "grafo.dot");
                printf("Nome inválido; usando %s\n", nomeDot);
            }

            if (GBexportaDot(g, nomeDot, dirigido)) {
                printf("DOT exportado em \"%s\"\n", nomeDot);
                printf("Para gerar imagem (CMD):\n");
                printf("  dot -Tpng %s -o grafo.png\n", nomeDot);
            } else {
                printf("Falha ao exportar DOT em \"%s\".\n", nomeDot);
            }
        }

        printf("\nVértices: %d | Arestas: %d\n",
                GInumeroVertices(g), GInumeroArestas(g));

        GGdestroiGrafo(g);

    } else if (opcao == 2) {
        char nomeArquivo[256];
        char nomeDot[256];
        int dirigido;

        printf("\n=== Converter Arquivo para Graphviz (DOT) ===\n\n");

        printf("Informe o nome do arquivo do grafo salvo (ex: grafo.txt): ");
        if (scanf("%255s", nomeArquivo) != 1) {
            printf("Nome de arquivo inválido.\n");
            return 1;
        }

        Grafo g = GGcarregaGrafo(nomeArquivo);
        
        if (g == NULL) {
            printf("\nFalha ao carregar o grafo do arquivo \"%s\".\n", nomeArquivo);
            return 1;
        }
        printf("Grafo carregado com sucesso de \"%s\"!\n", nomeArquivo);

        printf("\nGrafo dirigido? (1=sim digraph/-> , 0=não graph/-- ): ");
        if (scanf("%d", &dirigido) != 1) {
            dirigido = 1;
        }
        dirigido = dirigido ? 1 : 0;

        printf("Nome do arquivo .dot de saída (ex: grafo.dot): ");
        if (scanf("%255s", nomeDot) != 1) {
            snprintf(nomeDot, sizeof(nomeDot), "grafo.dot");
            printf("Nome inválido; usando %s\n", nomeDot);
        }

        if (GBexportaDot(g, nomeDot, dirigido)) {
            printf("\nDOT exportado com sucesso em \"%s\"!\n", nomeDot);
            printf("Para gerar a imagem via terminal (Graphviz):\n");
            printf("  dot -Tpng %s -o grafo.png\n", nomeDot);
        } else {
            printf("\nFalha ao exportar o DOT em \"%s\".\n", nomeDot);
        }

        printf("\nVértices carregados: %d | Arestas carregadas: %d\n",
                GInumeroVertices(g), GInumeroArestas(g));

        GGdestroiGrafo(g);

    } else {
        printf("Opção inválida.\n");
        return 1;
    }

    return 0;
}