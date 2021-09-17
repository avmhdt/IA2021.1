//https://gist.github.com/IsaacBruno/6c0dc146ef4bfe2f8038c954219d0530
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <string.h>
#include "labyrinth.h"

#define MAX_ID_LEN 1

// typedef struct lista Lista;




Lista* lista_cria()
{
    Lista *li = (Lista*) malloc(sizeof(Lista));
    if(li!=NULL)
        li->inicio = li->final = NULL;
    //printf("Lista criada");
    return li;
}

No getInicio(Lista *lista){
    No no = lista->inicio;
    //printf("eita ---- %c", no->id[0]);
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
    
    
    //printf("\n\n---------------------------------\n%c", no->custo);
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
    // printf("\n\nREMOCAO %c\n\n", elem->id[0]);
    // if (lista_busca(lista, elem->id[0]) == -1){
    //   //printf("deu menos um");
    //   return 0;
    // }
    //printf("\nsegue -- %c\n\n", elem->id[0]);
    // No no = lista->final;
    // printf("FINAL DA LISTA %c", no->id[0]);
    // if (no->id[0] == elem->id[0]){
    //   lista_removeFinal(lista);
    //   //printf("removeinicio");
    //   return 1;
    // }
    No no = lista->inicio;
    // printf("INICIO DA LISTA %c\n\n", no->id[0]);
    if (no->id[0] == elem->id[0]){
      lista_removeInicio(lista);
      //printf("removeinicio");
      return 1;
    }
    while (no){
      if (no->prox->id[0] != elem->id[0]){
        no = no->prox;
      } else {
        break;
      }
    }
                      // while (no->prox && no->prox->id[0] != elem->id[0]){
                      //   //printf("\n%c\n", no->prox->id[0]);
                      //   no = no->prox;
                      // }
    // printf("fim do while -- %c\n", no->id[0]);
    No aux = no->prox->prox;
    // No *aux2 = &aux->prox;

    no->prox->prox = NULL;
    free(no->prox);
    no->prox = aux;
    return 1;
}

// int lista_consulta(Lista *lista, int *dado)
// {
//     if(fila_vazia(lista)) return 0;
//     *dado = lista->inicio->dado;
//     return 1;
// }



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
    // printf("Quase no id");
    while(no->id[0] != idPai[0]){
      // printf("\n%c ---- %c\n", no->id[0] , idPai[0]);
      no = no->prox;
    }
    printf("<-%s", no->idPai);
    profundidade ++;
    idPai = no->idPai;
      
    
  }
  return profundidade;
}