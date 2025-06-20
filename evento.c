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
    Evento *aux = *lista;

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
    
    if(lista == NULL){
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

void removerEvento(Evento **lista, char nome[]){
    if (*lista == NULL) {
        printf("Nenhum evento para remover.\n");
        return;
    }

    Evento *atual = *lista;
    Evento *anterior = NULL;

    do {
        if (strcmp(atual->nome, nome) == 0) {
            if (atual == atual->prox) {
                // Único elemento
                free(atual);
                *lista = NULL;
            } else {
                if (atual == *lista) {
                    // Removendo o primeiro
                    Evento *ultimo = *lista;
                    while (ultimo->prox != *lista) {
                        ultimo = ultimo->prox;
                    }
                    *lista = atual->prox;
                    ultimo->prox = *lista;
                } else {
                    // Removendo do meio/fim
                    anterior->prox = atual->prox;
                }
                free(atual);
            }
            printf("Evento removido com sucesso.\n");
            return;
        }
        anterior = atual;
        atual = atual->prox;
    } while (atual != *lista);

    printf("Evento não encontrado.\n");

}
