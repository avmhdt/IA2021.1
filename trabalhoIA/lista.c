#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

lista* listaCria() {
    lista* ls = malloc(sizeof(lista));
    if(ls!=NULL)
        *ls = NULL;
    return ls;
};

void listaLibera(lista* ls) {
    ElemLista* thisElem = ls;
    ElemLista* nextElem;
    while(thisElem) {
        nextElem = thisElem->next;
        free(thisElem);
        thisElem = nextElem;
    }
    free(ls);
};

void listaInsere(lista* ls, Camara*camara, int fn) {
    ElemLista* thisElem = ls;
    ElemLista* nextElem;
    while(thisElem) {
        nextElem = thisElem->next;
        if(!nextElem) break;
        thisElem = nextElem;
    }
    if(thisElem) {
        thisElem->next = malloc(sizeof(ElemLista));
        thisElem = thisElem->next;
    } else {
        thisElem = malloc(sizeof(ElemLista));
        ls = thisElem;
    }
    thisElem = thisElem->next;
    thisElem->camara = camara;
    thisElem->fn = fn;
};

void listaRemove(lista* ls, char* id) {
    ElemLista* thisElem = ls;
    ElemLista *prevElem, *nextElem;
    while(thisElem) {
        if(strcmp(getId(thisElem->camara), id) == 0) {
            nextElem = thisElem->next;
            prevElem = thisElem->prev;
            prevElem->next = nextElem;
            nextElem->prev = prevElem;
            free(thisElem);
            break;
        }
        thisElem = thisElem->next;
    }
    return;
};
/*
void listaInsereOrd(lista* ls, Camara *camara) {
    int thisHn = camara->hn;
    ElemLista* thisElem = ls;
    ElemLista *nextElem, *aux;
    if(!(*ls)) {
        aux = malloc(sizeof(ElemLista));
        aux->camara = camara;
        aux->fn = camara->hn; // so para a gulosa
        *ls = aux;
        return;
    }
    if(*thisElem)
    while(thisElem) {
        nextElem = thisElem->next;
        if(thisElem->camara->hn < thisHn && (!nextElem || nextElem->camara->hn >= thisHn)) {
            aux = malloc(sizeof(ElemLista));
            aux->camara = camara;

            // fn aqui
            aux->fn = camara->hn; // so para a gulosa

            thisElem->next = aux;
            aux->prev = thisElem;
            aux->next = nextElem;
            if(nextElem){
                nextElem->prev = aux;
            }
            return;
        }
        thisElem = nextElem;
    }

    // resto aqui - inserir quando vazia ou quando primeiro elemento eh maior

};


void listaInsereOrd(lista* ls, Camara *camara) {
    ElemLista *aux = malloc(sizeof(ElemLista));
    aux->prev = NULL; aux->next = NULL;
    aux->camara = camara;
    aux->fn = camara->hn; // so para a gulosa

    int thisHn = camara->hn;
    ElemLista *thisElem = *ls;
    ElemLista *nextElem;
    if(!(*ls)) {
        *ls = aux;
        return;
    }
    if((*ls)->fn > thisHn) {
        aux->next = *ls;
        (*ls)->prev = aux;
        (*ls) = aux;
        return;
    }
    while(thisElem) {
        nextElem = thisElem->next;
        if(thisElem->camara->hn < thisHn && (!nextElem || nextElem->camara->hn >= thisHn)) {
            thisElem->next = aux;
            aux->prev = thisElem;
            aux->next = nextElem;
            if(nextElem){
                nextElem->prev = aux;
            }
            return;
        }
        thisElem = nextElem;
    }
    return;
}

void listaImprime(lista* ls) {
    ElemLista *thisElem = *ls;
    while(thisElem) {
        printf("%s \t %d\n", thisElem->camara, thisElem->fn);
        thisElem = thisElem->next;
    }
};
*/
