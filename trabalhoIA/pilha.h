#ifndef PILHA_H
#define PILHA_H

#include "labyrinth.h"

typedef struct elemento* Pilha;

struct elemento
{
//    int dado;
    Camara *camara;
    struct elemento *prox;
};

typedef struct elemento Elem;

Pilha* pilha_cria();
void pilha_libera(Pilha *pilha);
int pilha_vazia(Pilha *pilha);
int pilha_insere(Pilha *pilha, Camara* camara);
int pilha_remove(Pilha *pilha);
void pilha_imprime(Pilha *pilha);

#endif
