#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

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

int pilha_insere(Pilha *pilha, Camara* camara)
{
    // pilha existe?
    if(pilha==NULL) return 0;
    // aloca memória para um nó.
    Elem *no = (Elem*)malloc(sizeof(Elem));
    // malloc falhou?
    if(no==NULL) return 0;
    // alocação bem sucedida...
    // inicializa o nó
    no->camara = camara;
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
        printf("%s ", getId(no->camara));
        no = no->prox;
    }
    putchar('\n');
}
