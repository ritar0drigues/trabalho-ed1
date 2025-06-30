#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila *fila_cria(void) {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    if (f != NULL) {
        f->inicio = NULL;
        f->fim = NULL;
    }
    return f;
}

int fila_vazia(Fila *f) {
    return (f->inicio == NULL);
}

void fila_inserir(Fila *f, Participante *p) {
    nofila *novo = (nofila *)malloc(sizeof(nofila));
    if (novo == NULL) {
        printf("Erro de alocação na fila.\n");
        exit(1);
    }
    novo->valor = p;
    novo->prox = NULL;

    if (fila_vazia(f)) {
        f->inicio = novo;
    } else {
        f->fim->prox = novo;
    }
    f->fim = novo;
}

void fila_imprimir(Fila *f) {
    if (fila_vazia(f)) {
        printf("Fila vazia.\n");
        return;
    }

    nofila *atual = f->inicio;
    printf("Ordem de chegada dos participantes:\n");
    while (atual != NULL) {
        printf("- %s (%s)\n", atual->valor->nome, atual->valor->matricula);
        atual = atual->prox;
    }
}

Participante *fila_retira(Fila *f) {
    if (fila_vazia(f)) {
        printf("Fila vazia.\n");
        return NULL;
    }

    nofila *remover = f->inicio;
    Participante *p = remover->valor;

    f->inicio = remover->prox;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    free(remover);
    return p;
}

void fila_libera(Fila *f) {
    nofila *atual = f->inicio;
    while (atual != NULL) {
        nofila *temp = atual->prox;
        free(atual);
        atual = temp;
    }
    free(f);
}
