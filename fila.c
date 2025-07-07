#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int fila_contem_participante(Fila *f, char matricula[]) {
    if (fila_vazia(f)) return 0;
    
    nofila *atual = f->inicio;
    while (atual != NULL) {
        if (strcmp(atual->valor->matricula, matricula) == 0) {
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

void fila_imprimir(Fila *f) {
    if (fila_vazia(f)) {
        printf("\n----------------------------------------\n");
        printf("Nenhum participante registrado ainda.\n");
        printf("----------------------------------------\n");
        return;
    }

    nofila *atual = f->inicio;
    int posicao = 1;
    printf("\n----------------------------------------\n");
    printf("      ORDEM DE CHEGADA DOS PARTICIPANTES    \n");
    printf("----------------------------------------\n");
    while (atual != NULL) {
        printf("%d. Nome: %s\n", posicao, atual->valor->nome);
        printf("   Matrícula: %s\n", atual->valor->matricula);
        printf("----------------------------------------\n");
        atual = atual->prox;
        posicao++;
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

void credenciar_participantes(Fila *f) {
    printf("\n============================================\n");
    printf("      CREDENCIAMENTO DE PARTICIPANTES       \n");
    printf("============================================\n");
    if (fila_vazia(f)) {
        printf("A fila de credenciamento está vazia. Nenhum participante para credenciar.\n");
        return;
    }

    printf("Credenciando participantes (FIFO):\n");
    int count = 0;
    while (!fila_vazia(f) && count < 3) { // Credencia até 3 participantes para demonstração
        Participante *p = fila_retira(f);
        if (p != NULL) {
            printf("  - %s (Matrícula: %s) credenciado com sucesso!\n", p->nome, p->matricula);
            count++;
        }
    }
    if (!fila_vazia(f)) {
        printf("\nRestam participantes na fila de credenciamento. Use a opção 12 para ver a fila atualizada.\n");
    } else {
        printf("\nTodos os participantes da fila de credenciamento foram credenciados.\n");
    }
}