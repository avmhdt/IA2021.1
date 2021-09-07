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

lista* createLista();
void listaLibera(lista* ls);
void listaInsere(Camara* camara, hr *heur);
void listaRemove(char* id);
void listaInsereOrd(Camara *camara);
void listaImprime(lista* ls);

#endif // LISTA_H
