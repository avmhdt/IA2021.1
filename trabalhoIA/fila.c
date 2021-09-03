//https://gist.github.com/IsaacBruno/6c0dc146ef4bfe2f8038c954219d0530 (código base)
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "labyrinth.h"

Fila* fila_cria()
{
    Fila *fi = (Fila*) malloc(sizeof(Fila));
    if(fi!=NULL)
        fi->inicio = fi->final = NULL;
    return fi;
}

void fila_libera(Fila *fila)
{
    if(fila!=NULL){
        Elem *no;
        while(fila->inicio){
            no = fila->inicio;
            fila->inicio = fila->inicio->prox;
            free(no);
        }
        free(fila);
    }
}

int fila_vazia(Fila *fila)
{
    if(fila==NULL || fila->inicio==NULL) return 1;
    return 0;
}

int fila_tamanho(Fila *fila)
{
    if(fila_vazia(fila)) return 0;
    int contador = 0;
    Elem *no = fila->inicio;
    while(no){
        ++contador;
        no = no->prox;
    }
    return contador;
}

int fila_insere(Fila *fila, Camara* camara, int idPai, int id)
{
    // fila existe?
    if(fila==NULL) return 0;
    // aloca memória para um nó.
    Elem *no = (Elem*)malloc(sizeof(Elem));
    // malloc falhou?
    if(no==NULL) return 0;
    // alocação bem sucedida...
    // inicializa o nó
    no->camara = camara;
    no->idPai = idPai;
    no->id = id;
    no->prox = NULL;
    no->fechado = 0;
    if(fila->final==NULL) {
        fila->inicio = no;
        no->ant = NULL;
    }
    else {
        fila->final->prox = no;
        no->ant = fila->final;
    }
    fila->final = no;
    return 1;
}
/*
int fila_remove(Fila *fila)
{
    if(fila_vazia(fila)) return 0;
    Elem *no = fila->inicio;
    fila->inicio = no->prox;
    if(fila->inicio==NULL) //fila ficou vazia?
        fila->final = NULL;
    free(no);
    return 1;
}

/*
int fila_consulta(Fila *fila, int *dado)
{
    if(fila_vazia(fila)) return 0;
    *dado = fila->inicio->dado;
    return 1;
}

void fila_imprime(Fila *fila)
{
    if(fila_vazia(fila)) return;
    Elem *no = fila->inicio;
    while(no){
        printf("%d ", no->dado);
        no = no->prox;
    }
    putchar('\n');
}
*/