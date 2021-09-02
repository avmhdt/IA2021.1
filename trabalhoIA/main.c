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
    Camara* raiz = createLabyrinth();
    int regras[4] = {0, 1, 2, 3};
    Camara* bt = backtracking(raiz, "W", regras);
    printf("bt.objetivo = %s\n", getId(bt));
    printf("Hello world!\n");
    return 0;
}
