#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

lista* createLista() {
    lista* ls = malloc(sizeof(lista));
    return ls;
};

void listaLibera(lista* ls) {
    ElemLista* thisElem = ls->head;
    ElemLista* nextElem;
    while(thisElem) {
        nextElem = thisElem->next;
        free(thisElem);
        thisElem = nextElem;
    }
    free(ls);
};

void listaInsere(lista* ls, Camara*camara, int heuristica, int fn) {
    ElemLista* thisElem = ls;
    ElemLista* nextElem;
    while(thisElem) {
        nextElem = thisElem->next
        if(!nextElem) break;
        thisElem = nextElem;
    }
    if(thisElem) {
        thisElem->next = malloc(sizeof(ElemLista));
        thisElem = thisElem->next;
    } else {
        thisElem = malloc(sizeof(ElemLista));
        ls->head = thisElem;
    }
    thisElem = thisElem->next;
    thisElem->camara = camara;
    thisElem->fn = fn;
};

void listaRemove(lista* ls, char* id) {
    ElemLista* thisElem = ls;
    ElemLista *prevElem, *nextElem;
    while(ls) {
        if(strcmp(getId(ls->camara), id) == 0) {
            nextElem = ls->next;

        }
        ls = ls->next;
    }
};

void listaInsereOrd(Camara *camara) {

};
void listaImprime(lista* ls);
