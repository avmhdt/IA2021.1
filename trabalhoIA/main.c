/*
Trabalho IA 2021.1
Problema do labirinto
Autores: Jos�, Vin�cius e Yuri
*/

#include <stdio.h>
#include <stdlib.h>
#include "labyrinth.h"
#include "search.h"

Camara* createLabyrinth() {
    Camara* z = malloc(sizeof(Camara));
    setVizinhosNULL(z);
    setObjetivo(z, 0);
    setId(z, "Z");
    //    printf("strcmp == %d\n", strcmp(getId(z), "Z"));

    Camara* c = malloc(sizeof(Camara));
    setVizinhosNULL(c);
    setObjetivo(c, 0);
    setId(c, "C");
    insertVizinho(c, z, DOWN_POS);
    insertVizinho(z, c, UP_POS);

    Camara* d = malloc(sizeof(Camara));
    setVizinhosNULL(d);
    setObjetivo(d, 0);
    setId(d, "D");
    insertVizinho(d, c, RIGHT_POS);
    insertVizinho(c, d, LEFT_POS);

    Camara* i = malloc(sizeof(Camara));
    setVizinhosNULL(i);
    setObjetivo(i, 0);
    setId(i, "I");
    insertVizinho(i, d, DOWN_POS);
    insertVizinho(d, i, UP_POS);

    Camara* j = malloc(sizeof(Camara));
    setVizinhosNULL(j);
    setObjetivo(j, 0);
    setId(j, "J");
    insertVizinho(j, i, RIGHT_POS);
    insertVizinho(i, j, LEFT_POS);

    Camara* e = malloc(sizeof(Camara));
    setVizinhosNULL(e);
    setObjetivo(e, 0);
    setId(e, "E");
    insertVizinho(e, j, UP_POS);
    insertVizinho(j, e, DOWN_POS);

    Camara* b = malloc(sizeof(Camara));
    setVizinhosNULL(b);
    setObjetivo(b, 0);
    setId(b, "B");
    insertVizinho(b, c, LEFT_POS);
    insertVizinho(c, b, RIGHT_POS);

    Camara* a = malloc(sizeof(Camara));
    setVizinhosNULL(a);
    setObjetivo(a, 0);
    setId(a, "A");
    insertVizinho(a, b, LEFT_POS);
    insertVizinho(b, a, RIGHT_POS);

    Camara* f = malloc(sizeof(Camara));
    setVizinhosNULL(f);
    setObjetivo(f, 0);
    setId(f, "F");
    insertVizinho(f, a, DOWN_POS);
    insertVizinho(a, f, UP_POS);

    Camara* k = malloc(sizeof(Camara));
    setVizinhosNULL(k);
    setObjetivo(k, 0);
    setId(k, "K");
    insertVizinho(k, f, DOWN_POS);
    insertVizinho(f, k, UP_POS);

    Camara* p = malloc(sizeof(Camara));
    setVizinhosNULL(p);
    setObjetivo(p, 0);
    setId(p, "P");
    insertVizinho(p, k, DOWN_POS);
    insertVizinho(k, p, UP_POS);

    Camara* h = malloc(sizeof(Camara));
    setVizinhosNULL(h);
    setObjetivo(h, 0);
    setId(h, "H");
    insertVizinho(h, c, DOWN_POS);
    insertVizinho(c, h, UP_POS);

    Camara* g = malloc(sizeof(Camara));
    setVizinhosNULL(g);
    setObjetivo(g, 0);
    setId(g, "G");
    insertVizinho(g, h, LEFT_POS);
    insertVizinho(h, g, RIGHT_POS);
    insertVizinho(f, g, LEFT_POS);
    insertVizinho(g, f, RIGHT_POS);

    Camara* l = malloc(sizeof(Camara));
    setVizinhosNULL(l);
    setObjetivo(l, 0);
    setId(l, "L");
    insertVizinho(l, g, DOWN_POS);
    insertVizinho(g, l, UP_POS);

    Camara* q = malloc(sizeof(Camara));
    setVizinhosNULL(g);
    setObjetivo(q, 0);
    setId(q, "Q");
    insertVizinho(q, l, DOWN_POS);
    insertVizinho(l, q, UP_POS);

    Camara* r = malloc(sizeof(Camara));
    setVizinhosNULL(r);
    setObjetivo(r, 0);
    setId(r, "R");
    insertVizinho(r, q, RIGHT_POS);
    insertVizinho(q, r, LEFT_POS);

    Camara* m = malloc(sizeof(Camara));
    setVizinhosNULL(m);
    setObjetivo(m, 0);
    setId(m, "M");
    insertVizinho(m, r, UP_POS);
    insertVizinho(r, m, DOWN_POS);

    Camara* n = malloc(sizeof(Camara));
    setVizinhosNULL(n);
    setObjetivo(n, 0);
    setId(n, "N");
    insertVizinho(n, m, RIGHT_POS);
    insertVizinho(m, n, LEFT_POS);

    Camara* s = malloc(sizeof(Camara));
    setVizinhosNULL(s);
    setObjetivo(s, 0);
    setId(s, "S");
    insertVizinho(s, n, DOWN_POS);
    insertVizinho(n, s, UP_POS);
    insertVizinho(s, r, RIGHT_POS);
    insertVizinho(r, s, LEFT_POS);

    Camara* t = malloc(sizeof(Camara));
    setVizinhosNULL(t);
    setObjetivo(t, 0);
    setId(t, "T");
    insertVizinho(t, s, RIGHT_POS);
    insertVizinho(s, t, LEFT_POS);

    Camara* o = malloc(sizeof(Camara));
    setVizinhosNULL(o);
    setObjetivo(o, 0);
    setId(o, "O");
    insertVizinho(o, t, UP_POS);
    insertVizinho(t, o, DOWN_POS);

    Camara* w = malloc(sizeof(Camara));
    setVizinhosNULL(w);
    setObjetivo(w, 1);
    setId(w, "W");
    insertVizinho(w, t, DOWN_POS);
    insertVizinho(t, w, UP_POS);

    return z;
}

int main(void)
{
    printf("teste\n");

    Camara* start = createLabyrinth();
    /*No* raiz = malloc(sizeof(No));
    setCamara(raiz, start);
    setPai(raiz, NULL);
    allocFilhos(raiz);*/

    int regras[4] = {UP_POS, RIGHT_POS, DOWN_POS, LEFT_POS};
    //traverseLabyrinth(start, regras);

    //    No* bt = backtracking(raiz, "W", regras);
    //    printf("\naaaa\n");
    //    printf("bt.objetivo = %s\n", getId(bt));
    //    printf("Hello world!\n");

    return 0;
}
