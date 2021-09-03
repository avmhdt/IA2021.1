/*
    header labyrinth.h
    implementação dos nós do labirinto
*/

#ifndef LABYRINTH_H
#define LABYRINTH_H

#define MAX_ID_LEN 1
#define UP_POS 0
#define DOWN_POS 1
#define RIGHT_POS 2
#define LEFT_POS 3

// Tipo estruturado para os Camaras do labirinto
// possui um identificador, um booleaCamara se for o Camara objetivo
// e uma lista de Camaras vizinhos
typedef struct camara {
    char id[MAX_ID_LEN];
    int objetivo;
    struct Camara* Camaralist[4];
} Camara;

int getObjetivo(Camara* camara);
void setObjetivo(Camara* camara, int objetivo);

char* getId(Camara* camara);
void setId(Camara* camara, char id[]);

Camara* getVizinho(Camara* camara, int pos);
int insertVizinho(Camara* camara, Camara* parent, int pos);

void setVizinhosNULL(Camara* camara);

void traverseLabyrinth(Camara* camara, int regras[4]);

#endif // LABYRINTH_H
