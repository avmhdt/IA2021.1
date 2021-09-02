//https://gist.github.com/IsaacBruno/6c0dc146ef4bfe2f8038c954219d0530
#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

struct elemento
{
    int dado;
    struct elemento *prox;
};

typedef struct elemento Elem;

Pilha* pilha_cria()
{
    Pilha *pi = (Pilha*) malloc(sizeof(Pilha));
    if(pi!=NULL)
        *pi = NULL;
    return pi;
}

void pilha_libera(Pilha *pilha)
{
    if(pilha==NULL) return;
    if(!pilha_vazia(pilha)){
        Elem *aux = (*pilha);
        while(*pilha){
            *pilha = (*pilha)->prox;
            free(aux);
            aux = (*pilha);
        }
    }
    free(pilha);
}

int pilha_vazia(Pilha *pilha)
{
    return (pilha==NULL || (*pilha)==NULL);
}

int pilha_insere(Pilha *pilha, int dado)
{
    // pilha existe?
    if(pilha==NULL) return 0;
    // aloca memória para um nó.
    Elem *no = (Elem*)malloc(sizeof(Elem));
    // malloc falhou?
    if(no==NULL) return 0;
    // alocação bem sucedida...
    // inicializa o nó
    no->dado = dado;
    no->prox = (*pilha);
    *pilha = no;
    return 1;
}

int pilha_remove(Pilha *pilha)
{
    if(pilha==NULL || pilha_vazia(pilha)) return 0;
    Elem *aux = *pilha;
    *pilha = aux->prox;
    free(aux);
    return 1;
}

void pilha_imprime(Pilha *pilha)
{
    if(pilha_vazia(pilha)) return;
    Elem *no = *pilha;
    while(no){
        printf("%d ", no->dado);
        no = no->prox;
    }
    putchar('\n');
}