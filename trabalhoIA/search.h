#ifndef SEARCH_H
#define SEARCH_H

#include "labyrinth.h"
#include "fila.h"
#include "pilha.h"

//backtracking começo
void backtracking(Camara* start, char* objetivo, int regra[4]);
int bt_search(Pilha* atual, Pilha* visitados, char*raiz, char* objetivo, int regra[4]);
int visitado(char *objetivo, Pilha *pilha);
//backtracking fim

//busca largura começo
int ehPai(ElemFila* atual, Camara* camara);
ElemFila* proxEscolhido(ElemFila* atual);
Camara* buscaLargura(Camara* start, char* objetivo, int regra[4]);
//busca largura fim

//busca profundidade começo
Camara* buscaProfundidade(Camara* start, char* objetivo, int regra[4], int profundidade); //Modificada-> Não abertura de estados já visitados
Camara* buscaProfundidade2(Camara* start, char* objetivo, int regra[4], int profundidade); //Sem modificações
//busca profundidade fim

//começo busca A*
Camara* buscaA(Camara* start, char* objetivo, int regra[4]);
//fim busca A*
#endif // SEARCH_H