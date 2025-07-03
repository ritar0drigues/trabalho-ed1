#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // Para tolower()
#include "evento.h"
#include "atividade.h"

// Converte string para minúsculas
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Cria um evento com nome e data
Evento* criarEvento(char nome[], char data[]) {
    Evento *novo = malloc(sizeof(Evento));
    if (!novo) {
        printf("Erro ao alocar memória para evento.\n");
        exit(1);
    }
    toLowerCase(nome);
    strcpy(novo->nome, nome);
    strcpy(novo->data, data);
    novo->atividades = NULL;
    novo->prox = novo; // lista circular
    return novo;
}

// Verifica se já existe evento com o mesmo nome
int eventoExiste(Evento *lista, char nome[]) {
    if (lista == NULL) return 0;
    Evento *atual = lista;
    do {
        if (strcmp(atual->nome, nome) == 0)
            return 1;
        atual = atual->prox;
    } while (atual != lista);
    return 0;
}

// Insere um evento na lista circular
void inserirEvento(Evento **lista, Evento *novo) {
    if (eventoExiste(*lista, novo->nome)) {
        printf("Já existe um evento com esse nome.\n");
        free(novo); // evita vazamento de memória
        return;
    }

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
    printf("Evento inserido com sucesso.\n");
}

// Lista todos os eventos
void listarEventos(Evento *lista) {
    if (lista == NULL) {
        printf("Nenhum evento cadastrado.\n");
        return;
    }

    Evento *atual = lista;
    printf("--EVENTOS:");
    do {
        printf("\nEvento: %s\n", atual->nome);
        printf("Data: %s\n", atual->data);
        listarAtividadesSemOrdenar(atual->atividades);
        atual = atual->prox;
    } while (atual != lista);
}

// Remove um evento pelo nome
void removerEvento(Evento **lista, char nome[]) {
    if (*lista == NULL) {
        printf("Nenhum evento para remover.\n");
        return;
    }

    toLowerCase(nome);

    Evento *atual = *lista;
    Evento *anterior = NULL;

    do {
        if (strcmp(atual->nome, nome) == 0) {
            if (atual == atual->prox) {
                liberarAtividades(&atual->atividades);
                free(atual);
                *lista = NULL;
            } else {
                if (atual == *lista) {
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

    toLowerCase(nome);

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
