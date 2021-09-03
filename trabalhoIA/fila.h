//https://gist.github.com/IsaacBruno/6c0dc146ef4bfe2f8038c954219d0530
#ifndef FILA_H
#define FILA_H

#include "labyrinth.h"

struct fila
{
    struct elemento *inicio;
    struct elemento *final;
};

struct elemento
{
    int idPai;
    int id;
    int fechado;
    Camara *camara;
    struct elemento *prox;
    struct elemento *ant;
};
typedef struct elemento Elem;
typedef struct fila Fila;

Fila* fila_cria();
void fila_libera(Fila *fila);
int fila_vazia(Fila *fila);
int fila_tamanho(Fila *fila);
int fila_insere(Fila *fila, Camara* camara, int idPai, int id);

//int fila_remove(Fila *fila);
/*
int fila_consulta(Fila *fila, int *dado);
void fila_imprime(Fila *fila);
*/

#endif