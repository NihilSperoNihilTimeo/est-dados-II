#include <stdio.h>
#include <stdlib.h>

#include "algoritmos/algoritmos.h"

// Lê o vetor de pesos (posição 0 sem uso). Retorna NULL se a operação for cancelada.
static float* lePesos(Grafo g) {
    int op;
    int nA = GInumeroArestas(g);
    printf("Deseja criar (1) ou carregar (2) o vetor com os pesos de cada aresta? ");
    scanf("%d", &op);

    if (op == 1) {
        float *p = (float*) calloc((nA + 1), sizeof(float));

        printf("Preencha o vetor de pesos [%d arestas]\n", nA);
        for (int i = 1; i <= nA; i++) {
            printf("\t[%d]: ", i);
            scanf("%f", &p[i]);
        }
        return p;
    }

    if (op == 2) {
        char nomeArquivo[100];
        printf("Digite o nome do arquivo de pesos (ex: pesos.txt): ");
        scanf("%99s", nomeArquivo);

        FILE *arq = fopen(nomeArquivo, "r");
        if (arq == NULL) {
            printf("Não foi possível abrir o arquivo '%s'.\n", nomeArquivo);
            return NULL;
        }

        float *p = (float*) calloc((nA + 1), sizeof(float));
        int arestasLidas = 0;

        for (int i = 1; i <= nA; i++) {
            if (fscanf(arq, "%f;", &p[i]) != 1) {
                break;
            }
            arestasLidas++;
        }
        fclose(arq);

        if (arestasLidas != nA) {
            printf("O arquivo contém apenas %d pesos, mas o grafo exige %d\n", arestasLidas, nA);
            printf("Operação cancelada!\n");
            free(p);
            return NULL;
        }

        printf("Pesos carregados com sucesso! (%d arestas lidas)\n", arestasLidas);
        return p;
    }

    printf("Opção inválida!\n");
    return NULL;
}

int main(void) {
    char nomeArquivo[256];
    printf("Digite o nome do arquivo .txt com o grafo que se deseja manipular (ex: grafo.txt): ");
    if (scanf("%255s", nomeArquivo) != 1) {
        snprintf(nomeArquivo, sizeof(nomeArquivo), "grafo.txt");
        printf("Nome inválido; usando %s\n", nomeArquivo);
    }

    Grafo g = GGcarregaGrafo(nomeArquivo);

    if (g == NULL) {
        printf("Erro no carregamento de '%s'\n\tSaindo...", nomeArquivo);
        return 1;
    }

    int op;
    do
    {
        printf("======Algoritmos sobre grafos======\n");
        printf("1. Árvore Geradora Mínima (AGM)\n");
        printf("2. Busca em Largura (BEL)\n");
        printf("3. Busca em Profundidade (BEP)\n");
        printf("4. Caminho mais curto (CMC)\n");
        printf("5. Componentes conexos (CC)\n");
        printf("6. SAIR\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);

        switch(op) {
            case 1: {
                int op;
                printf("Deseja criar (1) ou carregar (2) o vetor com os pesos de cada aresta? ");
                scanf("%d", &op);
                
                if (op == 1) {
                    int nA = GInumeroArestas(g);
                    float *p = (float*) calloc((nA+ 1), sizeof(float));

                    printf("Preencha o vetor de pesos [%d arestas]\n", nA);
                    for (int i = 1; i <= nA; i++) {
                        printf("\t[%d]: ", i);
                        scanf("%f", &p[i]);
                    }
                    AGM(g, p);
                    free(p);

                } else if (op == 2) {
                    char nomeArquivo[100];
                    printf("Digite o nome do arquivo de pesos (ex: pesos.txt): ");
                    scanf("%s", nomeArquivo);
                    
                    FILE *arq = fopen(nomeArquivo, "r");
                    if (arq == NULL) {
                        printf("Não foi possível abrir o arquivo '%s'.\n", nomeArquivo);
                    } else {
                        int nA = GInumeroArestas(g);
                        float *p = (float*) calloc((nA + 1), sizeof(float)); 
                        
                        int arestasLidas = 0;
                        int leituraBemSucedida = 1;
                        
                        for (int i = 1; i <= nA; i++) {    
                            if (fscanf(arq, "%f;", &p[i]) == 1) {
                                arestasLidas++;
                            } else {
                                leituraBemSucedida = 0;
                                break; 
                            }
                        }
                        
                        fclose(arq);
                        
                        if (leituraBemSucedida && arestasLidas == nA) {
                            printf("Pesos carregados com sucesso! (%d arestas lidas)\n", arestasLidas);
                            AGM(g, p);
                        } else {
                            printf("Aarquivo contém apenas %d pesos, mas o grafo exige %d\n", arestasLidas, nA);
                            printf("Operação cancelada!\n");
                        }  
                        free(p);
                    }
                } else {
                    printf("Opção inválida!\n");
                    break;
                }                
            break;}

            case 2: {
                int v;    
                printf("Digite o vértice inicial: ");
                scanf("%d", &v);
                if (GBexisteIdVertice(g, v)) {
                    BEL(g, v);
                } else {
                    printf("Vértice não existe no grafo carregado!\n");
                }
            break;}

            case 3: {
                int v;    
                printf("Digite o vértice inicial: ");
                scanf("%d", &v);
                if (GBexisteIdVertice(g, v)) {
                    BEP(g, v);
                } else {
                    printf("Vértice não existe no grafo carregado!\n");
                }
            break; }

            case 4: {
                int a, b;
                printf("Digite o vértice de partida: ");
                scanf("%d", &a);
                printf("Digite o vértice de chegada: ");
                scanf("%d", &b);

                if (!GBexisteIdVertice(g, a) || !GBexisteIdVertice(g, b)) {
                    printf("Vértice não existe no grafo carregado!\n");
                    break;
                }

                float *p = lePesos(g);
                if (p != NULL) {
                    CMC(g, p, a, b);
                    free(p);
                }
            break;}

            case 5:  
                CC(g);
            break;

            case 6:              
            break;

            default:
                printf("Opção inválida!\n");
            break;
        }

    } while (op != 6);

    return 0;
}