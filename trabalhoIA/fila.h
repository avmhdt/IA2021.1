#ifndef FILA_H
#define FILA_H

typedef struct fila Fila;

Fila* fila_cria();
void fila_libera(Fila *fila);
int fila_vazia(Fila *fila);
int fila_tamanho(Fila *fila);
int fila_insere(Fila *fila, int dado);
int fila_remove(Fila *fila);
int fila_consulta(Fila *fila, int *dado);
void fila_imprime(Fila *fila);

int fila_insere_ord(Fila* fila, Camara* camara);

#endif
