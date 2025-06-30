#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "participante.h"
#include "pilha.h"

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
    novo->registrado = 0;  // Ainda não enfileirado
    return novo;
}

// Insere no fim da lista
void inserirParticipante(Participante **lista, Participante *novo) {
    novo->prox = NULL;  // Evita loops com ponteiros antigos
    novo->ant = NULL;

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


// Remove participante da lista e empilha o participante removido
void removerParticipante(Participante **lista, char matricula[], Pilha *pilhaParticipantes) {
    if (*lista == NULL) {
        printf("Lista de participantes vazia.\n");
        return;
    }

    Participante *atual = *lista;

    while (atual != NULL) {
        if (strcmp(atual->matricula, matricula) == 0) {
            // Remove da lista duplamente encadeada
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

            // Empilha o ponteiro do participante removido para possível restauração
            atual->prox = NULL;
            atual->ant = NULL;
            pilha_inserir(pilhaParticipantes, (void *)atual);
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

// Desfaz a última remoção de participante (restaura na lista)
void desfazerRemocaoParticipante(Pilha *pilhaParticipantes, Participante **listaParticipantes) {
    if (pilha_vazia(pilhaParticipantes)) {
        printf("Nenhuma remoção de participante para desfazer.\n");
        return;
    }

    Participante *participante = (Participante *) pilha_pop(pilhaParticipantes);

    if (participante == NULL) {
        printf("Erro ao recuperar participante da pilha.\n");
        return;
    }

    // Reinsere participante na lista
    inserirParticipante(listaParticipantes, participante);
    printf("Desfazer: participante '%s' restaurado com sucesso.\n", participante->nome);
}