#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento.h"

// Cria um evento com nome e data
Evento* criarEvento(char nome[], char data[]) {
    Evento *novo = malloc(sizeof(Evento));
    if (!novo) {
        printf("Erro ao alocar memória para evento.\n");
        exit(1);
    }
    strcpy(novo->nome, nome);
    strcpy(novo->data, data);
    novo->atividades = NULL;
    novo->prox = novo; // lista circular
    return novo;
}

// Insere um evento na lista circular
void inserirEvento(Evento **lista, Evento *novo) {
    if (*lista == NULL) {
        *lista = novo;
    } else {
        Evento *atual = *lista;
        while (atual->prox != *lista) {
            atual = atual->prox;
        }
        atual->prox = novo;
        novo->prox = *lista;
    }
}

// Lista todos os eventos
void listarEventos(Evento *lista) {
    if (lista == NULL) {
        printf("Nenhum evento cadastrado.\n");
        return;
    }

    Evento *atual = lista;
    do {
        printf("\nEvento: %s\n", atual->nome);
        printf("Data: %s\n", atual->data);
        listarAtividades(atual->atividades); // lista as atividades do evento
        atual = atual->prox;
    } while (atual != lista);
}

// Remove um evento pelo nome
void removerEvento(Evento **lista, char nome[]) {
    if (*lista == NULL) {
        printf("Nenhum evento para remover.\n");
        return;
    }

    Evento *atual = *lista;
    Evento *anterior = NULL;

    do {
        if (strcmp(atual->nome, nome) == 0) {
            if (atual == atual->prox) {
                // Único evento na lista
                liberarAtividades(&atual->atividades);
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
                    anterior->prox = atual->prox;
                }
                liberarAtividades(&atual->atividades);
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

// Busca um evento pelo nome
Evento* buscarEvento(Evento *lista, char nome[]) {
    if (lista == NULL) return NULL;

    Evento *atual = lista;
    do {
        if (strcmp(atual->nome, nome) == 0)
            return atual;
        atual = atual->prox;
    } while (atual != lista);

    return NULL;
}

// Libera todos os eventos e suas atividades
void liberarEventos(Evento **lista) {
    if (*lista == NULL) return;

    Evento *inicio = *lista;
    Evento *atual = *lista;
    Evento *prox;

    do {
        prox = atual->prox;
        liberarAtividades(&atual->atividades);
        free(atual);
        atual = prox;
    } while (atual != inicio);

    *lista = NULL;
}
