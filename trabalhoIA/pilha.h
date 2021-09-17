#ifndef PILHA_H
#define PILHA_H

#include "labyrinth.h"

typedef struct elementoPilha* Pilha;

struct elementoPilha
{
    Camara *camara;
    struct elementoPilha *prox;
    int profundidade;
    int id;
    int idPai;
    int custo;
};

typedef struct elementoPilha ElemPilha;

Pilha* pilha_cria();
void pilha_libera(Pilha *pilha);
int pilha_vazia(Pilha *pilha);
int pilha_insere(Pilha *pilha, Camara* camara);
int pilha_remove(Pilha *pilha);
int pilha_imprime(Pilha *pilha);

#endif