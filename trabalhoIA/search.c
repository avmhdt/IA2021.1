#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pilha.h"
#include "lista.h"
#include "search.h"

void backtracking(Camara* start, char* objetivo, int regra[4]) {

    printf("\n******** Backtracking ********\n");

    int* folhas = malloc(sizeof(int));
    *folhas = 0;

    int *custo = malloc(sizeof(double));
    *custo = 0;

    clock_t timeStart = clock();
    Pilha *raiz = pilha_cria();
    pilha_insere(raiz, start);
    Pilha *visitados = pilha_cria();
    int search = bt_search(raiz, visitados, getId((*raiz)->camara), objetivo, regra, folhas, custo  );
    clock_t timeEnd = clock();

    double executionTime = (double) (timeEnd - timeStart)/CLOCKS_PER_SEC;
    char sucesso;
    if(search) {
        sucesso = 'S';
    } else sucesso = 'N';

    int nvisitados = pilha_conta(visitados);
    double frm = (double)(nvisitados-1)/(double)(nvisitados - *folhas - 1);

    printf("\nSucesso? %c\n", sucesso);
    printf("Caminho: ");
    pilha_imprime(raiz);
    printf("\nCusto: %d\n", *custo);
    printf("Expandidos/Visitados: %d\n", nvisitados);
    printf("Fator de ramificacao medio: %.2f\n", frm);
    printf("Tempo de execucao: %.6f s\n", executionTime);

    //pilha_imprime(visitados);

    pilha_libera(raiz);
    pilha_libera(visitados);

    free(folhas);
    free(custo);

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

int bt_search(Pilha* atual, Pilha* visitados, char* raiz, char* objetivo, int regra[4], int *folhas, int* custo) {
    int i, b;
    Camara* vizinho;
    pilha_insere(visitados, (*atual)->camara);
    //pilha_imprime(atual);

    int j = 0;
    if(strcmp(getId((*atual)->camara), objetivo) == 0) {
        return 1;
    } else {
        for(i = 0; i < 4; i++) {
            vizinho = getVizinho((*atual)->camara, regra[i]);
            if(vizinho != NULL && !visitado(vizinho->id, visitados)) {
                //if(j == 0) {
                //    (*pais) += 1;
                //}
                //j++;
                //(*filhos) += 1;
                *custo += (*atual)->camara->pesos[regra[i]];
                pilha_insere(atual, vizinho);
                b = bt_search(atual, visitados, raiz, objetivo, regra, folhas, custo);
                if(b) return b; else *custo -= (*atual)->camara->pesos[regra[i]];
            } else j++;
        }
        if(j == 4) *folhas += 1;
        if(strcmp(getId((*atual)->camara), raiz) == 0) {
            return 0;
        }
        // backtracking:
        pilha_remove(atual);
        return bt_search(atual, visitados, raiz, objetivo, regra, folhas, custo);
    }
};

void gulosa(Camara* start, char* objetivo) {
    printf("\n******** Busca Gulosa *******\n");

    clock_t timeStart = clock();

    Fila *abertos = fila_cria();
    fila_insere_ord(abertos, start, -1, 0, 0, 0);

    Fila *fechados = fila_cria();
    int *fr = malloc(sizeof(int));
    *fr = 0;
    int search = g_search(abertos, fechados, objetivo, fr);
    clock_t timeEnd = clock();
    printf("\n");

    int prof = fila_conta(fechados) + 1;
    int expandidos = prof - 1 + fila_conta(abertos);
    int visitados = prof;
    double frm = (*fr)/(prof-1);
    double executionTime = (double)(timeEnd - timeStart)/CLOCKS_PER_SEC;

    char sucesso;
    if(search) {
        sucesso = 'S';
    } else sucesso = 'N';

    int custo = fechados->final->custo;

    printf("Sucesso? %c\n", sucesso);
    printf("Caminho: ");
    caminho(fechados, abertos->inicio->idPai, objetivo);
    printf("Custo: %d\n", custo);
    printf("Profundidade: %d\n", prof);
    printf("Expandidos: %d\n", expandidos);
    printf("Visitados: %d\n", visitados);
    printf("Fator de ramificacao medio: %.2f\n", frm);
    printf("Tempo de execucao: %.6f s\n", executionTime);

    //fila_imprime(fechados);

    free(fr);
    fila_libera(abertos);
    fila_libera(fechados);
};

void fecha(Fila* abertos, Fila* fechados) {
    ElemFila *inicio = abertos->inicio;
    fila_insere(fechados, inicio->camara, inicio->idPai, inicio->id);
    fechados->final->custo = inicio->custo;
    fila_remove(abertos);
}

int fechado(Camara* camara, Fila* fechados) {
    ElemFila* thisElem = fechados->inicio;
    while(thisElem) {
        if(strcmp(thisElem->camara->id, camara->id) == 0) {
            return 1;
        }
        thisElem = thisElem->prox;
    }
    return 0;
}

int abreVizinhos(Fila* fechados, Fila* abertos) {
    int regras[4] = {UP_POS, DOWN_POS, RIGHT_POS, LEFT_POS};
    int i;

    ElemFila* atual = fechados->final;
    Camara* vizinho;
    int j = 0;
    for(i = 0; i < 4; i++) {
        vizinho = atual->camara->Camaralist[regras[i]];
        if(vizinho && !fechado(vizinho, fechados)) {
            fila_insere_ord(abertos, vizinho, atual->id, atual->id+j+1, atual->camara->pesos[regras[i]], atual->custo);
            j++;
        }
    }
    return j;
}

int g_search(Fila* abertos, Fila* fechados, char* objetivo, int* fr) {
    if(!abertos) return 0;
    //printf("%s ", getId(abertos->inicio->camara));
    //fila_imprime(fechados);
    if(strcmp(getId(abertos->inicio->camara), objetivo) == 0) {
        //printf("\nCaminho: ");
        //caminho(fechados, abertos->inicio->idPai, objetivo);
        return 1;
    } else {
        fecha(abertos, fechados);
        *fr += abreVizinhos(fechados, abertos);
        g_search(abertos, fechados, objetivo, fr);
    }
}


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

Camara* buscaProfundidade(Camara* start, char* objetivo, int regra[4], int profundidade) {
    //busca em profundidade não modificada
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

    printf("Tempo de execução - busca A*: %10fs\n", (double) (clock()-tempo)/CLOCKS_PER_SEC);
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

    Lista *abertos = lista_cria();
    Lista *fechados = lista_cria();

    lista_insere(abertos, getId(start),  getId(start), 0, start);

    while(!sucesso){
      atual = getMenorCusto(abertos);
      custo = atual->custo;
      Camara *cam = atual->camara;
      if(!strcmp(cam->id, objectivo)) {
            sucesso = 1;
        }

      int i=0;
      for (i; i<4; i++){

        if (cam->Camaralist[i]){
          Camara *novaCam = cam->Camaralist[i];
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

        }
      }

      lista_insere(fechados, atual->id, atual->idPai, 0, cam);
      lista_remove(abertos, cam);

      // lista_imprime(abertos, fechados);


    }

    printf("\n\n\nTempo de execução - busca ordenada: %fs\n", (float) (clock()-tempo)/CLOCKS_PER_SEC);
    printf("Caminho: ");
    int profundidade = caminho2(fechados, start, objectivo);
    printf("\nNós fechados: %d\n", lista_tamanho(fechados));
    printf("Custo solução: %d\n",custo);

    printf("Profundidade: %d\n", profundidade);
    // printf("Fator médio de ramificação: %f\n\n", (float) (indice-fila_tamanho(podado))/nFechados);
    printf("\n");
}
//fim busca ordenada

/**
// Busca IDA*
Algoritmo IDA*
Início
    Fracasso := F; Sucesso := F;
    S := raiz; Calcule(f(S));
    Patamar := f(S); Patamar_Old := -1; N := S;
    Enquanto não (Sucesso ou Fracasso) faça
        Se Patamar_Old = Patamar então
            Fracasso := T;
        Senão_Se N = solução e f(N) <= patamar então
            Sucesso := T;
        Senão
            Se f(N) > patamar então
                Insere(N, descartado);
                N := pai(N);
            Fim-se;
            Se R(N) <> vazio então
                Escolha r de R(N);
                N := r(N); Calcule(f(N));
            Senão_Se N = S então
                Patamar_Old := Patamar;
                Patamar := min(f(N), N in descartado);
            Senão
                N := pai(N);
            Fim-se;
        Fim-se;
    Fim-enquanto;
Fim.
**/

int minFnDescartado(Pilha* descartados) {
    ElemPilha *thisElem = *descartados;
    int minfn;
    if(!thisElem) {
        return -1;
    }
    minfn = thisElem->fn;
    while(thisElem) {
        if(thisElem->fn < minfn) {
            minfn = thisElem->fn;
        }
        thisElem = thisElem->prox;
    }
    return minfn;
}

void ida(Camara* start, char* objetivo, int regra[4]) {
    printf("\n******* Busca IDA* ********\n");
    double executionTime;
    clock_t timeStart = clock();
    int nvisitados;
    int folhas = 0;
    double frm;
    Pilha* descartados = pilha_cria();
    Pilha* visitados = pilha_cria();
    Pilha* atual = pilha_cria();

    int sucesso = 0, fracasso = 0, i, RNvazio, j;
    Camara *N = start, *vizinho;

    int patamar = N->hn;
    int patamar_old = - 1;
    int fn, custo = 0, peso = 0;
    fn = N->hn + custo;
    pilha_insere(atual, N);
    (*atual)->fn = fn;
    (*atual)->peso = 0;
    while(!(sucesso || fracasso)) {
        //printf("%s ", N->id);
        //fn = N->hn + custo;
        //pilha_insere(atual, N);
        //(*atual)->fn = fn;

        pilha_insere(visitados, N);
        (*visitados)->fn = fn;
        //(*visitados)->peso = custo;

        fn = N->hn + custo;

        //pilha_imprime(atual);
        //printf("patamar = %d \t patamar_old = %d \t", patamar, patamar_old);
        //printf("custo = %d\n", custo);

        if(patamar_old == patamar) {
            fracasso = 1;
        } else if(strcmp(N->id, objetivo) == 0 && fn <= patamar) {
            sucesso = 1;
        } else {
            if(fn > patamar) {
                //printf("descartando %s\n", N->id);
                pilha_insere(descartados, N);
                (*descartados)->fn = fn;
                //(*descartados)->peso = custo;
                custo -= (*atual)->peso;
                pilha_remove(atual);
                N = (*atual)->camara;
            }
            RNvazio = 1;
            j = 0;
            for(i = 0; i < 4; i++) {
                vizinho = N->Camaralist[regra[i]];
                if(vizinho && !visitado(vizinho->id, visitados)) {
                    //printf("vizinho\n");
                    RNvazio = 0;
                    peso = N->pesos[regra[i]];
                    custo += peso;
                    N = vizinho;
                    fn = N->hn + custo;
                    pilha_insere(atual, N);
                    (*atual)->fn = fn;
                    (*atual)->peso = peso;
                    break;
                } else {
                    j++;
                }
            }
            if(j == 4) folhas++;
            if(RNvazio) {
                if(strcmp(N->id, start->id) == 0) {
                    //printf("reset\n");
                    patamar_old = patamar;
                    patamar = minFnDescartado(descartados);
                    if(patamar < 0) {
                        printf("ERROR: patamar < 0\n");
                        return;
                    }
                    while(!pilha_vazia(visitados)) {
                        pilha_remove(visitados);
                    }
                    while(!pilha_vazia(descartados)) {
                        pilha_remove(descartados);
                    }
                    folhas = 0;
                } else {
                    //printf("removendo\n");
                    //pilha_imprime(atual);
                    custo -= (*atual)->peso;
                    //printf("custo = %d\n", custo);
                    pilha_remove(atual);
                    //pilha_imprime(atual);
                    N = (*atual)->camara;
                    fn = N->hn + custo;
                }
            }

        }
    }
    nvisitados = pilha_conta(visitados);

    clock_t timeEnd = clock();
    executionTime = (double) (timeEnd - timeStart)/CLOCKS_PER_SEC;

    char suc;
    if(sucesso) {
        suc = 'S';
    } else suc = 'N';

    frm = (double)(nvisitados-1)/(double)(nvisitados-folhas-1);

    printf("\nSucesso? %c\n", suc);
    printf("Caminho: ");
    pilha_imprime(atual);
    printf("Custo: %d\n", custo);
    printf("Expandidos/Visitados: %d\n", nvisitados);
    printf("Fator de ramificacao medio: %.2f\n", frm);
    printf("Tempo de execucao: %.6f s", executionTime);

    pilha_libera(descartados);
    pilha_libera(visitados);
    pilha_libera(atual);

}
