//https://gist.github.com/IsaacBruno/6c0dc146ef4bfe2f8038c954219d0530
#ifndef LISTA_H
#define LISTA_H

#include "labyrinth.h"

#define MAX_ID_LEN 1

typedef struct no *No;
struct no
{
  char id[MAX_ID_LEN];
  char idPai[MAX_ID_LEN];
  int custo;
  int fechado;
  struct no *prox;
  Camara *camara;
};

typedef struct lista Lista;
// typedef struct no *No;

Lista* lista_cria();
void lista_libera(Lista *lista);
int lista_vazia(Lista *lista);
int lista_tamanho(Lista *lista);
int lista_insere(Lista *lista, char* id, char* idPai, int custo, Camara *camara);
int lista_removeInicio(Lista *lista);
int lista_removeFinal(Lista *lista);
// int lista_consulta(Lista *lista, int *dado);
void lista_imprime(Lista *abertos, Lista *fechados);
No getInicio(Lista *lista);
No getMenorCusto(Lista *lista);
int lista_remove(Lista *lista, Camara* elem);
int lista_busca(Lista * lista, char id);
int lista_compara(Lista *lista, char id[], int custo);
#endif