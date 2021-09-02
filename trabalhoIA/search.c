#include "search.h"
#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "fila.h"

Camara* backtracking(Camara* raiz, char* objetivo, int regra[4]) {
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
    Camara* N = raiz;
    Camara* V;
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

Camara* buscaLargura(Camara* raiz, char* objetivo, int regra[4]) {
    /*
    início
    defina(abertos); {pilha(profundidade), fila(largura)}
    S := raiz; fracasso := F; sucesso := F;
    insere(S, abertos); defina(fechados);
    enquanto não (sucesso ou fracasso) faça
        se abertos = vazio então
            fracasso := T;
        senão
            N := primeiro(abertos); {pilha(topo), fila(primeiro)}
            se N = solução então
                sucesso := T;
            senão
                enquanto R(N) ≠ vazio faça
                    escolha r de R(N); new(u);
                    u := r(N); insere(u, abertos);
                    atualiza R(N);
                fim-enquanto;
                insere(N, fechados); {destrua(N)}
            fim-se;
        fim-se;
    fim-enquanto;
fim.
    */
    int* abertos; //fila
    int sucesso = 0, fracasso = 0;
    Camara* N = raiz;
    while(!(sucesso || fracasso)) {
        if(abertos == NULL)
            fracasso = 1;
        else {

        }
    }
}