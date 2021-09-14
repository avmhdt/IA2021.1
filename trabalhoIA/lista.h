#ifndef LISTA_H
#define LISTA_H

#include "labyrinth.h"

typedef struct elementoLista {
    struct ElemLista *prev;
    struct ElemLista *next;

    Camara* camara;
    int fn;
} ElemLista;

typedef struct ElemLista* lista;

lista* listaCria();
void listaLibera(lista* ls);
void listaInsere(lista* ls, Camara* camara, int fn);
void listaRemove(lista* ls, char* id);
void listaInsereOrd(lista* ls, Camara *camara);
void listaImprime(lista* ls);

#endif // LISTA_H
