/*
Trabalho IA 2021.1
Problema do labirinto
Autores: Jos�, Vin�cius e Yuri
*/

#include <stdio.h>
#include <stdlib.h>
//#include labyrinth.h"
#include "search.h"
#include "createLabyrinth.h"

int main()
{
    Camara* start = createLabyrinth();
    No* raiz = malloc(sizeof(No));
    setCamara(raiz, start);
    setPai(raiz, NULL);
    allocFilhos(raiz);

    printf("teste\n");

    int regras[4] = {UP_POS, RIGHT_POS, DOWN_POS, LEFT_POS};
    traverseLabyrinth(start, regras);

//    No* bt = backtracking(raiz, "W", regras);
//    printf("\naaaa\n");
//    printf("bt.objetivo = %s\n", getId(bt));
//    printf("Hello world!\n");
    return 0;
}
