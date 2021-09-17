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
    no->custo = 0;
    no->fn = camara->hn;
    no->profundidade = 0;
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

int fila_remove(Fila *fila) {
    if(fila_vazia(fila)) return 0;
    ElemFila *no = fila->inicio;
    fila->inicio = no->prox;
    if(fila->inicio==NULL) //fila ficou vazia?
        fila->final = NULL;
    free(no);
    return 1;
}

int fila_remove_ord(Fila *fila, int id) {
    if(fila_vazia(fila)) return 0;
    ElemFila *no = fila->inicio;
    if(no->id == id) {
        return fila_remove(fila);
    }
    while(no->id != id) {
        no = no->prox;
    }
    no->ant->prox = no->prox;
    if(no->prox == NULL) {
        fila->final = no->ant;
    }
    else
        no->prox->ant = no->ant;
    free(no);
    return 1;
}

int fila_conta(Fila *fila)
{
    if(fila_vazia(fila)) return 0;
    int quantNos = 0;
    ElemFila *no = fila->inicio;
    while(no){
        no = no->prox;
        quantNos++;
    }
    return quantNos;
}


int fila_imprime(Fila *fila)
{
    if(fila_vazia(fila)) return 0;
    int quantNos = 0;
    ElemFila *no = fila->inicio;
    while(no){
        printf(no->camara->id);
        printf(", hn = %d",no->camara->hn);
        printf(", idPai: %d",no->idPai);
        printf(", id: %d\n",no->id);
        no = no->prox;
        quantNos++;
    }
    putchar('\n');
    return quantNos;
}

int fila_insere_ord(Fila* fila, Camara* camara, int idPai, int id, int peso, int custoPai) {
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
    no->custo = peso + custoPai;

    ElemFila *current = fila->inicio;
    ElemFila *next;
    if(!current) {
        fila->inicio = fila->final = no;
    } else if (current->camara->hn >= camara->hn) {
        fila->inicio = no;
        no->prox = current;
        current->ant = no;
        return 1;
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

int fila_insere_ord_fn(Fila* fila, Camara* camara, int id, int peso, ElemFila* pai) {
    // fila existe?
    if(fila==NULL) return 0;
    // aloca memória para um nó.
    ElemFila *no = (ElemFila*)malloc(sizeof(ElemFila));
    // malloc falhou?
    if(no==NULL) return 0;

    no->camara = camara;
    no->idPai = pai->id;
    no->id = id;
    no->prox = no->ant = NULL;
    no->profundidade = pai->profundidade+1;
    int fn = (pai->custo + peso) + camara->hn;
    no->fn = fn;
    no->custo = pai->custo + peso;

    ElemFila *current = fila->inicio;
    ElemFila *next;
    if(!current) {
        fila->inicio = fila->final = no;
    } else if (current->fn >= fn) {
        fila->inicio = no;
        no->prox = current;
        current->ant = no;
        return 1;
    } else {
        while(current) {
        next = current->prox;
        if(current->fn < fn && (!next || next->fn >= fn)) {
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
