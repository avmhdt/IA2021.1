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
        ElemPilha *aux = (*pilha);
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
    ElemPilha *no = (ElemPilha*)malloc(sizeof(ElemPilha));
    // malloc falhou?
    if(no==NULL) return 0;
    // alocação bem sucedida...
    // inicializa o nó
    no->camara = camara;
    no->prox = (*pilha);
    no->custo = 0;
    no->profundidade = 0;
    *pilha = no;
    return 1;
}

int pilha_remove(Pilha *pilha)
{
    if(pilha==NULL || pilha_vazia(pilha)) return 0;
    ElemPilha *aux = *pilha;
    *pilha = aux->prox;
    free(aux);
    return 1;
}

int pilha_imprime(Pilha *pilha)
{
    if(pilha_vazia(pilha)) return 0;
    int quantNos = 0;
    ElemPilha *no = *pilha;
    while(no){
        printf("%s ", getId(no->camara));
        no = no->prox;
        quantNos++;
    }
    putchar('\n');
    return quantNos;
}

int pilha_conta(Pilha *pilha) {
    if(pilha_vazia(pilha)) return 0;
    int quantNos = 0;
    ElemPilha *no = *pilha;
    while(no) {
        quantNos++;
        no = no->prox;
    }
    return quantNos;
}
