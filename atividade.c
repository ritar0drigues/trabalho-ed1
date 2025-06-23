#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atividade.h"

// Cria uma nova atividade
Atividade* criarAtividade(char titulo[], char horario[]) {
    Atividade *nova = malloc(sizeof(Atividade));
    if (!nova) {
        printf("Erro ao alocar memória para atividade.\n");
        exit(1);
    }
    strcpy(nova->titulo, titulo);
    strcpy(nova->horario, horario);
    nova->participantes = NULL;
    nova->prox = NULL;
    return nova;
}

// Insere atividade no fim da lista
void inserirAtividade(Atividade **lista, Atividade *nova) {
    if (*lista == NULL) {
        *lista = nova;
    } else {
        Atividade *atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = nova;
    }
}

// Lista todas as atividades
void listarAtividades(Atividade *lista) {
    if (lista == NULL) {
        printf("Nenhuma atividade cadastrada.\n");
        return;
    }

    Atividade *atual = lista;
    while (atual != NULL) {
        printf("\nAtividade: %s\n", atual->titulo);
        printf("Horário: %s\n", atual->horario);
        atual = atual->prox;
    }
}

// Remove atividade pelo título
void removerAtividade(Atividade **lista, char titulo[]) {
    if (*lista == NULL) {
        printf("Lista de atividades vazia.\n");
        return;
    }

    Atividade *atual = *lista;
    Atividade *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->titulo, titulo) == 0) {
            if (anterior == NULL) {
                // Primeiro da lista
                *lista = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            liberarParticipantes(&atual->participantes); // limpa participantes
            free(atual);
            printf("Atividade removida com sucesso.\n");
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }

    printf("Atividade não encontrada.\n");
}

// Busca uma atividade pelo título (caso precise)
Atividade* buscarAtividade(Atividade *lista, char titulo[]) {
    while (lista != NULL) {
        if (strcmp(lista->titulo, titulo) == 0)
            return lista;
        lista = lista->prox;
    }
    return NULL;
}

// Libera toda a lista de atividades
void liberarAtividades(Atividade **lista) {
    Atividade *atual = *lista;
    while (atual != NULL) {
        Atividade *temp = atual;
        atual = atual->prox;
        liberarParticipantes(&temp->participantes);
        free(temp);
    }
    *lista = NULL;
}
