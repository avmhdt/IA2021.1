#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pilha.h"
#include "lista.h"
#include "search.h"

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

int ehPai2(ElemFila* atual, Camara* camara) {
    int idPai = atual->idPai;
    ElemFila* no = atual;
    while(no) {
        if(no->id == idPai) {
            if(!strcmp(no->camara->id, camara->id))
                return 1;
            idPai = no->idPai;
        }
        no = no->ant;
        if(no == NULL) {
            return 0;
        }
    }
    return 0;
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

int existeMenor(Fila* fila, ElemFila* no, char* id) {
    int peso = no->fn;
    ElemFila* noFila = fila->inicio;
    while(noFila) {
        if(!strcmp(noFila->camara->id, id)) {
            if(noFila->fn <= peso)
                return 1;
            fila_remove_ord(fila, noFila->id);
            fila_insere(fila, no->camara, no->idPai, no->id);
            fila->final->custo = no->custo;
            fila->final->fn = no->custo + no->camara->hn;
            return 0;
        }
        noFila = noFila->prox;
    }
    fila_insere(fila, no->camara, no->idPai, no->id);
    fila->final->custo = no->custo;
    fila->final->fn = no->custo + no->camara->hn;
    return 0;
}

Camara* buscaLargura(Camara* start, char* objetivo, int regra[4]) {
    clock_t tempo;
    tempo = clock();
    Fila* abertos = fila_cria();
    Fila* fechados = fila_cria();
    int indice = 0;
    int nFechados = 0;
    fila_insere(abertos, start, -1, indice);
    ElemFila* no;
    Camara* camara;
    int sucesso = 0;
    int profundidade = 0;
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
            int aux = indice;
            fila_insere(fechados, camara, no->idPai, no->id);
            for(i; i<4; i++) {
                Camara* prox = camara->Camaralist[regra[i]];
                if(prox != NULL) {
                    if(!ehPai(fechados->final, prox)) {
                        indice++;
                        fila_insere(abertos, prox, no->id, indice);
                        abertos->final->custo = no->custo + camara->pesos[regra[i]];
                        abertos->final->profundidade = no->profundidade + 1;
                    }
                }
            }
            if(aux != indice) {
                nFechados++;
                if(abertos->final->profundidade > profundidade)
                    profundidade = abertos->final->profundidade;
            }
            fila_remove(abertos);
        }
    }

    printf("Tempo de execução - busca em largura: %fs\n", (float) (clock()-tempo)/CLOCKS_PER_SEC);
    printf("Caminho: ");
    caminho(fechados, no->idPai, camara->id);
    printf("Nós fechados: %d\n", fila_tamanho(fechados));
    printf("Custo solução: %d\n", no->custo);
    printf("Profundidade: %d\n", profundidade);
    printf("Fator médio de ramificação: %f\n\n",(float) indice/nFechados);
    return camara;
}
//fim busca em largura

//começo busca em profundidade
Camara* buscaProfundidade(Camara* start, char* objetivo, int regra[4], int profundidade) {
    clock_t tempo;
    tempo = clock();
    Pilha *abertos = pilha_cria();
    Fila *fechados = fila_cria();
    pilha_insere(abertos, start);
    (*abertos)->profundidade = 0;
    (*abertos)->idPai = -1;
    (*abertos)->id = 0;
    Camara* camara;
    ElemPilha* no;
    int sucesso = 0;
    int profundidadeNova;
    int profundidadeMax = 0;
    int indice = 0;
    int nFechados = 0;
    while(!sucesso) {
        no = *abertos;
        if(no == NULL)
            return NULL;
        camara = no->camara;
        profundidadeNova = no->profundidade+1;
        if(!strcmp(camara->id, objetivo)) {
            sucesso = 1;
            break;
        }
        else if(profundidadeNova<profundidade){
            int custo = no->custo;
            fila_insere(fechados, camara, no->idPai, no->id);
            pilha_remove(abertos);
            int aux = indice;
            int i = 3;
            for(i; i>=0; i--) {
                Camara* prox = camara->Camaralist[regra[i]];
                if(prox != NULL) {
                    if(!ehPai(fechados->final, prox)) {
                        indice++;
                        pilha_insere(abertos, prox);
                        (*abertos)->profundidade = profundidadeNova;
                        (*abertos)->idPai = fechados->final->id;
                        (*abertos)->id = indice;
                        (*abertos)->custo = camara->pesos[regra[i]] + custo;
                    }
                }
            }
            if(aux != indice) {
                nFechados++;
                if(profundidadeNova > profundidadeMax)
                    profundidadeMax = profundidadeNova;
            }
        }
        else {
            pilha_remove(abertos);
        }
    }
    
    printf("Tempo de execução - busca em profundidade: %fs\n", (float) (clock()-tempo)/CLOCKS_PER_SEC);
    printf("Caminho: ");
    caminho(fechados, no->idPai, camara->id);
    printf("Nós fechados: %d\n", fila_tamanho(fechados));
    printf("Custo solução: %d\n", no->custo);
    printf("Profundidade: %d\n", profundidadeMax);
    printf("Fator médio de ramificação: %f\n\n", (float) indice/nFechados);
    
    return camara;
}
//fim busca em profundidade

//começo busca A*
Camara* buscaA(Camara* start, char* objetivo) {
    clock_t tempo;
    tempo = clock();
    Fila* abertos = fila_cria();
    Fila* fechados = fila_cria();
    Fila* menorValor = fila_cria();
    Fila* podado = fila_cria();
    int indice = 0;
    fila_insere(abertos, start, -1, indice);
    ElemFila* no;
    Camara* camara;
    int nFechados = 0;
    int sucesso = 0;
    int profundidade = 0;
    while(!sucesso) {
        no = abertos->inicio;
        if(no == NULL) {
            //fila_imprime(ordenada);
            return NULL;
        }
        camara = no->camara;
        if(!existeMenor(menorValor, no, no->camara->id)) {
            if(!strcmp(camara->id, objetivo)) {
                sucesso = 1;
                break;
            }
            else {
                int i = 0;
                int aux = indice;
                fila_insere(fechados, camara, no->idPai, no->id);
                //fila_insere(menorValor, camara, no->idPai, no->id);
                fechados->final->custo = no->custo;
                for(i; i<4; i++) {
                    Camara* prox = camara->Camaralist[i];
                    if(prox != NULL) {
                        if(!ehPai2(fechados->final, prox)) {
                            indice++;
                            fila_insere_ord_fn(abertos, prox, indice, camara->pesos[i], no);
                        }
                    }
                }
                if(aux != indice) {
                    nFechados++;
                    if(no->profundidade + 1 > profundidade)
                        profundidade = no->profundidade + 1;
                }
                fila_remove_ord(abertos, no->id);
            }
        }
        else {
            fila_insere(podado, no, no->idPai, no->id);
            fila_remove_ord(abertos, no->id);
        }
    }

    printf("Tempo de execução - busca A*: %fs\n", (float) (clock()-tempo)/CLOCKS_PER_SEC);
    printf("Caminho: ");
    caminho(fechados, no->idPai, camara->id);
    printf("Nós fechados: %d\n", fila_tamanho(fechados));
    printf("Custo solução: %d\n", no->custo);
    printf("Profundidade: %d\n", profundidade);
    printf("Fator médio de ramificação: %f\n\n", (float) (indice-fila_tamanho(podado))/nFechados);

    return camara;
}
//fim busca A*

//começo busca ordenada
  void buscaOrdenada(Camara* start, char* objectivo, int regra[4]){
    clock_t tempo;
    tempo = clock();
    int sucesso = 0, custo;
    No atual;
    // No anterior;
    Lista *abertos = lista_cria();
    Lista *fechados = lista_cria();

    // printf("AHSIUAHSIAHSIH\n\n\n\n%s---%s", getId(start),  getId(start));
    lista_insere(abertos, getId(start),  getId(start), 0, start);

    while(!sucesso){
      atual = getMenorCusto(abertos);
      custo = atual->custo;
      Camara *cam = atual->camara;
      if(!strcmp(cam->id, objectivo)) {
            sucesso = 1;
            // break;
        }
      // printf("\n------------------------------------------------\n");
      
      
      // printf("\n\nNO ATUAL_______%c___%c", atual->id[0], atual->idPai[0]);
      
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
            // printf("\n\nINSERINDO -- %s -- %s -- %d",getId(cam->Camaralist[i]), getId(cam), custo);
            lista_insere(abertos, getId(cam->Camaralist[i]), getId(cam), custo, cam->Camaralist[i]);
            }
          }
          // printf("fim");
        }
      }
      // printf("\n\nSAIU DO LOOP_______%c___%c", atual->id[0], atual->idPai[0]);
     
      // printf("\n\nREMOVEU_______%c___%c", atual->id[0], atual->idPai[0]);
      lista_insere(fechados, atual->id, atual->idPai, 0, cam);
      lista_remove(abertos, cam);

      lista_imprime(abertos, fechados);
      // lista_imprime(fechados);
      
    }
    No vish = fechados->inicio;
    while (vish->prox){
      vish = vish->prox;
    }
    
    printf("\n\n\nTempo de execução - busca ordenada: %fs\n", (float) (clock()-tempo)/CLOCKS_PER_SEC);
    printf("Caminho: ");
    caminho2(fechados, start, objectivo);
    printf("\nNós fechados: %d\n", lista_tamanho(fechados));
    printf("Custo solução: %d\n",custo);
    // printf("Profundidade: %d\n", profundidade);
    // printf("Fator médio de ramificação: %f\n\n", (float) (indice-fila_tamanho(podado))/nFechados);
    printf("\n\n\n");
}
//fim busca ordenada

