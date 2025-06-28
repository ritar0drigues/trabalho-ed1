#ifndef PILHA_H
#define PILHA_H

#include "participante.h"
#include "atividade.h"
#include "evento.h"

typedef struct no{
    int valor;
    struct no *prox;
}no;

typedef struct pilha{
    no *topo;
} pilha;

Pilha *pilha_vazia(void){
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    if(p!= NULL){
        p->topo = NULL;
        return p;
    }
}

void Inserir(Pilha *p, int valor){
    no *novo = (no*)malloc(sizeof(no));
    if(novo == NULL){
        printf("Erro de alocação.\n");
        exit(1);
    }
    novo->valor = valor;
    novo->prox=p->topo;
    p->topo = novo;
}

int pilha_pop(Pilha *p){
    if(pilha_vazia(p)){
        
    }
}
#endif