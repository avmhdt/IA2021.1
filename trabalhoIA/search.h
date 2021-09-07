#ifndef SEARCH_H
#define SEARCH_H

#include "labyrinth.h"
#include "fila.h"
#include "pilha.h"

//backtracking começo
/*
typedef struct {
    Camara* camara;
    struct No** filhos;
    struct No* pai;
} No;

Camara* getCamara(No* node);
void setCamara(No* node, Camara* camara);

No* getPai(No* node);
void setPai(No* node, No* pai);

No* getFilho(No* node, int pos);
void insertFilho(No* node, No* filho);
void allocFilhos(No* node);

No* backtracking(No* raiz, char* objetivo, int regra[4]);


int match(char* key, No* node);


void backtracking(Camara* start, char* objetivo, int regra[4]);
int bt_search(Pilha* atual, Pilha* visitados, char*raiz, char* objetivo, int regra[4]);
int visitado(char *objetivo, Pilha *pilha);
No* buscaLargura(No* raiz, char* objetivo, int regra[4]);

//backtracking fim
*/

//buscaLargura começo
int ehPai(ElemFila* atual, Camara* camara);
ElemFila* proxEscolhido(ElemFila* atual);
Camara* buscaLargura(Camara* start, char* objetivo, int regra[4]);
//buscaLargura fim

#endif // SEARCH_H