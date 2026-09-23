#ifndef LISTAESPEC_H
#define LISTAESPEC_H

typedef struct no No;
typedef struct lista *Lista;

Lista Lcria();

void Ldestroi(Lista l);

int Lvazia(Lista l);

int Lcheia(Lista l);

int Ltamanho(Lista l);

void* Lexamina(Lista l, int posicao);

int Llocaliza(Lista l, void *elemento);

void Linsere(Lista l, void *elemento, int posicao);

void* Lremove(Lista l, int posicao);

#endif