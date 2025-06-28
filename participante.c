#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "participante.h"

// Cria e inicializa um novo participante
Participante* criarParticipante(char nome[], char matricula[], char email[]) {
    Participante *novo = malloc(sizeof(Participante));
    if (!novo) {
        printf("Erro ao alocar memória para participante.\n");
        exit(1);
    }
    strcpy(novo->nome, nome);
    strcpy(novo->matricula, matricula);
    strcpy(novo->email, email);
    novo->ant = NULL;
    novo->prox = NULL;
    return novo;
}

// Insere no fim da lista
void inserirParticipante(Participante **lista, Participante *novo) {
    if (*lista == NULL) {
        *lista = novo;
    } else {
        Participante *atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
        novo->ant = atual;
    }
}

// Lista todos os participantes
void listarParticipantes(Participante *lista) {
    if (lista == NULL) {
        printf("Nenhum participante cadastrado.\n");
        return;
    }

    Participante *atual = lista;
    while (atual != NULL) {
        printf("\nNome: %s\n", atual->nome);
        printf("Matrícula: %s\n", atual->matricula);
        printf("Email: %s\n", atual->email);
        atual = atual->prox;
    }
}

// Remove participante com base na matrícula
void removerParticipante(Participante **lista, char matricula[]) {
    if (*lista == NULL) {
        printf("Lista de participantes vazia.\n");
        return;
    }

    Participante *atual = *lista;

    while (atual != NULL) {
        if (strcmp(atual->matricula, matricula) == 0) {
            if (atual->ant == NULL) {
                // Primeiro da lista
                *lista = atual->prox;
                if (*lista != NULL) {
                    (*lista)->ant = NULL;
                }
            } else {
                atual->ant->prox = atual->prox;
                if (atual->prox != NULL) {
                    atual->prox->ant = atual->ant;
                }
            }
            free(atual);
            printf("Participante removido com sucesso.\n");
            return;
        }
        atual = atual->prox;
    }

    printf("Participante não encontrado.\n");
}

// Busca participante pela matrícula
Participante* buscarParticipante(Participante *lista, char matricula[]) {
    while (lista != NULL) {
        if (strcmp(lista->matricula, matricula) == 0)
            return lista;
        lista = lista->prox;
    }
    return NULL;
}

// Libera a memória de todos os participantes da lista
void liberarParticipantes(Participante **lista) {
    Participante *atual = *lista;
    while (atual != NULL) {
        Participante *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    *lista = NULL;
}
