/*
    header labyrinth.h
    implementação dos nós do labirinto
*/

#define MAX_ID_LEN 2
#define UP_POS 0
#define DOWN_POS 1
#define RIGHT_POS 2
#define LEFT_POS 3

// Tipo estruturado para os nos do labirinto
// possui um identificador, um booleano se for o No objetivo
// e uma lista de nos vizinhos
typedef struct node {
    char id[MAX_ID_LEN+1];
    int objetivo;
    struct No** nolist;
} No;

int getObjetivo(No* node);
void setObjetivo(No* node, int objetivo);

char* getId(No* node);
void setId(No* node, char id[]);

No* getVizinho(No* node, int pos);
int insertVizinho(No* node, No* parent, int pos);
