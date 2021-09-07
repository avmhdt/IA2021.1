#include "search.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

/*Camara* getCamara(No* node) {
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
    
    // Algoritmo Backtracking
    // In�cio
    // S := estado inicial;
    // N := S;
    // Fracasso := F;
    // Sucesso := F;
    // Enquanto n�o (Sucesso ou Fracasso) fa�a
    // Selecione o operador r de R(N);
    // Se R(N) <> vazio ent�o
    // N := r(N);
    // Se N � solu��o ent�o
    // Sucesso := T;
    // Fim-se;
    // Sen�o
    // Se N = S ent�o
    // Fracasso := T;
    // Sen�o
    // N := pai(N);
    // Fim-se;
    // Fim-se;
    // Fim-enquanto;
    // Fim.
    
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



*/




//verifica se a camara que vai ser colocada na lista é ancestral de si mesma
int ehPai(ElemFila* atual, Camara* camara) {
    int idPai = atual->idPai;
    ElemFila* no = atual;
    while(no->id>idPai) {
        no = no->ant;
        if(no == NULL) {
            return 0;
        }
    }
    if(!strcmp(no->camara->id, camara->id))
        return 1;
    return ehPai(no, camara);
}

Camara* buscaLargura(Camara* start, char* objetivo, int regra[4]) {
    
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
    Fila* abertos = fila_cria(); //fila
    Fila* fechados = fila_cria();
    int indice = 0;
    fila_insere(abertos, start, -1, indice);
    ElemFila* no = abertos->inicio;
    Camara* camara = no->camara;
    int sucesso = 0;
    while(!sucesso) {
        no = abertos->inicio;
        if(no == NULL)
            return NULL;
        else {
            camara = no->camara;
            //camara atual
            printf(camara->id);
            printf("  adiciona:\n");

            if(!strcmp(camara->id, objetivo)) {
                sucesso = 1;
                break;
            }
            else {
                int i = 0;
                fila_insere(fechados,no->camara, no->idPai, no->id);
                for(i; i<4; i++) {
                    if(camara->Camaralist[regra[i]] != NULL) {
                        if(!ehPai(fechados->final, camara->Camaralist[regra[i]])) {
                            printf(camara->Camaralist[regra[i]]->id);
                            indice++;
                            fila_insere(abertos, camara->Camaralist[regra[i]], no->id, indice);
                        }
                    }
                }
                fila_remove(abertos);
                printf("\n");
            }
        } 
    }
    return camara;
}