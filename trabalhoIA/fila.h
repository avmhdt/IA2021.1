#ifndef FILA_H
#define FILA_H

#include "labyrinth.h"

struct fila
{
    struct elementoFila *inicio;
    struct elementoFila *final;
};

struct elementoFila
{
    int idPai;
    int id;
    int custo;
    int fn;
    int profundidade;
    Camara *camara;
    struct elementoFila *prox;
    struct elementoFila *ant;
};
typedef struct elementoFila ElemFila;
typedef struct fila Fila;

Fila* fila_cria();
void fila_libera(Fila *fila);
int fila_vazia(Fila *fila);
int fila_tamanho(Fila *fila);
int fila_insere(Fila *fila, Camara* camara, int idPai, int id);

int fila_remove(Fila *fila);
int fila_remove_ord(Fila *fila, int id);
/*
int fila_consulta(Fila *fila, int *dado);
*/
int fila_imprime(Fila *fila);

int fila_insere_ord(Fila* fila, Camara* camara, int idPai, int id);
int fila_insere_ord_gn(Fila* fila, Camara* camara, int idPai, int id, int custoPai, int gn);

int fila_conta(Fila *fila);
//int fila_insere_ord_fn(Fila* fila, Camara* camara, int idPai, int id, int custoPai, int peso);
int fila_insere_ord_fn(Fila* fila, Camara* camara, int id, int peso, ElemFila* pai);
#endif
