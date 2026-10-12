#include <stdio.h>
#include <stdio.h>

#include "algoritmos/algoritmos.h"

int main(void) {

    printf("Iniciando programa...\n");
    fflush(stdout);

    Grafo g = GGcarregaGrafo("grafo.txt");

    if (g == NULL) {
        printf("Erro: Ponteiro do grafo é NULL!\n");
        return 1;
    }

    BEL(g, 1);

    return 0;
}