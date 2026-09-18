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