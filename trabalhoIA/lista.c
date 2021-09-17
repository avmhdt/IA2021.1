#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <string.h>
#include "labyrinth.h"

Lista* lista_cria()
{
    Lista *li = (Lista*) malloc(sizeof(Lista));
    if(li!=NULL)
        li->inicio = li->final = NULL;
    return li;
}

No getInicio(Lista *lista){
    No no = lista->inicio;
    return no;
}

No getMenorCusto(Lista *lista){
    No min = lista->inicio;
    No no = lista->inicio;
    while (no){

      if (no->custo < min->custo){
        min = no;
      }
      no = no->prox;
    }

    return min;
}

void lista_libera(Lista *lista)
{
    if(lista!=NULL){
        No *no;
        while(lista->inicio){
            *no = lista->inicio;
            lista->inicio = lista->inicio->prox;
            free(no);
        }
        free(lista);
    }
}

int lista_vazia(Lista *lista)
{
    if(lista==NULL || lista->inicio==NULL) return 1;
    return 0;
}

int lista_tamanho(Lista *lista)
{
    if(lista_vazia(lista)) return 0;
    int contador = 0;
    No no = lista->inicio;
    while(no){
        ++contador;
        no = no->prox;
    }
    return contador;
}


int lista_busca(Lista * lista, char id){

    No no = lista->inicio;
    int i=0;
    while (no){

        if (no->id[0] == id){
          return i;
        }
        if (no->prox != NULL)
          no = no->prox;
        else {
          no = NULL;
        }
        i=i+1;
    }
    return -1;
}

No getNoByID (Lista *lista, char* id){
    No no = lista->inicio;
    while (no){
      if (!strcmp(no->camara->id, id)){
        return no;
      }
      no = no->prox;
    }
    No nulo = (No)malloc(sizeof(No)+sizeof(Camara));
    nulo->profundidade = -1;
    return nulo;
}

int lista_insere(Lista *lista, char*id, char* idPai, int custo, Camara *camara)
{
    // lista existe?
    if(lista==NULL) return 0;
    // aloca memória para um nó.
    No no = (No)malloc(sizeof(No)+sizeof(Camara));
    // malloc falhou?
    if(no==NULL) return 0;
    // alocação bem sucedida...
    // inicializa o nó

    setId(no,id);
    setId(no->idPai, idPai);
    no->custo = custo;


    no->prox = NULL;
    no->camara = camara;
    if(lista->final==NULL){
        lista->inicio = no;
        no->ant = NULL;
    }
    else{
        lista->final->prox = no;
        no->ant = lista->final;
    }
    lista->final = no;
    return 1;
}

int lista_removeInicio(Lista *lista)
{
    if(lista_vazia(lista)) return 0;
    No no = lista->inicio;
    lista->inicio = no->prox;
    if(lista->inicio==NULL) //fila ficou vazia?
        lista->final = NULL;
    free(no);
    return 1;
}

int lista_removeFinal(Lista *lista)
{
    if(lista==NULL || lista_vazia(lista)) return 0;
    No no = lista->inicio;
    while (no->prox->prox!=NULL)
      no = no->prox;
    lista->final = no;
    free (no->prox);
    no->prox = NULL;
    return 1;
}

int lista_compara(Lista *lista, char id[], int custo){

  No no = lista->inicio;
  while (no){
    if (no->id[0] == id[0]){

      if (no->custo > custo){
        return 1;
      } else {
        return 2;
      }
    }
    no = no->prox;
  }
  return 0;
}

int lista_remove(Lista *lista, Camara* elem){
    No no = lista->inicio;
    if (no->id[0] == elem->id[0]){
      lista_removeInicio(lista);
      return 1;
    }
    while (no){
      if (no->prox->id[0] != elem->id[0]){
        no = no->prox;
      } else {
        break;
      }
    }

    No aux = no->prox->prox;

    no->prox->prox = NULL;
    free(no->prox);
    no->prox = aux;
    return 1;
}

void lista_imprime(Lista *abertos, Lista *fechados)
{
    printf("\n");

    if(lista_vazia(abertos)) return;
    No no = abertos->inicio;

    while(no){
        printf("  %c(%d)", no->id[0], no->custo);
        no = no->prox;
    }
    printf("  **************  ");
    no = fechados->inicio;
    while(no){
        printf("  %c", no->id[0]);
        no = no->prox;
    }

}

int caminho2 (Lista *fechados, Camara* start, char* objectivo){
  printf(" %c", objectivo[0]);
  int profundidade = 0;
  No no = fechados->inicio;
  while(no->prox){
    no = no->prox;
  }

  char* idPai =  no->idPai;
  printf("<-%s ", no->idPai);
  while (no->id[0] != start->id[0]){
    no = fechados->inicio;
    while(no->id[0] != idPai[0]){
      no = no->prox;
    }
    printf("<-%s", no->idPai);
    profundidade ++;
    idPai = no->idPai;


  }
  return profundidade;
}

int lista_insere_ord(Lista* lista, Camara* camara, No noPai, char* id, int custo) {
    // fila existe?
    if(lista==NULL) return 0;
    // aloca memória para um nó.
    No no = (No)malloc(sizeof(No)+sizeof(Camara));
    // malloc falhou?
    if(no==NULL) return 0;

    no->camara = camara;
    setId(no,id);
    setId(no->idPai, noPai->id);
    no->prox = no->ant = NULL;
    no->custo = custo;

    No current = lista->inicio;
    No next;
    if(!current) {
        lista->inicio = lista->final = no;
    } else if (current->custo >= custo) {
        lista->inicio = no;
        no->prox = current;
        current->ant = no;
        return 1;
    } else {
        while(current) {
        next = current->prox;
        if(current->custo < custo && (!next || next->custo >= custo)) {
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
