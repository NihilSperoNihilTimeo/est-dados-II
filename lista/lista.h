#ifndef LISTA_H
#define LISTA_H

typedef struct no No;
typedef struct lista *Lista;

Lista Lcria();

void Ldestroi(Lista l);

int Lvazia(Lista l);

int Lcheia(Lista l);

int Ltamanho(Lista l);

#endif