#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento.h"


Evento* criarEvento(char nome[], char data[]){
    Evento *novo = (Evento*)malloc(sizeof(Evento));
    strcpy(novo->nome, nome);
    strcpy(novo->data, data);
    novo->atividades = NULL; 
    novo->prox = novo;
    return novo;
}

void inserirEvento(Evento **lista, Evento *novo){
    Evento *aux = *lista, *ant = NULL;

    if (*lista == NULL){
        *lista = novo;
    }

    while (aux->prox != *lista){
        aux = aux->prox;
    }

    novo->prox = *lista;
    aux->prox = novo;
    *lista = novo;
}

void listarEventos(Evento *lista){
    Evento *atual = lista;
    if (lista = NULL){
    printf("NÃO EXISTEM EVENTOS A SEREM LISTADOS");
    return;
    }
    else{
        do{ 
        printf("\nEvento: %s\n", atual->nome);
        printf("Data: %s\n", atual->data);
        atual = atual->prox;
        } while(atual != lista);
    }
}
