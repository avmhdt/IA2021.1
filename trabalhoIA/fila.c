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
        ElemFila *no;
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
    ElemFila *no = fila->inicio;
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
    ElemFila *no = (ElemFila*)malloc(sizeof(ElemFila));
    // malloc falhou?
    if(no==NULL) return 0;
    // alocação bem sucedida...
    // inicializa o nó
    no->camara = camara;
    no->idPai = idPai;
    no->id = id;
    no->prox = NULL;
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

int fila_remove(Fila *fila)
{
    if(fila_vazia(fila)) return 0;
    ElemFila *no = fila->inicio;
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
*/
void fila_imprime(Fila *fila)
{
    if(fila_vazia(fila)) return;
    ElemFila *no = fila->inicio;
    while(no){
        printf(no->camara->id);
        printf(",idPai: %d",no->idPai);
        printf(",id: %d\n",no->id);
        no = no->prox;
    }
    putchar('\n');
}

int fila_insere_ord(Fila* fila, Camara* camara, int idPai, int id) {
    // fila existe?
    if(fila==NULL) return 0;
    // aloca memória para um nó.
    ElemFila *no = (ElemFila*)malloc(sizeof(ElemFila));
    // malloc falhou?
    if(no==NULL) return 0;

    no->camara = camara;
    no->idPai = idPai;
    no->id = id;
    no->prox = no->ant = NULL;

    ElemFila *current = fila->inicio;
    ElemFila *next;
    if(!current) {
        fila->inicio = fila->final = no;
    } else if (current->camara->hn > camara->hn) {
        fila->inicio = no;
        no->prox = current;
        current->ant = no;
        return;
    } else {
        while(current) {
        next = current->prox;
        if(current->camara->hn < camara->hn && (!next || next->camara->hn >= camara->hn)) {
            current->prox = no;
            no->ant = current;
            no->prox = next;
            if(next) {
                next->ant = no;
            }
        }
        current = next;
        }
    }
    return 1;
}


