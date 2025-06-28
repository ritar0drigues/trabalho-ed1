// pilha.c
#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

// Cria uma nova pilha vazia
Pilha *pilha_cria(void) {
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    if (p != NULL) {
        p->topo = NULL;
    }
    return p;
}

// Insere um novo item no topo da pilha
void pilha_inserir(Pilha *p, void *dado) {
    no *novo = (no *)malloc(sizeof(no));
    if (novo == NULL) {
        printf("Erro de alocação na pilha.\n");
        exit(1);
    }
    novo->dado = dado;
    novo->prox = p->topo;
    p->topo = novo;
}

// Remove e retorna o item do topo da pilha
void *pilha_pop(Pilha *p) {
    if (pilha_vazia(p)) {
        printf("Pilha vazia.\n");
        return NULL;
    }
    no *remover = p->topo;
    void *dado = remover->dado;
    p->topo = remover->prox;
    free(remover);
    return dado;
}

// Retorna 1 se a pilha estiver vazia, 0 caso contrário
int pilha_vazia(Pilha *p) {
    return (p->topo == NULL);
}

// Libera a pilha (os nós), mas não libera os dados armazenados
void pilha_libera(Pilha *p) {
    no *atual = p->topo;
    while (atual != NULL) {
        no *temp = atual;
        atual = atual->prox;
        free(temp); // Não dá free no dado para evitar duplo free
    }
    free(p);
}
