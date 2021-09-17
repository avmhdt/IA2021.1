#ifndef LISTA_H
#define LISTA_H

#include "labyrinth.h"

typedef struct no *No;
struct no
{
  char id[MAX_ID_LEN];
  char idPai[MAX_ID_LEN];
  int custo;
  int fechado;
  int profundidade;
  struct no *prox;
  struct no *ant;
  Camara *camara;
};

struct lista
{
  struct no *inicio;
  struct no *final;
};

typedef struct lista Lista;

Lista* lista_cria();
void lista_libera(Lista *lista);
int lista_vazia(Lista *lista);
int lista_tamanho(Lista *lista);
int lista_insere(Lista *lista, char* id, char* idPai, int custo, Camara *camara);
int lista_removeInicio(Lista *lista);
int lista_removeFinal(Lista *lista);
void lista_imprime(Lista *abertos, Lista *fechados);
No getInicio(Lista *lista);
No getMenorCusto(Lista *lista);
int lista_remove(Lista *lista, Camara* elem);
int lista_busca(Lista * lista, char id);
int lista_compara(Lista *lista, char id[], int custo);
int caminho2 (Lista *fechados, Camara* start, char* objectivo);
No getNoByID (Lista *lista, char* id);

int lista_insere_ord(Lista* lista, Camara* camara, No noPai, char* id, int custo);
#endif
