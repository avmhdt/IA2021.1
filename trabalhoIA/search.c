#include "search.h"
#include <stdio.h>
#include <stdlib.h>

#include "pilha.h"

/*
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

int match(char* key, No* node) {
    if(node == NULL) {
        printf("NULL ");
        return 0;
    }
    if(strcmp(getId(getCamara(node)), key) == 0) {
        return 1;
    }
    printf("oi\n");
    match(key, getPai(node));
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
    //
    No* S = raiz;
    No* N = S;
    No* V;
    Camara* vizinho;
    int i;
    int sucesso = 0, fracasso = 0;
    while(!(sucesso || fracasso)) {
        printf("%s ", getId(getCamara(N)));
        for(i = 0; i < 4; i++) {
            vizinho = getVizinho(getCamara(N), regra[i]);
            printf("\n vizinho = %s \n", getId(vizinho));
            //printf("match = %d\n", match(getId(vizinho), N));
            if(vizinho != NULL && !match(getId(vizinho), N)) { // e no nao eh ancestral
                V = malloc(sizeof(No));
                setCamara(V, vizinho);
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
*/

void backtracking(Camara* start, char* objetivo, int regra[4]) {
    Pilha *raiz = pilha_cria();
    pilha_insere(raiz, start);
    Pilha *visitados = pilha_cria();
    int search = bt_search(raiz, visitados, getId((*raiz)->camara), objetivo, regra);
    //pilha_imprime(raiz);
    return search;
};

int visitado(char *objetivo, Pilha *pilha)
{
    if(pilha_vazia(pilha)) return 0;
    Elem *no = *pilha;
    while(no){
        if(strcmp(getId(no->camara), objetivo) == 0) return 1;
        no = no->prox;
    }
}

int bt_search(Pilha* atual, Pilha* visitados, char* raiz, char* objetivo, int regra[4]) {
    int i, b;
    Camara* vizinho;
    pilha_insere(visitados, (*atual)->camara);
    pilha_imprime(atual);

    if(strcmp(getId((*atual)->camara), objetivo) == 0) {
        return 1;
    } else {
        for(i = 0; i < 4; i++) {
            vizinho = getVizinho((*atual)->camara, regra[i]);
            if(vizinho != NULL && !visitado(vizinho, visitados)) {
                pilha_insere(atual, vizinho);
                b = bt_search(atual, visitados, raiz, objetivo, regra);
                if(b) return b;
            };
        }
        if(strcmp(getId((*atual)->camara), raiz) == 0) {
            return 0;
        }
        // backtracking:
        pilha_remove(atual);
        return bt_search(atual, visitados, raiz, objetivo, regra);
    }
};

int getHeuristica(hr* start, char* id);

hr* hrCreate(Camara* camara, hr* parent, int heuristica) {
    hr *thisHr = malloc(sizeof(hr));
    if(parent){
        parent->next = thisHr;
    }
    thisHr->prev = parent;
    thisHr->next = NULL;
    thisHr->camara = camara;
    thisHr->heuristica = heuristica;
    return thisHr;
};

void hrDelete(hr* thisHr) {
    hr* nextHr;
    while(thisHr) {
        nextHr = thisHr->next;
        free(thisHr);
        thisHr = nextHr;
    }
};

hr* hrReset(hr* thisHr) {
    if(!thisHr) return;
    while(thisHr->prev) {
        //printf(" %s \t %d\n", getId(thisHr->camara), thisHr->heuristica);
        thisHr = thisHr->prev;
    }
    //printf(" %s \t %d\n", getId(thisHr->camara), thisHr->heuristica);
    return thisHr;
};


void hrPrint(hr* thisHr) {
    if(!thisHr)  {
        printf("NULL hr\n");
        return;
    }
    while(thisHr->next) {
        printf(" %s \t %d\n", getId(thisHr->camara), thisHr->heuristica);
        thisHr = thisHr->next;
    }
    printf(" %s \t %d\n", getId(thisHr->camara), thisHr->heuristica);
    thisHr = hrReset(thisHr);
};


void gulosa(Camara* start, char* objetivo, int regra[4], hr* heuristica) {
    Pilha* raiz = pilha_cria();
    pilha_insere(raiz, start);
    int search = g_search(raiz, objetivo, regra, heuristica);
};

hr* findHr(hr* heuristica, char* qual) {
    while(heuristica) {
        if(strcmp(getId(heuristica->camara), qual) == 0) {
            return heuristica;
        }
        heuristica = heuristica->next;
    }
    return NULL;
};

Camara* minVizinho(Pilha* atual, int regra[4], hr* heuristica) {
    int i;
    Camara *vizinho, *retorno = NULL;
    hr* thisHr;

    int min = -1;

    for(i = 0; i < 4; i++) {
        vizinho = getVizinho((*atual)->camara, regra[i]);
        if(vizinho && !visitado(getId(vizinho), atual)) {
            thisHr = findHr(heuristica, getId(vizinho));
            if(thisHr) {
                thisHr = thisHr->heuristica;
                if(thisHr < min) {
                    min = thisHr;
                    retorno = vizinho;
                }
            } else {
                printf("Erro. thisHr = NULL\n");
                return NULL;
            }
        }
    }
    return retorno;
}

int g_search(Pilha* atual, char* objetivo, int regra[4], hr* heuristica) {
    Camara* vizinho;
    int i;
    pilha_imprime(atual);
    if(strcmp(getId((*atual)->camara), objetivo) == 0) {
        return 1;
    } else {
        /**
        abre_vizinhos(abertos);
        vizinho = minVizinho(abertos, heuristica);
        **/
        vizinho = minVizinho(atual, regra, heuristica);
        if(vizinho) {
            pilha_insere(atual, vizinho);
            g_search(atual, objetivo, regra, heuristica);
        } else {
            return 0;
        }
    }

};
/**
int g_search(lista* abertos, Pilha* fechados, char* objetivo)
    Camara* vizinho;
    int i;
    printf("%s ", getId(abertos->camara));
    if(!abertos) return 0;
    if(strcmp(getId(abertos->camara), objetivo) == 0) {
        return 1;
    } else {
        fecha(abertos, fechados);
        abreVizinhos(fechados);
        g_search(abertos, fechados, objetivo);
    }

**/
/*
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
    \\
    int* abertos;
    int sucesso = 0, fracasso = 0;
    Camara* N = raiz;
    while(!(sucesso || fracasso)) {
        if(abertos == NULL)
            fracasso = 1;
        else {

        }
    }
}
*/
