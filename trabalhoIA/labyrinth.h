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
    int hn;
    int pesos[4];
    Camara* Camaralist[4];
};

int getObjetivo(Camara* camara);
void setObjetivo(Camara* camara, int objetivo);

char* getId(Camara* camara);
void setId(Camara* camara, char id[]);

Camara* getVizinho(Camara* camara, int pos);
int insertVizinho(Camara* camara, Camara* parent, int pos, int peso);

void setVizinhosNULL(Camara* camara);

Camara* getById (Camara lista[], int size, char *id[]);

#endif // LABYRINTH_H
