#include <stdlib.h>
#include "pilha.h"

// Struct do node principal, que armazena o dado que queremos e um ponteiro para o próximo
struct node {
    void* dados;
    struct node* proximo;
};
typedef struct node Node;

// Struct principal da pilha
struct pilha {
    struct node* topo;
    int qtd;
};

// Cria a pilha, alocando memória, aterrando o topo e inicializando o contador
Pilha Pcria() {
    Pilha p = (Pilha) malloc(sizeof(struct pilha));
   
    if (p != NULL) {
        p->topo = NULL;
        p->qtd = 0;
    }

    return p;
}

// Percorre a pilha, liberando cada node
void Pdestroi(Pilha p) {
    if (p != NULL) {
        Node* atual = p->topo;
        Node* proximoNode;

        while ( atual  != NULL) {
            proximoNode = atual->proximo;
            free(atual);
            atual = proximoNode;
        }       

        free(p);
    }
}

// Verifica se há elementos na pilha, retornando 0 caso existam
int Pvazia(Pilha p) {
    if (p == NULL) {
        return 1;
    }
    if (p->topo == NULL){
        return 1;
    }

    return 0;
}

// Uma pilha dinâmica somente ficará cheia se não houver mais espaço na memória
int Pcheia(Pilha p) {
    return 0;
}

// Retorna a quantidade de itens na pilha, valor armazenado na struct para facilitar
int Ptamanho(Pilha p) {
    if (p == NULL) {
        return 0;
    }

    return p->qtd;
}

// Apenas retorna o dado de quem está no topo
void* Pexamina(Pilha p) {
    if (p == NULL) {
        return NULL;
    }
    if (p->topo == NULL) {
        return NULL;
    }

    return p->topo->dados;
}

// .PUSH
int Pinsere(Pilha p, void* dado) {
    if (p == NULL) {
        return 0;
    }
    
    Node* node;
    node =  (Node*) malloc(sizeof(Node));

    if (node == NULL) {
        return 0;
    }

    node->dados = dado;
    node->proximo = p->topo;
    p->topo = node;
    p->qtd++;
    
    return 1;
}

// .POP
void* Premove(Pilha p) {
    if (p == NULL) {
        return NULL;
    }
    if (p->topo == NULL) {
        return NULL;
    }

    Node* temp = p->topo;
    void* dado = temp->dados;

    p->topo = p->topo->proximo;
    free(temp);
    p->qtd--;

    return dado;
}