#include "search.h"
#include <stdio.h>
#include <stdlib.h>

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
