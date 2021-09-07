#ifndef SEARCH_H
#define SEARCH_H

#include "labyrinth.h"
#include "fila.h"
#include "pilha.h"




void backtracking(Camara* start, char* objetivo, int regra[4]);
int bt_search(Pilha* atual, Pilha* visitados, char*raiz, char* objetivo, int regra[4]);
int visitado(char *objetivo, Pilha *pilha);

//backtracking fim


//buscaLargura começo
int ehPai(ElemFila* atual, Camara* camara);
ElemFila* proxEscolhido(ElemFila* atual);
Camara* buscaLargura(Camara* start, char* objetivo, int regra[4]);
//buscaLargura fim

#endif // SEARCH_H