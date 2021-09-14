/*
Trabalho IA 2021.1
Problema do labirinto
Autores: José, Vinícius e Yuri
*/

#include <stdio.h>
#include <stdlib.h>
//#include labyrinth.h"
#include "search.h"

Camara* createLabyrinth(hr** heuristica) {
    Camara* z = malloc(sizeof(Camara));
    setVizinhosNULL(z);
    setObjetivo(z, 0);
    setId(z, "Z");

    *heuristica = hrCreate(z, *heuristica, 9);
    //printf("strcmp == %d\n", strcmp(getId(z), "Z"));

    Camara* c = malloc(sizeof(Camara));
    setVizinhosNULL(c);
    setObjetivo(c, 0);
    setId(c, "C");
    insertVizinho(c, z, DOWN_POS);
    insertVizinho(z, c, UP_POS);

    (*heuristica)->next = hrCreate(c, *heuristica, 8);
    *heuristica = (*heuristica)->next;

    Camara* d = malloc(sizeof(Camara));
    setVizinhosNULL(d);
    setObjetivo(d, 0);
    setId(d, "D");
    insertVizinho(d, c, RIGHT_POS);
    insertVizinho(c, d, LEFT_POS);

    (*heuristica)->next = hrCreate(d, *heuristica, 9);
    *heuristica = (*heuristica)->next;

    Camara* i = malloc(sizeof(Camara));
    setVizinhosNULL(i);
    setObjetivo(i, 0);
    setId(i, "I");
    insertVizinho(i, d, DOWN_POS);
    insertVizinho(d, i, UP_POS);

    (*heuristica)->next = hrCreate(i, *heuristica, 10);
    *heuristica = (*heuristica)->next;

    Camara* j = malloc(sizeof(Camara));
    setVizinhosNULL(j);
    setObjetivo(j, 0);
    setId(j, "J");
    insertVizinho(j, i, RIGHT_POS);
    insertVizinho(i, j, LEFT_POS);

    (*heuristica)->next = hrCreate(j, *heuristica, 11);
    *heuristica = (*heuristica)->next;

    Camara* e = malloc(sizeof(Camara));
    setVizinhosNULL(e);
    setObjetivo(e, 0);
    setId(e, "E");
    insertVizinho(e, j, UP_POS);
    insertVizinho(j, e, DOWN_POS);

    (*heuristica)->next = hrCreate(e, *heuristica, 12);
    *heuristica = (*heuristica)->next;

    Camara* b = malloc(sizeof(Camara));
    setVizinhosNULL(b);
    setObjetivo(b, 0);
    setId(b, "B");
    insertVizinho(b, c, LEFT_POS);
    insertVizinho(c, b, RIGHT_POS);

    (*heuristica)->next = hrCreate(b, *heuristica, 9);
    *heuristica = (*heuristica)->next;

    Camara* a = malloc(sizeof(Camara));
    setVizinhosNULL(a);
    setObjetivo(a, 0);
    setId(a, "A");
    insertVizinho(a, b, LEFT_POS);
    insertVizinho(b, a, RIGHT_POS);

    (*heuristica)->next = hrCreate(a, *heuristica, 8);
    *heuristica = (*heuristica)->next;

    Camara* f = malloc(sizeof(Camara));
    setVizinhosNULL(f);
    setObjetivo(f, 0);
    setId(f, "F");
    insertVizinho(f, a, DOWN_POS);
    insertVizinho(a, f, UP_POS);

    (*heuristica)->next = hrCreate(f, *heuristica, 7);
    *heuristica = (*heuristica)->next;

    Camara* k = malloc(sizeof(Camara));
    setVizinhosNULL(k);
    setObjetivo(k, 0);
    setId(k, "K");
    insertVizinho(k, f, DOWN_POS);
    insertVizinho(f, k, UP_POS);

    (*heuristica)->next = hrCreate(k, *heuristica, 8);
    *heuristica = (*heuristica)->next;

    Camara* p = malloc(sizeof(Camara));
    setVizinhosNULL(p);
    setObjetivo(p, 0);
    setId(p, "P");
    insertVizinho(p, k, DOWN_POS);
    insertVizinho(k, p, UP_POS);

    (*heuristica)->next = hrCreate(p, *heuristica, 9);
    *heuristica = (*heuristica)->next;

    Camara* h = malloc(sizeof(Camara));
    setVizinhosNULL(h);
    setObjetivo(h, 0);
    setId(h, "H");
    insertVizinho(h, c, DOWN_POS);
    insertVizinho(c, h, UP_POS);

    (*heuristica)->next = hrCreate(h, *heuristica, 7);
    *heuristica = (*heuristica)->next;

    Camara* g = malloc(sizeof(Camara));
    setVizinhosNULL(g);
    setObjetivo(g, 0);
    setId(g, "G");
    insertVizinho(g, h, LEFT_POS);
    insertVizinho(h, g, RIGHT_POS);
    insertVizinho(f, g, LEFT_POS);
    insertVizinho(g, f, RIGHT_POS);

    (*heuristica)->next = hrCreate(g, *heuristica, 6);
    *heuristica = (*heuristica)->next;

    Camara* l = malloc(sizeof(Camara));
    setVizinhosNULL(l);
    setObjetivo(l, 0);
    setId(l, "L");
    insertVizinho(l, g, DOWN_POS);
    insertVizinho(g, l, UP_POS);

    (*heuristica)->next = hrCreate(l, *heuristica, 5);
    *heuristica = (*heuristica)->next;

    Camara* q = malloc(sizeof(Camara));
    setVizinhosNULL(q);
    setObjetivo(q, 0);
    setId(q, "Q");
    insertVizinho(q, l, DOWN_POS);
    insertVizinho(l, q, UP_POS);

    (*heuristica)->next = hrCreate(q, *heuristica, 4);
    *heuristica = (*heuristica)->next;

    Camara* r = malloc(sizeof(Camara));
    setVizinhosNULL(r);
    setObjetivo(r, 0);
    setId(r, "R");
    insertVizinho(r, q, RIGHT_POS);
    insertVizinho(q, r, LEFT_POS);

    (*heuristica)->next = hrCreate(r, *heuristica, 3);
    *heuristica = (*heuristica)->next;

    Camara* m = malloc(sizeof(Camara));
    setVizinhosNULL(m);
    setObjetivo(m, 0);
    setId(m, "M");
    insertVizinho(m, r, UP_POS);
    insertVizinho(r, m, DOWN_POS);

    (*heuristica)->next = hrCreate(m, *heuristica, 4);
    *heuristica = (*heuristica)->next;

    Camara* n = malloc(sizeof(Camara));
    setVizinhosNULL(n);
    setObjetivo(n, 0);
    setId(n, "N");
    insertVizinho(n, m, RIGHT_POS);
    insertVizinho(m, n, LEFT_POS);

    (*heuristica)->next = hrCreate(n, *heuristica, 3);
    *heuristica = (*heuristica)->next;

    Camara* s = malloc(sizeof(Camara));
    setVizinhosNULL(s);
    setObjetivo(s, 0);
    setId(s, "S");
    insertVizinho(s, n, DOWN_POS);
    insertVizinho(n, s, UP_POS);
    insertVizinho(s, r, RIGHT_POS);
    insertVizinho(r, s, LEFT_POS);

    (*heuristica)->next = hrCreate(s, *heuristica, 2);
    *heuristica = (*heuristica)->next;

    Camara* t = malloc(sizeof(Camara));
    setVizinhosNULL(t);
    setObjetivo(t, 0);
    setId(t, "T");
    insertVizinho(t, s, RIGHT_POS);
    insertVizinho(s, t, LEFT_POS);

    (*heuristica)->next = hrCreate(t, *heuristica, 1);
    *heuristica = (*heuristica)->next;

    Camara* o = malloc(sizeof(Camara));
    setVizinhosNULL(o);
    setObjetivo(o, 0);
    setId(o, "O");
    insertVizinho(o, t, UP_POS);
    insertVizinho(t, o, DOWN_POS);

    (*heuristica)->next = hrCreate(o, *heuristica, 2);
    *heuristica = (*heuristica)->next;

    Camara* w = malloc(sizeof(Camara));
    setVizinhosNULL(w);
    setObjetivo(w, 1);
    setId(w, "W");
    insertVizinho(w, t, DOWN_POS);
    insertVizinho(t, w, UP_POS);

    (*heuristica)->next = hrCreate(w, *heuristica, 0);
    *heuristica = (*heuristica)->next;

    *heuristica = hrReset(*heuristica);
    return z;
}

int main()
{
    hr **heuristica = malloc(sizeof(hr*));
    *heuristica = NULL;
    Camara* start = createLabyrinth(heuristica);
    hrPrint(*heuristica);
//    No* raiz = malloc(sizeof(No));
//    setCamara(raiz, start);
//    setPai(raiz, NULL);
//    allocFilhos(raiz);
//    printf("raiz = %s\n", getId(getCamara(raiz)));
//
//    printf("teste\n");

    int regras[4] = {UP_POS, RIGHT_POS, DOWN_POS, LEFT_POS};
//    backtracking(start, "W", regras);

    gulosa(start, "W", regras, *heuristica);



    printf("Hello world!\n");
    return 0;
}
