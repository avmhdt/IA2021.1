/*
    header labyrinth.h
    implementa��o dos n�s do labirinto
*/
#ifndef LABYRINTH_H
#define LABYRINTH_H

#define MAX_ID_LEN 10
#define UP_POS 0
#define DOWN_POS 1
#define RIGHT_POS 2
#define LEFT_POS 3


// Tipo estruturado para os Camaras do labirinto
// possui um identificador, um booleaCamara se for o Camara objetivo
// e uma lista de Camaras vizinhos

typedef struct camara Camara;

struct camara{
    char id[MAX_ID_LEN];
    int objetivo;
    Camara* Camaralist[4];
};

int getObjetivo(Camara* Camarade);
void setObjetivo(Camara* Camarade, int objetivo);

char* getId(Camara* Camarade);
void setId(Camara* Camarade, char id[]);

Camara* getVizinho(Camara* Camarade, int pos);
int insertVizinho(Camara* Camarade, Camara* parent, int pos);

void setVizinhosNULL(Camara* Camarade);

void traverseLabyrinth(Camara* camara, int regras[4]);

#endif