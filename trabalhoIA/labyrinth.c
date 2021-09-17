#include "labyrinth.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getObjetivo(Camara* camara) {
    return camara->objetivo;
};

void setObjetivo(Camara* camara, int objetivo) {
    camara->objetivo = objetivo;
};

char* getId(Camara* camara) {
    return camara->id;
};

void setId(Camara* camara, char id[]) {
    strcpy(camara->id, id);
};

Camara* getVizinho(Camara* camara, int pos) {
    Camara** vizinhos = camara->Camaralist;
    return vizinhos[pos];
};

int insertVizinho(Camara* camara, Camara* parent, int pos, int peso) {
    if(pos < 0 || pos > 3) {
        printf("Error. pos out of bounds.\n");
        return -1;
    }
    parent->Camaralist[pos] = camara;
    parent->pesos[pos] = peso;
    return 0;
};

void setVizinhosNULL(Camara* camara) {
    camara->Camaralist[UP_POS] = NULL;
    camara->Camaralist[DOWN_POS] = (Camara*)NULL;
    camara->Camaralist[RIGHT_POS] = (Camara*)NULL;
    camara->Camaralist[LEFT_POS] = (Camara*)NULL;

};

Camara* getById (Camara lista[], int size, char *id[]){
    int i = 0;
    for (i; i<size; i++){
      if (!strcmp(lista[i].id, id[0])){
        Camara *cam = &lista[i];
        return cam;
      }
    }
    Camara *nulo = malloc(sizeof(Camara));
    setId(nulo, "nu");
    return nulo;
}

