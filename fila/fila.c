#include <stdlib.h>
#include "fila.h"

typedef struct no {
    void *dado;
    struct no *prox;
} No;

struct fila {
    No *inicio;
    No *fim;
    int qtd;
};

Fila Fcria() {
    Fila f = (Fila) malloc(sizeof(struct fila));

    if (f != NULL) {
        f->inicio = NULL;
        f->fim = NULL;
        f->qtd = 0;
    }

    return f;
}

void Fdestroi(Fila f) {
    if (f != NULL) {
        No *atual = f->inicio;
        No *prox;

        while (atual != NULL) {
            prox = atual->prox;
            free(atual);
            atual = prox;
        }

        free(f);
    }
}

int Fvazia(Fila f) {
    if (f == NULL) {
        return 1;
    }
    if (f->qtd == 0) {
        return 1;
    }

    return 0;
}

int Fcheia(Fila f) {
    return 0;
}

int Ftamanho(Fila f) {
    if (f == NULL) {
        return 0;
    }

    return f->qtd;
}

void* Fexamina(Fila f) {
    if (f == NULL) {
        return NULL;
    }
    if (f->qtd == 0) {
        return NULL;
    }

    return f->inicio->dado;
}

void Finsere(Fila f, void *elemento) {
    if (f == NULL) {
        return;
    }

    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) {
        return;
    }
    novo->dado = elemento;
    novo->prox = NULL;

    if (f->qtd == 0) {
        /* fila vazia: novo é o único nó */
        f->inicio = novo;
        f->fim = novo;
    } else {
        /* encaixa no fim e atualiza o ponteiro fim */
        f->fim->prox = novo;
        f->fim = novo;
    }

    f->qtd++;
}
void* Fremove(Fila f) {
    if (f == NULL) {
        return NULL;
    }
    if (f->qtd == 0) {
        return NULL;
    }

    No *removido = f->inicio;
    void *dado = removido->dado;

    f->inicio = removido->prox;

    if (f->inicio == NULL) {
        /* a fila ficou vazia: fim também deve apontar para NULL */
        f->fim = NULL;
    }

    free(removido);
    f->qtd--;

    return dado;
}