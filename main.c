#include <stdio.h>
#include <stdlib.h>
#include "pilha/pilha.h"

int main() {

    Pilha p = Pcria();

    int op = 0, num;
    do {
        printf("1. Inserir\n");
        printf("2. Remover\n");
        printf("3. Exibir topo\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);

        switch (op) {
            case 1: {
                int* num = (int*) malloc(sizeof(int));
                
                if (num == NULL) {
                    printf("Erro na alocação para novo número!\n");
                    break;
                }

                printf("Digite um número: ");
                scanf("%d", num);

                if (Pinsere(p, num)) {
                    printf("[%d] inserido com sucesso!\n", *num);
                } else {
                    printf("Falha!\n");
                    free(num);
                }
            
            break;}

            case 2: {
                int *removido = (int *) Premove(p);
                if (removido != NULL) {
                    printf("[%d]: topo removido com sucesso! \n", *removido);
                    free(removido);
                } else {
                    printf("Remoção inválida!\n");
                }
            break;}

            case 3: {
                int* dados = (int*) Pexamina(p);
                if (dados != NULL) {
                    printf("Conteúdo topo: %d\n", *dados);
                } else {
                    printf("Verificação inválida!\n");
                }
            break; }

            default:
                break;
        }
    } while (op != 4);

    Pdestroi(p);

    return 0;
}