/*
Trabalho IA 2021.1
Problema do labirinto
Autores: Jos�, Vin�cius e Yuri
*/

#include <stdio.h>
#include <stdlib.h>
#include "labyrinth.h"

No* createLabyrinth() {
    No* z = malloc(sizeof(No));
    setObjetivo(z, 0);
    setId(z, "Z");

    No* c = malloc(sizeof(No));
    setObjetivo(c, 0);
    setId(c, "C");
    insertVizinho(c, z, DOWN_POS);
    printf("oi\n");
    insertVizinho(z, c, UP_POS);

    No* d = malloc(sizeof(No));
    setObjetivo(d, 0);
    setId(d, "D");
    insertVizinho(d, c, RIGHT_POS);
    insertVizinho(c, d, LEFT_POS);

    No* i = malloc(sizeof(No));
    setObjetivo(i, 0);
    setId(i, "I");
    insertVizinho(i, d, DOWN_POS);
    insertVizinho(d, i, UP_POS);

    No* j = malloc(sizeof(No));
    setObjetivo(j, 0);
    setId(j, "J");
    insertVizinho(j, i, RIGHT_POS);
    insertVizinho(i, j, LEFT_POS);

    No* e = malloc(sizeof(No));
    setObjetivo(e, 0);
    setId(e, "E");
    insertVizinho(e, j, UP_POS);
    insertVizinho(j, e, DOWN_POS);

    No* b = malloc(sizeof(No));
    setObjetivo(b, 0);
    setId(b, "B");
    insertVizinho(b, c, LEFT_POS);
    insertVizinho(c, b, RIGHT_POS);

    No* a = malloc(sizeof(No));
    setObjetivo(a, 0);
    setId(a, "A");
    insertVizinho(a, b, LEFT_POS);
    insertVizinho(b, a, RIGHT_POS);

    No* f = malloc(sizeof(No));
    setObjetivo(f, 0);
    setId(f, "F");
    insertVizinho(f, a, DOWN_POS);
    insertVizinho(a, f, UP_POS);

    No* k = malloc(sizeof(No));
    setObjetivo(k, 0);
    setId(k, "K");
    insertVizinho(k, f, DOWN_POS);
    insertVizinho(f, k, UP_POS);

    No* p = malloc(sizeof(No));
    setObjetivo(p, 0);
    setId(p, "P");
    insertVizinho(p, k, DOWN_POS);
    insertVizinho(k, p, UP_POS);

    No* h = malloc(sizeof(No));
    setObjetivo(h, 0);
    setId(h, "H");
    insertVizinho(h, c, DOWN_POS);
    insertVizinho(c, h, UP_POS);

    No* g = malloc(sizeof(No));
    setObjetivo(g, 0);
    setId(g, "G");
    insertVizinho(g, h, LEFT_POS);
    insertVizinho(h, g, RIGHT_POS);
    insertVizinho(f, g, LEFT_POS);
    insertVizinho(g, f, RIGHT_POS);

    No* l = malloc(sizeof(No));
    setObjetivo(l, 0);
    setId(l, "L");
    insertVizinho(l, g, DOWN_POS);
    insertVizinho(g, l, UP_POS);

    No* q = malloc(sizeof(No));
    setObjetivo(q, 0);
    setId(q, "Q");
    insertVizinho(q, l, DOWN_POS);
    insertVizinho(l, q, UP_POS);

    No* r = malloc(sizeof(No));
    setObjetivo(r, 0);
    setId(r, "R");
    insertVizinho(r, q, RIGHT_POS);
    insertVizinho(q, r, LEFT_POS);

    No* m = malloc(sizeof(No));
    setObjetivo(m, 0);
    setId(m, "M");
    insertVizinho(m, r, UP_POS);
    insertVizinho(r, m, DOWN_POS);

    No* n = malloc(sizeof(No));
    setObjetivo(n, 0);
    setId(n, "N");
    insertVizinho(n, m, RIGHT_POS);
    insertVizinho(m, n, LEFT_POS);

    No* s = malloc(sizeof(No));
    setObjetivo(s, 0);
    setId(s, "S");
    insertVizinho(s, n, DOWN_POS);
    insertVizinho(n, s, UP_POS);
    insertVizinho(s, r, RIGHT_POS);
    insertVizinho(r, s, LEFT_POS);

    No* t = malloc(sizeof(No));
    setObjetivo(t, 0);
    setId(t, "T");
    insertVizinho(t, s, RIGHT_POS);
    insertVizinho(s, t, LEFT_POS);

    No* o = malloc(sizeof(No));
    setObjetivo(o, 0);
    setId(o, "O");
    insertVizinho(o, t, UP_POS);
    insertVizinho(t, o, DOWN_POS);

    No* w = malloc(sizeof(No));
    setObjetivo(w, 1);
    setId(w, "W");
    insertVizinho(w, t, DOWN_POS);
    insertVizinho(t, w, UP_POS);

    return z;
}

int main()
{
    No* raiz = createLabyrinth();
    printf("Hello world!\n");
    return 0;
}
