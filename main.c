#include <stdio.h>
#include <stdio.h>

#include "algoritmos/algoritmos.h"

int main(void) {

    printf("Iniciando programa...\n");
    fflush(stdout);

    Grafo g = GGcarregaGrafo("grafo2.txt");

    if (g == NULL) {
        printf("Erro: Ponteiro do grafo é NULL!\n");
        return 1;
    }
        
    float p[15] = {
        0.0,  // Índice 0: Não utilizado[cite: 10]
        4.0,  // Índice 1:  Aresta (1 -- 2)
        2.0,  // Índice 2:  Aresta (1 -- 3)
        5.0,  // Índice 3:  Aresta (2 -- 4)
        1.0,  // Índice 4:  Aresta (2 -- 5)
        8.0,  // Índice 5:  Aresta (3 -- 6)
        3.0,  // Índice 6:  Aresta (3 -- 7)
        2.0,  // Índice 7:  Aresta (4 -- 5)
        6.0,  // Índice 8:  Aresta (4 -- 8)
        3.0,  // Índice 9:  Aresta (5 -- 8)
        1.0,  // Índice 10: Aresta (6 -- 7)
        7.0,  // Índice 11: Aresta (6 -- 9)
        4.0,  // Índice 12: Aresta (7 -- 9)
        2.0,  // Índice 13: Aresta (8 -- 10)
        5.0   // Índice 14: Aresta (9 -- 10)
    };

    // BEL(g, 1);
    //   BEP(g, 1);
    AGM(g, p);
    
    return 0;
}