#include <stdlib.h>
#include "lista.h"

typedef struct no {
    void *dado;
    struct no *ant;
    struct no *prox;
} No;

struct lista {
    No *inicio;
    No *fim;
    int qtd;
};

Lista Lcria() {
    Lista l = (Lista) malloc(sizeof(struct lista));

    if (l != NULL) {
        l->inicio = NULL;
        l->fim = NULL;
        l->qtd = 0;
    }

    return l;
}

void Ldestroi(Lista l) {
    if (l != NULL) {
        No *atual = l->inicio;
        No *prox;

        while (atual != NULL) {
            prox = atual->prox;
            free(atual);
            atual = prox;
        }

        free(l);
    }
}

int Lvazia(Lista l) {
    if (l == NULL) {
        return 1;
    }
    if (l->qtd == 0) {
        return 1;
    }

    return 0;
}

int Lcheia(Lista l) {
    return 0;
}

int Ltamanho(Lista l) {
    if (l == NULL) {
        return 0;
    }

    return l->qtd;
}

void* Lexamina(Lista l, int posicao) {
    if (l == NULL) {
        return NULL;
    }
    if (posicao < 0 || posicao >= l->qtd) {
        return NULL;
    }

    No *atual = l->inicio;

    for (int i = 0; i < posicao; i++) {
        atual = atual->prox;
    }

    return atual->dado;
}

int Llocaliza(Lista l, void *elemento) {
    if (l == NULL) {
        return -1;
    }

    No *atual = l->inicio;
    int i = 0;

    while (atual != NULL) {
        if (atual->dado == elemento) {
            return i;
        }
        atual = atual->prox;
        i++;
    }

    return -1;
}
 
void Linsere(Lista l, void *elemento, int posicao) {
    if (l == NULL) {
        return;
    }
    if (posicao < 0 || posicao > l->qtd) {
        return;
    }

    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) {
        return;
    }
    novo->dado = elemento;

    if (l->qtd == 0) {
        /* lista vazia: novo é o único nó */
        novo->ant = NULL;
        novo->prox = NULL;
        l->inicio = novo;
        l->fim = novo;
    } else if (posicao == 0) {
        /* insere no início */
        novo->ant = NULL;
        novo->prox = l->inicio;
        l->inicio->ant = novo;
        l->inicio = novo;
    } else if (posicao == l->qtd) {
        /* insere no fim */
        novo->prox = NULL;
        novo->ant = l->fim;
        l->fim->prox = novo;
        l->fim = novo;
    } else {
        /* insere no meio: encontra o nó que hoje ocupa "posicao" */
        No *atual = l->inicio;
        for (int i = 0; i < posicao; i++) {
            atual = atual->prox;
        }
        novo->prox = atual;
        novo->ant = atual->ant;
        atual->ant->prox = novo;
        atual->ant = novo;
    }

    l->qtd++;
}

void* Lremove(Lista l, int posicao) {
    if (l == NULL) {
        return NULL;
    }
    if (posicao < 0 || posicao >= l->qtd) {
        return NULL;
    }

    No *atual = l->inicio;
    for (int i = 0; i < posicao; i++) {
        atual = atual->prox;
    }

    void *dado = atual->dado;

    if (atual->ant != NULL) {
        atual->ant->prox = atual->prox;
    } else {
        l->inicio = atual->prox;
    }

    if (atual->prox != NULL) {
        atual->prox->ant = atual->ant;
    } else {
        l->fim = atual->ant;
    }

    free(atual);
    l->qtd--;

    return dado;
}