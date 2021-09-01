#include "labyrinth.h"
#include <stdio.h>
#include <stdlib.h>

int getObjetivo(No* node) {
    return node->objetivo;
};

void setObjetivo(No* node, int objetivo) {
    node->objetivo = objetivo;
};

char* getId(No* node) {
    return &(node->id[0]);
};
void setId(No* node, char id[]) {
    strcpy(node->id, id);
};

No* getVizinho(No* node, int pos) {
    No** vizinhos = node->nolist;
    return vizinhos[pos];
};

int insertVizinho(No* node, No* parent, int pos) {
    if(pos < 0 || pos > 3) {
        printf("Error. pos out of bounds.\n");
        return -1;
    }
//    if(parent->nolist[pos] != NULL) {
//        printf("Error inserting node. Position full.");
//        return -2;
//    }
    parent->nolist[pos] = node;
    return 0;
};

void setVizinhosNULL(No* node) {
    node->nolist[UP_POS] = NULL;
    node->nolist[DOWN_POS] = (No*)NULL;
    node->nolist[RIGHT_POS] = (No*)NULL;
    node->nolist[LEFT_POS] = (No*)NULL;

};
