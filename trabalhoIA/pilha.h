//https://gist.github.com/IsaacBruno/6c0dc146ef4bfe2f8038c954219d0530
#ifndef PILHA_H
#define PILHA_H

typedef struct elemento* Pilha;

Pilha* pilha_cria();
void pilha_libera(Pilha *pilha);
int pilha_vazia(Pilha *pilha);
int pilha_insere(Pilha *pilha, int dado);
int pilha_remove(Pilha *pilha);
void pilha_imprime(Pilha *pilha);

#endif