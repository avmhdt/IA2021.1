#include "labyrinth.h"

typedef struct node{
    struct Camara* camara;
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
No* buscaLargura(No* raiz, char* objetivo, int regra[4]);