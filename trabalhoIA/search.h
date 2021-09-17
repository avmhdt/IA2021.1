#ifndef SEARCH_H
#define SEARCH_H

#include "labyrinth.h"
#include "fila.h"
#include "pilha.h"

//backtracking começo
void backtracking(Camara* start, char* objetivo, int regra[4]);
int bt_search(Pilha* atual, Pilha* visitados, char*raiz, char* objetivo, int regra[4], int *folhas, int* custo,int* profundidadeMax);
int visitado(char *objetivo, Pilha *pilha);
//backtracking fim

//busca largura começo
int ehPai(ElemFila* atual, Camara* camara);
int ehPai2(ElemFila* atual, Camara* camara);
int caminho(Fila* fechados, int idPai, char* final);
int existeMenor(Fila* fila, ElemFila* no, char* id);
Camara* buscaLargura(Camara* start, char* objetivo, int regra[4]);
//busca largura fim

//busca profundidade começo
Camara* buscaProfundidade(Camara* start, char* objetivo, int regra[4], int profundidade);
//busca profundidade fim

//busca gulosa começo
void fecha(Fila* abertos, Fila* fechados);
int fechado(Camara* camara, Fila* fechados);
int abreVizinhos(Fila* fechados, Fila* abertos);
int g_search(Fila* abertos, Fila* fechados, char* objetivo, int* fr);
void gulosa(Camara* start, char* objetivo);
//busca gulosa fim

int minFnDescartado(Pilha* descartados);
void ida(Camara* start, char* objetivo, int regra[4]);

//começo busca A*
Camara* buscaA(Camara* start, char* objetivo);
//fim busca A*

//começo busca ordenada
void buscaOrdenada(Camara* start, char* objectivo, int regra[4]);
//fim busca ordenada
#endif // SEARCH_H
