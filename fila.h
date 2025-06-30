// fila.h
#ifndef FILA_H
#define FILA_H

#include "participante.h"

typedef struct nofila {
    Participante *valor;
    struct nofila *prox;
} nofila;

typedef struct {
    nofila *inicio;
    nofila *fim;
} Fila;

Fila *fila_cria(void);
int fila_vazia(Fila *f);
void fila_inserir(Fila *f, Participante *p);
void fila_imprimir(Fila *f);
Participante *fila_retira(Fila *f);
void fila_libera(Fila *f);

#endif
