#include "labyrinth.h"
#include "fila.h"

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
//backtracking fim
*/
//buscaLargura começo
int ehPai(Elem* atual, Camara* camara);
Camara* buscaLargura(Camara* start, char* objetivo, int regra[4]);
//buscaLargura fim