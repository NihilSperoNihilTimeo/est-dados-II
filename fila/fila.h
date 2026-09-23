#ifndef FILA_H
#define FILA_H

typedef struct no No;
typedef struct fila *Fila;

Fila Fcria();

void Fdestroi(Fila f);

int Fvazia(Fila f);

int Fcheia(Fila f);

int Ftamanho(Fila f);

void* Fexamina(Fila f);

void Finsere(Fila f, void* elemento);

void* Fremove(Fila f);

#endif