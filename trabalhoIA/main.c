/*
Trabalho IA 2021.1
Problema do labirinto
Autores: Jos�, Vin�cius e Yuri
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "labyrinth.h"
#include "search.h"
#include "fila.h"

int create(char* ref, Camara lista[]){

  FILE *arq;
  int result;
  char str[100];
  int i,j, k;
  char *token;
  int contador = 0;
  char *a[10], *b[10], *c[10], *d[10], *e[10];
  int d2, pos2, hn;

  arq = fopen(ref, "rt");
  if (arq == NULL){
    printf("Erro na abertura do arquivo");
  }

  i = 0;
  while(!feof(arq)){
    result = fgets(str, 100, arq);
    if (result){
      token = strtok(str,",");
      j=0;
      while(token){
        switch (j){
          case 0:
            a[0] = token;
            break;
          case 1:
            b[0] = token;
            break;
          case 2:
            c[0] = token;
            break;
          case 3:
            d[0] = token;
            break;
          case 4:
            e[0] = token;
            // puts(token);
        }

        token = strtok(NULL, ",");
        j++;

      }

        d2 = strtol(d[0], NULL, 10);
        hn = strtol(e[0], NULL, 10);


        if (!(strcmp(c[0],"DOWN_POS"))){
          pos2 = DOWN_POS;
        } else if (!(strcmp(c[0],"UP_POS"))){
          pos2 = UP_POS;
        } else if (!(strcmp(c[0],"RIGHT_POS"))){
          pos2 = RIGHT_POS;
        } else if (!(strcmp(c[0],"LEFT_POS"))){
          pos2 = LEFT_POS;
        } else {
          pos2=0;
        }

        int existe = 0;
        for (int k =0; k<contador; k++){
          if (!strcmp(lista[k].id, a[0])){
            existe = 1;
          }
        }
        if (existe ==0){
          Camara *cam = malloc(sizeof(Camara));
          setVizinhosNULL(cam);
          setObjetivo(cam, 0);
          setId(cam, a[0]);
          cam->hn = hn;
          lista[contador] = *cam;
          contador++;

        }
        Camara *cam1 = getById(lista, contador, a);
        Camara *cam2 = getById(lista, contador, b);

        if(strcmp(cam1->id, "nu") && strcmp(cam2->id, "nu")){
          insertVizinho(cam1, cam2, pos2, d2);
        }
    }
    i++;
  }
  fclose(arq);
  return contador;
}

Camara* createLabyrinth() { //(hr** heuristica) {
    Camara* z = malloc(sizeof(Camara));
    setVizinhosNULL(z);
    setObjetivo(z, 0);
    setId(z, "Z");
    z->hn = 9;

    //Fila* thisFila = fila_cria();
    // fila_insere_ord(thisFila, z, 0, 0);
    //fila_imprime(thisFila);

    //*heuristica = hrCreate(z, *heuristica, 9);
    //printf("strcmp == %d\n", strcmp(getId(z), "Z"));

    Camara* c = malloc(sizeof(Camara));
    setVizinhosNULL(c);
    setObjetivo(c, 0);
    setId(c, "C");
    insertVizinho(c, z, DOWN_POS , 1  );
    insertVizinho(z, c, UP_POS , 1  );
    c->hn = 8;

    // fila_insere_ord(thisFila, c, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(c, *heuristica, 8);
    //    *heuristica = (*heuristica)->next;


    Camara* d = malloc(sizeof(Camara));
    setVizinhosNULL(d);
    setObjetivo(d, 0);
    setId(d, "D");
    insertVizinho(d, c, RIGHT_POS , 2  );
    insertVizinho(c, d, LEFT_POS , 2  );
    d->hn = 9;

    // fila_insere_ord(thisFila, d, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(d, *heuristica, 9);
    //    *heuristica = (*heuristica)->next;


    Camara* i = malloc(sizeof(Camara));
    setVizinhosNULL(i);
    setObjetivo(i, 0);
    setId(i, "I");
    insertVizinho(i, d, DOWN_POS , 1  );
    insertVizinho(d, i, UP_POS , 1  );
    i->hn = 10;

    // fila_insere_ord(thisFila, i, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(i, *heuristica, 10);
    //    *heuristica = (*heuristica)->next;

    Camara* j = malloc(sizeof(Camara));
    setVizinhosNULL(j);
    setObjetivo(j, 0);
    setId(j, "J");
    insertVizinho(j, i, RIGHT_POS , 3  );
    insertVizinho(i, j, LEFT_POS , 3  );
    j->hn = 11;

    // fila_insere_ord(thisFila, j, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(j, *heuristica, 11);
    //    *heuristica = (*heuristica)->next;

    Camara* e = malloc(sizeof(Camara));
    setVizinhosNULL(e);
    setObjetivo(e, 0);
    setId(e, "E");
    insertVizinho(e, j, UP_POS , 2  );
    insertVizinho(j, e, DOWN_POS , 2  );
    e->hn = 12;

    // fila_insere_ord(thisFila, e, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(e, *heuristica, 12);
    //    *heuristica = (*heuristica)->next;

    Camara* b = malloc(sizeof(Camara));
    setVizinhosNULL(b);
    setObjetivo(b, 0);
    setId(b, "B");
    insertVizinho(b, c, LEFT_POS , 1  );
    insertVizinho(c, b, RIGHT_POS , 1  );
    b->hn = 9;

    // fila_insere_ord(thisFila, b, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(b, *heuristica, 9);
    //    *heuristica = (*heuristica)->next;

    Camara* a = malloc(sizeof(Camara));
    setVizinhosNULL(a);
    setObjetivo(a, 0);
    setId(a, "A");
    insertVizinho(a, b, LEFT_POS , 5  );
    insertVizinho(b, a, RIGHT_POS , 5  );
    a->hn = 8;

    // fila_insere_ord(thisFila, a, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(a, *heuristica, 8);
    //    *heuristica = (*heuristica)->next;

    Camara* f = malloc(sizeof(Camara));
    setVizinhosNULL(f);
    setObjetivo(f, 0);
    setId(f, "F");
    insertVizinho(f, a, DOWN_POS , 3  );
    insertVizinho(a, f, UP_POS , 3  );
    f->hn = 7;

    // fila_insere_ord(thisFila, f, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(f, *heuristica, 7);
    //    *heuristica = (*heuristica)->next;

    Camara* k = malloc(sizeof(Camara));
    setVizinhosNULL(k);
    setObjetivo(k, 0);
    setId(k, "K");
    insertVizinho(k, f, DOWN_POS , 1  );
    insertVizinho(f, k, UP_POS , 1  );
    k->hn = 8;

    // fila_insere_ord(thisFila, k, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(k, *heuristica, 8);
    //    *heuristica = (*heuristica)->next;

    Camara* p = malloc(sizeof(Camara));
    setVizinhosNULL(p);
    setObjetivo(p, 0);
    setId(p, "P");
    insertVizinho(p, k, DOWN_POS , 2  );
    insertVizinho(k, p, UP_POS , 2  );
    p->hn = 9;

    // fila_insere_ord(thisFila, p, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(p, *heuristica, 9);
    //    *heuristica = (*heuristica)->next;

    Camara* h = malloc(sizeof(Camara));
    setVizinhosNULL(h);
    setObjetivo(h, 0);
    setId(h, "H");
    insertVizinho(h, c, DOWN_POS , 4  );
    insertVizinho(c, h, UP_POS , 4  );
    h->hn = 7;

    // fila_insere_ord(thisFila, h, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(h, *heuristica, 7);
    //    *heuristica = (*heuristica)->next;

    Camara* g = malloc(sizeof(Camara));
    setVizinhosNULL(g);
    setObjetivo(g, 0);
    setId(g, "G");
    insertVizinho(g, h, LEFT_POS , 2  );
    insertVizinho(h, g, RIGHT_POS , 2  );
    insertVizinho(f, g, LEFT_POS , 5  );
    insertVizinho(g, f, RIGHT_POS , 5  );
    g->hn = 6;

    // fila_insere_ord(thisFila, g, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(g, *heuristica, 6);
    //    *heuristica = (*heuristica)->next;

    Camara* l = malloc(sizeof(Camara));
    setVizinhosNULL(l);
    setObjetivo(l, 0);
    setId(l, "L");
    insertVizinho(l, g, DOWN_POS , 2  );
    insertVizinho(g, l, UP_POS , 2  );
    l->hn = 5;

    // fila_insere_ord(thisFila, l, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(l, *heuristica, 5);
    //    *heuristica = (*heuristica)->next;

    Camara* q = malloc(sizeof(Camara));
    setVizinhosNULL(q);
    setObjetivo(q, 0);
    setId(q, "Q");
    insertVizinho(q, l, DOWN_POS , 3  );
    insertVizinho(l, q, UP_POS , 3  );
    q->hn = 4;

    // fila_insere_ord(thisFila, q, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(q, *heuristica, 4);
    //    *heuristica = (*heuristica)->next;

    Camara* r = malloc(sizeof(Camara));
    setVizinhosNULL(r);
    setObjetivo(r, 0);
    setId(r, "R");
    insertVizinho(r, q, RIGHT_POS , 1  );
    insertVizinho(q, r, LEFT_POS , 1  );
    r->hn = 3;

    // fila_insere_ord(thisFila, r, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(r, *heuristica, 3);
    //    *heuristica = (*heuristica)->next;

    Camara* m = malloc(sizeof(Camara));
    setVizinhosNULL(m);
    setObjetivo(m, 0);
    setId(m, "M");
    insertVizinho(m, r, UP_POS , 3  );
    insertVizinho(r, m, DOWN_POS , 3  );
    m->hn = 4;

    // fila_insere_ord(thisFila, m, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(m, *heuristica, 4);
    //    *heuristica = (*heuristica)->next;

    Camara* n = malloc(sizeof(Camara));
    setVizinhosNULL(n);
    setObjetivo(n, 0);
    setId(n, "N");
    insertVizinho(n, m, RIGHT_POS , 2  );
    insertVizinho(m, n, LEFT_POS , 2  );
    n->hn = 3;

    // fila_insere_ord(thisFila, n, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(n, *heuristica, 3);
    //    *heuristica = (*heuristica)->next;

    Camara* s = malloc(sizeof(Camara));
    setVizinhosNULL(s);
    setObjetivo(s, 0);
    setId(s, "S");
    insertVizinho(s, n, DOWN_POS , 3  );
    insertVizinho(n, s, UP_POS , 3  );
    insertVizinho(s, r, RIGHT_POS , 4  );
    insertVizinho(r, s, LEFT_POS , 4  );
    s->hn = 2;

    // fila_insere_ord(thisFila, s, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(s, *heuristica, 2);
    //    *heuristica = (*heuristica)->next;

    Camara* t = malloc(sizeof(Camara));
    setVizinhosNULL(t);
    setObjetivo(t, 0);
    setId(t, "T");
     insertVizinho(t, s, RIGHT_POS , 5  );
    insertVizinho(s, t, LEFT_POS , 5  );
    t->hn = 1;

    // fila_insere_ord(thisFila, t, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(t, *heuristica, 1);
    //    *heuristica = (*heuristica)->next;

    Camara* o = malloc(sizeof(Camara));
    setVizinhosNULL(o);
    setObjetivo(o, 0);
    setId(o, "O");
    insertVizinho(o, t, UP_POS , 4  );
    insertVizinho(t, o, DOWN_POS , 4  );
    o->hn = 2;

    // fila_insere_ord(thisFila, o, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(o, *heuristica, 2);
    //    *heuristica = (*heuristica)->next;

    Camara* w = malloc(sizeof(Camara));
    setVizinhosNULL(w);
    setObjetivo(w, 1);
    setId(w, "W");
    insertVizinho(w, t, DOWN_POS , 3  );
    insertVizinho(t, w, UP_POS , 3  );
    w->hn = 0;

    // fila_insere_ord(thisFila, w, 0, 0);
    //fila_imprime(thisFila);

    //    (*heuristica)->next = hrCreate(w, *heuristica, 0);
    //    *heuristica = (*heuristica)->next;

    //    *heuristica = hrReset(*heuristica);
    return z;
}

int main(void) {
  Camara lista[100];
  int total = create ("entrada.txt", lista);

  char startChar[MAX_ID_LEN];
  char endChar[MAX_ID_LEN];
  Camara* start;
  Camara* objetivo;
  int i =0;
  int objetivoEncontrado = 0;
  int comecoEncontrado = 0;
  int profundidade = 0;
  printf("Digite o ponto de partida: ");
  gets(startChar);
  printf("Digite o objetivo: ");
  gets(endChar);
  printf("Digite a profundidade máxima da busca em profundidade: ");
  scanf("%d",&profundidade);
  for(i; i<total; i++) {
    if(!strcmp(startChar,lista[i].id)) {
      start = &lista[i];
      comecoEncontrado = 1;
    }
    else if(!strcmp(endChar,lista[i].id)){
      objetivo = &lista[i];
      objetivoEncontrado = 1;
    }
  }
  if(objetivoEncontrado && comecoEncontrado) {
    int regras[4] = {UP_POS, RIGHT_POS, DOWN_POS, LEFT_POS};

    backtracking(start, objetivo, regras);
    //gulosa(start, objetivo);
    //ida(start, objetivo, regras);
    //buscaOrdenada(start, objetivo, regras);

    Camara* resultado1 = buscaLargura(start, objetivo, regras);
    if(resultado1 == NULL)
      printf("Erro\n");
    Camara* resultado2 = buscaProfundidade(start, objetivo, regras, profundidade);
    if(resultado2 == NULL)
      printf("Erro\n");
    Camara* resultado = buscaA(start, objetivo);
    if(resultado == NULL)
      printf("Erro\n");

  }
  else
    printf("Objetivo ou ponto de partida não encontrado, digite uma câmara válida");

  return 0;
}
