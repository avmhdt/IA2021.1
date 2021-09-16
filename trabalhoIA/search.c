#include "search.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
#include "lista.h"

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

int caminho(Fila* fechados, int idPai, char* final) {
    ElemFila* no = fechados->final;
    printf("%s", final);
    while(no) {
        if(no->id == idPai) {
            printf("<-%s",no->camara->id);
            idPai = no->idPai;
            if(idPai == -1) {
                printf("\n");
                return 0;
            }
        }
        no = no->ant;
    }
    return 0;
}

Camara* buscaLargura(Camara* start, char* objetivo, int regra[4]) {
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
                Camara* prox = camara->Camaralist[regra[i]];
                if(prox != NULL) {
                    if(!ehPai(fechados->final, prox)) {
                        indice++;
                        fila_insere(abertos, prox, no->id, indice);
                    }
                }
            }
            fila_remove(abertos);
        }
    }
    int nFechados = fila_tamanho(fechados);
    printf("Caminho: ");
    caminho(fechados,no->idPai,camara->id);
    printf("Nós fechados: %d\n",nFechados);
    printf("Custo solução: %d\n",no->custo);
    printf("Fator médio de ramificação: %f\n",(float) indice/nFechados);
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
                Camara* prox = camara->Camaralist[regra[i]];
                if(prox != NULL) { 
                    if(!visitado(prox->id, fechados)) {
                        printf(prox->id);
                        pilha_insere(abertos, prox);
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
    printf("Fechados: %d\n",pilha_imprime(fechados));
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
                Camara* prox = camara->Camaralist[regra[i]];
                if(prox != NULL) {
                    if(!ehPai(fechados->final, prox)) {
                        indice++;
                        printf(prox->id);
                        pilha_insere(abertos, prox);
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
    /*
    int nFechados = fila_tamanho(fechados);
    printf("Caminho: ");
    caminho(fechados,no->idPai,camara->id);
    printf("Nós fechados: %d\n",nFechados);
    printf("Custo solução: %d\n",no->custo);
    printf("Fator médio de ramificação: %f\n",(float) indice/nFechados);*/
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
    Fila* abertos = fila_cria();
    Fila* fechados = fila_cria();
    int indice = 0;
    fila_insere(abertos, start, -1, indice);
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
            fechados->final->custo = no->custo;
            for(i; i<4; i++) {
                Camara* prox = camara->Camaralist[regra[i]];
                if(prox != NULL) {
                    if(!ehPai(fechados->final, prox)) {
                        printf("%d,%d,%s\n",no->id,no->idPai,no->camara->id);
                        indice++;
                        fila_insere_ord_fn(abertos, prox, no->id, indice, no->custo, camara->pesos[regra[i]]);
                    }
                }
            }
            fila_remove_ord(abertos, no->id);
        }
    }
    int nFechados = fila_tamanho(fechados);
    printf("Caminho: ");
    caminho(fechados,no->idPai,camara->id);
    printf("Nós fechados: %d\n",nFechados);
    printf("Custo solução: %d\n",no->custo);
    printf("Fator médio de ramificação: %f\n",(float) indice/nFechados);
    return camara;
}
//fim busca A*

//começo busca ordenada
void buscaOrdenada(Camara* start, char* objectivo, int regra[4]){

    Lista *abertos = lista_cria();
    Lista *fechados = lista_cria();

    lista_insere(abertos, getId(start),  getId(start), 0, start);

    for (int k=0; k<21; k++){
      // printf("\n------------------------------------------------\n");
      No atual = getMenorCusto(abertos);
      // printf("\n\nNO ATUAL_______%c", atual->id[0]);
      Camara *cam = atual->camara;
      // printf("\n\n\nCAMARA ATUAL_______%c", cam->id[0]);
      int i=0;
      for (i; i<4; i++){
        
        if (cam->Camaralist[i]){
          Camara *novaCam = cam->Camaralist[i];
          // printf("\n\n %d ----- %c \n\n", i, novaCam->id[0]);
          int custo = (cam->pesos[i]);
          custo += atual->custo;
          
          if (lista_busca(fechados, novaCam->id[0]) == -1){
            if (lista_compara(abertos, getId(cam->Camaralist[i]), custo) == 1){
              
              lista_remove(abertos, cam->Camaralist[i]);
              lista_insere(abertos, getId(cam->Camaralist[i]), getId(cam), custo, cam->Camaralist[i]);
            } else if (lista_compara(abertos, getId(cam->Camaralist[i]), custo) == 0){
            lista_insere(abertos, getId(cam->Camaralist[i]), getId(cam), custo, cam->Camaralist[i]);
            }
          }
          // printf("fim");
        }
      }
      lista_remove(abertos, cam);
      // printf("REMOVEU");
      lista_insere(fechados, getId(cam), getId(cam), 0, cam);

      lista_imprime(abertos, fechados);
      // lista_imprime(fechados);
    }
}
//fim busca ordenada