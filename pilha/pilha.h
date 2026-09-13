#ifndef PILHA_H
#define PILHA_H

// Structs 
struct pilha;
typedef struct pilha* Pilha;

// Cria uma pilha vazia
Pilha Pcria();

// Destrói a pilha 
void Pdestroi(Pilha p);

// Examina se a pilha está vazia
int Pvazia(Pilha p);

// Examina se a pilha está cheia
int Pcheia(Pilha p);

// Retorna a quantidade de elementos da pilha
int Ptamanho(Pilha p);

// Retorna o elemento no topo da pilha (= top)
void* Pexamina(Pilha p);

// Insere o elemento no topo da pilha (= push)
int Pinsere(Pilha p, void* elemento);

// Remove o elemento do topo da pilha (= pop)
void* Premove(Pilha p);

#endif 