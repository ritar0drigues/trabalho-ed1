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

// Lista os participantes da lista duplamente encadeada
void listarParticipantes(Participante **lista) {
    if (*lista == NULL) {
        printf("Nenhum participante cadastrado.\n");
        return;
    }

    Participante *atual = *lista;
    while (atual != NULL) {
        printf("\nNome: %s\n", atual->nome);
        printf("Matrícula: %s\n", atual->matricula);
        printf("Email: %s\n", atual->email);
        atual = atual->prox;
    }
}

// Função para copiar a lista de participantes (cria nova lista com mesmo conteúdo)
Participante* copiarListaParticipantes(Participante *origem) {
    Participante *copia = NULL, *fim = NULL;

    while (origem != NULL) {
        Participante *novo = malloc(sizeof(Participante));
        if (!novo) {
            printf("Erro de memória.\n");
            liberarParticipantes(&copia);
            return NULL;
        }
        strcpy(novo->nome, origem->nome);
        strcpy(novo->matricula, origem->matricula);
        strcpy(novo->email, origem->email);
        novo->prox = NULL;
        novo->ant = fim;

        if (fim != NULL)
            fim->prox = novo;
        else
            copia = novo;

        fim = novo;
        origem = origem->prox;
    }
    return copia;
}

// Função de Insertion Sort para ordenar a lista duplamente encadeada por nome
Participante* insertionSortParticipantes(Participante *head) {
    Participante *sorted = NULL;

    while (head != NULL) {
        Participante *atual = head;
        head = head->prox;

        // Desconecta o nó para inserção
        atual->ant = atual->prox = NULL;

        Participante *p = sorted;
        Participante *prev = NULL;
        // Procura a posição de inserção na lista 'sorted'
        while (p != NULL && strcmp(p->nome, atual->nome) < 0) {
            prev = p;
            p = p->prox;
        }

        if (prev == NULL) {
            // Insere no início da lista ordenada
            atual->prox = sorted;
            if (sorted)
                sorted->ant = atual;
            sorted = atual;
        } else {
            // Insere entre 'prev' e 'p'
            atual->prox = prev->prox;
            atual->ant = prev;
            if (prev->prox)
                prev->prox->ant = atual;
            prev->prox = atual;
        }
    }

    return sorted;
}

// Função para listar os participantes ordenados por nome (usa cópia para manter a lista original)
void listarParticipantesOrdenado(Participante **lista) {
    if (*lista == NULL) {
        printf("Nenhum participante cadastrado.\n");
        return;
    }

    // Copia a lista original
    Participante *copia = copiarListaParticipantes(*lista);
    if (copia == NULL) {
        printf("Erro ao copiar a lista.\n");
        return;
    }

    // Ordena a cópia usando insertion sort
    copia = insertionSortParticipantes(copia);

    // Exibe a lista ordenada
    Participante *atual = copia;
    while (atual != NULL) {
        printf("\nNome: %s\n", atual->nome);
        printf("Matrícula: %s\n", atual->matricula);
        printf("Email: %s\n", atual->email);
        atual = atual->prox;
    }

    // Libera a memória da cópia para evitar vazamentos
    liberarParticipantes(&copia);
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

