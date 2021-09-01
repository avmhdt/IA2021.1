#include "search.h"
#include <stdio.h>
#include <stdlib.h>

No* backtracking(No* raiz, char* objetivo, int regra[4]) {
    /*
    Algoritmo Backtracking
    Início
    S := estado inicial;
    N := S;
    Fracasso := F;
    Sucesso := F;
    Enquanto não (Sucesso ou Fracasso) faça
    Selecione o operador r de R(N);
    Se R(N) <> vazio então
    N := r(N);
    Se N é solução então
    Sucesso := T;
    Fim-se;
    Senão
    Se N = S então
    Fracasso := T;
    Senão
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
