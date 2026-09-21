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

Lista Lcria(){
    Lista l = (Lista) malloc(sizeof(struct lista));

    if ( l != NULL ){
        l->inicio = NULL;
        l->fim = NULL;
        l->qtd = 0;
    }

    return l; 
 }

  void Ldestroi( Lista l){
    if ( l != NULL){
        No* atual = l->inicio;
        No* prox;

        while (atual != NULL){
            prox = atual->prox;
            free(atual);
            atual = prox;
        }

        free(l);
    }
}

int Lvazia(Lista l){
    if (l == NULL){
        return 1;
    }
    if (l->qtd == 0){
        return 1;
    }

   return 0 ;
}

int Lcheia (Lista l){
    return 0;
}

int Ltamanho (Lista l){
    if (l == NULL){
        return 0;
    }

    return l->qtd;
}

int Lexamina(Lista l, int pos) {
    if (l == NULL || pos <= 0) {
        return NULL;
    }
    No *no = l->inicio;
    int i = 1;
    while (no != NULL && i < pos) {
        no = no->prox;
        i++;
    }

    if (no == NULL) {
        return 0;
    } else {
        return no->dado;
    }

}

int Llocaliza(Lista l, void* dado) {
    if (l == NULL) {
        return 0;
    }
    No *no = l->inicio;
    int i = 1;
    while (no != NULL && no->dado != dado) {
        no = no->prox;
        i++;
    }

    if (no == NULL) {
        return 0;
    } else {
        return i;
    }
}

int Linsere(Lista l, void* dado) {
    if (l == NULL) {
        return 0;
    }
    
    No *no;
    no =  (No*) malloc(sizeof(No));
    if (no == NULL) {
        return NULL;
    }
    
    no->dado = dado;
    no->prox = NULL;
    if (l->inicio == NULL) {
        l->inicio = no;
        no->ant = NULL;
    } else {
        l->fim->prox = no;
        no->ant = l->fim;
    }

    l->fim = no;
    l->qtd++;
    return 1;
}

int Lremove(Lista l, void* dado) {
    if (l == NULL) {
        return NULL;
    }
    if (l->fim == NULL) {
        return NULL;
    }
    No *no = l->inicio;
    while (no != NULL && no->dado != dado) {
        no = no->prox;
    }
    if (no == NULL) {
        return 0;
    }
    if (no->ant == NULL) {
        l->inicio = no->prox;
    } else {
        no->ant->prox = no->prox;
    }

    if (no->prox != NULL) {
        no->prox->ant = no->ant;
    } else {
        l->fim = no->ant;
    }

    
    free(no);
    l->qtd--;

    return 1;
}