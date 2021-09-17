#ifndef SEARCH_H
#define SEARCH_H

#include "labyrinth.h"
#include "fila.h"
#include "pilha.h"

//backtracking começo
void backtracking(Camara* start, char* objetivo, int regra[4]);
int bt_search(Pilha* atual, Pilha* visitados, char*raiz, char* objetivo, int regra[4], int *folhas, double* custo);
int visitado(char *objetivo, Pilha *pilha);
//backtracking fim

//busca largura começo
int ehPai(ElemFila* atual, Camara* camara);
int ehPai2(ElemFila* atual, Camara* camara);
int caminho(Fila* fechados, int idPai, char* final);
int existeMenor(Fila* fila, ElemFila* no, char* id);
ElemFila* proxEscolhido(ElemFila* atual);
Camara* buscaLargura(Camara* start, char* objetivo, int regra[4]);
//busca largura fim

//busca profundidade começo
Camara* buscaProfundidade(Camara* start, char* objetivo, int regra[4], int profundidade);
//busca profundidade fim

/*
typedef struct heuristica {
    struct hr* prev;
    struct hr* next;

    Camara* camara;
    int heuristica;
} hr;

hr* hrCreate(Camara* camara, hr* parent, int heuristica);
void hrDelete(hr* thisHr);

hr* hrReset(hr* thisHr);
void hrPrint(hr* thisHr);
*/
//void gulosa(Camara* start, char* objetivo, int regra[4], hr* heuristica);
void gulosa(Camara* start, char* objetivo);
void ida(Camara* start, char* objetivo, int regra[4]);

//começo busca A*
Camara* buscaA(Camara* start, char* objetivo);
//fim busca A*

//começo busca ordenada
void buscaOrdenada(Camara* start, char* objectivo, int regra[4]);
//fim busca ordenada
#endif // SEARCH_H
