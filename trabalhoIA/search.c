#include "search.h"
#include <stdio.h>
#include <stdlib.h>

No* backtracking(No* raiz, char* objetivo, int regra[4]) {
    /*
    Algoritmo Backtracking
    In�cio
    S := estado inicial;
    N := S;
    Fracasso := F;
    Sucesso := F;
    Enquanto n�o (Sucesso ou Fracasso) fa�a
    Selecione o operador r de R(N);
    Se R(N) <> vazio ent�o
    N := r(N);
    Se N � solu��o ent�o
    Sucesso := T;
    Fim-se;
    Sen�o
    Se N = S ent�o
    Fracasso := T;
    Sen�o
    N := pai(N);
    Fim-se;
    Fim-se;
    Fim-enquanto;
    Fim.
    */
    No* N = raiz;
    No* V;
    int i;
    int sucesso = 0, fracasso = 0;
    while(!(sucesso || fracasso)) {
        for(i = 0; i < 4; i++) {
            V = getVizinho(N, regra[i]);
            if(V != NULL) {
                N = V;
                break;
            }
        }
        if(strcmp(getId(N), objetivo) == 0) {
            sucesso = 1;
        } else {
            fracasso = 1;
        }
    }
    return N;
}
