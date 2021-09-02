#include "labyrinth.h"
#include <stdio.h>
#include <stdlib.h>

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

int insertVizinho(Camara* camara, Camara* parent, int pos) {
    if(pos < 0 || pos > 3) {
        printf("Error. pos out of bounds.\n");
        return -1;
    }
//    if(parent->Camaralist[pos] != NULL) {
//        printf("Error inserting camara. Position full.");
//        return -2;
//    }
    parent->Camaralist[pos] = camara;
    return 0;
};

void setVizinhosNULL(Camara* camara) {
    camara->Camaralist[UP_POS] = NULL;
    camara->Camaralist[DOWN_POS] = (Camara*)NULL;
    camara->Camaralist[RIGHT_POS] = (Camara*)NULL;
    camara->Camaralist[LEFT_POS] = (Camara*)NULL;

};

void traverseLabyrinth(Camara* camara, int regras[4]) {
    if(camara == NULL) return;
    printf("%s\n", getId(camara));
    int i;
    for(i = 0; i < 4; i++) {
        traverseLabyrinth(getVizinho(camara, regras[i]), regras);
    }
};
