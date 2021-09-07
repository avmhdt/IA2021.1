#ifndef PILHA_H
#define PILHA_H

#include "labyrinth.h"

typedef struct elementoPilha* Pilha;

struct elementoPilha
{
//    int dado;
    Camara *camara;
    struct elementoPilha *prox;
};

typedef struct elementoPilha ElemPilha;

Pilha* pilha_cria();
void pilha_libera(Pilha *pilha);
int pilha_vazia(Pilha *pilha);
int pilha_insere(Pilha *pilha, Camara* camara);
int pilha_remove(Pilha *pilha);
void pilha_imprime(Pilha *pilha);

#endif