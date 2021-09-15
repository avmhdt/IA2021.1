#include "search.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

void backtracking(Camara* start, char* objetivo, int regra[4]) {
    Pilha *raiz = pilha_cria();
    pilha_insere(raiz, start);
    Pilha *visitados = pilha_cria();
    int search = bt_search(raiz, visitados, getId((*raiz)->camara), objetivo, regra);
    //pilha_imprime(raiz);
    return;
};

int visitado(char *objetivo, Pilha *pilha)
{
    if(pilha_vazia(pilha)) return 0;
    ElemPilha *no = *pilha;
    while(no){
        if(strcmp(getId(no->camara), objetivo) == 0) return 1;
        no = no->prox;
    }
    return 0;
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
            if(vizinho != NULL && !visitado(vizinho->id, visitados)) {
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
        
        // abre_vizinhos(abertos);
        // vizinho = minVizinho(abertos, heuristica);
        
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

void fecha(fila* abertos, fila* fechados) {
    ElemFila *inicio = abertos->inicio;
    fila_insere(fechados, inicio->camara, inicio->idPai, inicio->id);
    fila_remove(abertos);
}

void abreVizinhos(fechados) {

}

int g_search(fila* abertos, fila* fechados, char* objetivo)
    Camara* vizinho;
    int i;
    printf("%s ", getId(abertos->inicio->camara));
    if(!abertos) return 0;
    if(strcmp(getId(abertos->inicio->camara), objetivo) == 0) {
        return 1;
    } else {
        fecha(abertos, fechados);
        abreVizinhos(fechados, abertos);
        g_search(abertos, fechados, objetivo);
    }

**/

//começo busca em largura
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

        camara = no->camara;
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
                        indice++;
                        fila_insere(abertos, camara->Camaralist[regra[i]], no->id, indice);
                    }
                }
            }
            fila_remove(abertos);
        }
    }
    return camara;
}
//fim busca em largura

//começo busca em profundidade
Camara* buscaProfundidade(Camara* start, char* objetivo, int regra[4], int profundidade) {
    //busca em profundidade modificada, não geração de estados já visitados
    Pilha *abertos = pilha_cria();
    Pilha *fechados = pilha_cria();
    pilha_insere(abertos, start);
    (*abertos)->profundidade = 0;
    Camara* camara;
    int sucesso = 0;
    int profundidadeNova;
    while(!sucesso) {
        ElemPilha* no = *abertos;
        if(no == NULL)
            return NULL;
        camara = no->camara;
        profundidadeNova = no->profundidade+1;
        if(!strcmp(camara->id, objetivo)) {
            sucesso = 1;
            break;
        }
        else if(profundidadeNova<profundidade){
            printf("Camara Aberta: ");
            printf(camara->id);
            printf("\n");
            pilha_insere(fechados, camara);
            pilha_remove(abertos);

            int i = 3;
            for(i; i>=0; i--) {
                if(camara->Camaralist[regra[i]] != NULL) { 
                    if(!visitado(camara->Camaralist[regra[i]]->id, fechados)) {
                        printf(camara->Camaralist[regra[i]]->id);
                        pilha_insere(abertos, camara->Camaralist[regra[i]]);
                        (*abertos)->profundidade = profundidadeNova;
                    }
                }
            }
        }
        else {
            pilha_remove(abertos);
        }
        printf("\nLista: ");
        pilha_imprime(abertos);
    }
    return camara;
}

Camara* buscaProfundidade2(Camara* start, char* objetivo, int regra[4], int profundidade) {
    //busca em profundidade não modificada
    Pilha *abertos = pilha_cria();
    Fila *fechados = fila_cria();
    pilha_insere(abertos, start);
    (*abertos)->profundidade = 0;
    (*abertos)->idPai = -1;
    (*abertos)->id = 0;
    Camara* camara;
    int sucesso = 0;
    int profundidadeNova;
    int indice = 0;
    while(!sucesso) {
        ElemPilha* no = *abertos;
        if(no == NULL)
            return NULL;
        camara = no->camara;
        profundidadeNova = no->profundidade+1;
        if(!strcmp(camara->id, objetivo)) {
            sucesso = 1;
            break;
        }
        else if(profundidadeNova<profundidade){
            printf("Camara Aberta: ");
            printf(camara->id);
            printf("\n");
            fila_insere(fechados, camara, no->idPai, no->id);
            pilha_remove(abertos);

            int i = 3;
            for(i; i>=0; i--) {
                if(camara->Camaralist[regra[i]] != NULL) {
                    if(!ehPai(fechados->final, camara->Camaralist[regra[i]])) {
                        indice++;
                        printf(camara->Camaralist[regra[i]]->id);
                        pilha_insere(abertos, camara->Camaralist[regra[i]]);
                        (*abertos)->profundidade = profundidadeNova;
                        (*abertos)->idPai = fechados->final->id;
                        (*abertos)->id = indice;
                    }
                }
            }
        }
        else {
            pilha_remove(abertos);
        }
        printf("\nLista: ");
        pilha_imprime(abertos);
    }
    return camara;
}
//fim busca em profundidade

//começo busca A*
Camara* buscaA(Camara* start, char* objetivo, int regra[4]) {
    // fracasso := F; sucesso := F; defina(abertos);
    // S := raiz; calcule(f(S));
    // insere(S, abertos); defina(fechados);
    // enquanto não (sucesso ou fracasso) faça
    //  se abertos = vazio então
    //      fracasso := T;
    //  senão
    //      N := primeiro(abertos); // nó com o menor f
    //      se N = solução então
    //          sucesso := T;
    //      senão
    //          enquanto R(N) ≠ vazio faça
    //              escolha r de R(N); new(u);
    //              u := r(N); calcule(f(u));
    //              insere(u, abertos); // se u não for ancestral de n
    //              atualiza R(N);
    //          fim-enquanto;
    //          insere(N, fechados); // destrói N
    //      fim-se;
    //  fim-se;
    // fim-enquanto;
    // fim.
    Fila* abertos = fila_cria(); //fila
    Fila* fechados = fila_cria();
    Fila* ordenada = fila_cria();
    int indice = 0;
    fila_insere(abertos, start, -1, indice);
    fila_insere(ordenada, start, -1, indice);
    ElemFila* no = abertos->inicio;
    Camara* camara = no->camara;
    int sucesso = 0;
    while(!sucesso) {
        no = abertos->inicio;
        if(no == NULL) {
            //fila_imprime(ordenada);
            return NULL;
        }
        camara = no->camara;
        if(!strcmp(camara->id, objetivo)) {
            sucesso = 1;
            break;
        }
        else {
            int i = 0;
            fila_insere(fechados, no->camara, no->idPai, no->id);
            for(i; i<4; i++) {
                if(camara->Camaralist[regra[i]] != NULL) {
                    if(!ehPai(fechados->final, camara->Camaralist[regra[i]])) {
                        indice++;
                        fila_insere(abertos, camara->Camaralist[regra[i]], no->id, indice);
                        fila_insere_ord_gn(ordenada,  camara->Camaralist[regra[i]], no->id, indice, no->custo, camara->gn[regra[i]]);
                    }
                }
            }
            fila_remove(abertos);
        }
    }
    //fila_imprime(ordenada);
    return camara;
}
//fim busca A*