#include "search.h"
#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "fila.h"

Camara* getCamara(No* node) {
    return node->camara;
};

void setCamara(No* node, Camara* camara) {
    node->camara = camara;
};

No* getPai(No* node) {
    return node->pai;
};

void setPai(No* node, No* pai) {
    node->pai = pai;
};

No* getFilho(No* node, int pos) {
    return node->filhos[pos];
};
void insertFilho(No* node, No* filho) {
    int i = 0;
    No* irmao = node->filhos[i];
    while(irmao != NULL) {
        i++;
        irmao = node->filhos[i];
    }
    node->filhos[i] = filho;
};

void allocFilhos(No* node) {
    node->filhos = malloc(sizeof(No*));
};

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
    No* S = raiz;
    No* N = S;
    No* V;
    Camara* vizinho;
    int i;
    int sucesso = 0, fracasso = 0;
    while(!(sucesso || fracasso)) {
        for(i = 0; i < 4; i++) {
            vizinho = getVizinho(getCamara(N), regra[i]);
            if(vizinho != NULL) {
                V = malloc(sizeof(No));
                setCamara(V, vizinho);
                printf("%s ", getId(vizinho));
                setPai(V, N);
                allocFilhos(V);
                insertFilho(N, V);
                N = V;
                break;
            }
        }
        if(strcmp(getId(getCamara(N)), objetivo) == 0) {
            sucesso = 1;
        } else {
            if(strcmp(getId(getCamara(N)), getId(getCamara(S))) == 0) {
                fracasso = 1;
            } else {
                N = getPai(N);
            }
        }
    }
    return N;
}
/*
Camara* buscaLargura(Camara* raiz, char* objetivo, int regra[4]) {
    
    //     início
    //     defina(abertos); {pilha(profundidade), fila(largura)}
    //     S := raiz; fracasso := F; sucesso := F;
    //     insere(S, abertos); defina(fechados);
    //     enquanto não (sucesso ou fracasso) faça
    //         se abertos = vazio então
    //             fracasso := T;
    //         senão
    //             N := primeiro(abertos); {pilha(topo), fila(primeiro)}
    //             se N = solução então
    //                 sucesso := T;
    //             senão
    //                 enquanto R(N) ≠ vazio faça
    //                     escolha r de R(N); new(u);
    //                     u := r(N); insere(u, abertos);
    //                     atualiza R(N);
    //                 fim-enquanto;
    //                 insere(N, fechados); {destrua(N)}
    //             fim-se;
    //         fim-se;
    //     fim-enquanto;
    // fim.
    
    int* abertos; //fila
    int sucesso = 0, fracasso = 0;
    Camara* N = raiz;
    while(!(sucesso || fracasso)) {
        if(abertos == NULL)
            fracasso = 1;
        else {

        }
    }
}*/
