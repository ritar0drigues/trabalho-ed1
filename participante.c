#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // Para tolower
#include "participante.h"
#include "pilha.h"

// Converte string para minúsculas
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Cria e inicializa um novo participante
Participante* criarParticipante(char nome[], char matricula[], char email[]) {
    Participante *novo = malloc(sizeof(Participante));
    if (!novo) {
        printf("Erro ao alocar memória para participante.\n");
        exit(1);
    }

    toLowerCase(nome);
    toLowerCase(matricula);
    toLowerCase(email);

    strcpy(novo->nome, nome);
    strcpy(novo->matricula, matricula);
    strcpy(novo->email, email);
    novo->ant = NULL;
    novo->prox = NULL;
    novo->registrado = 0;
    return novo;
}

// Verifica se já existe participante com a mesma matrícula
int participanteExiste(Participante *lista, char matricula[]) {
    toLowerCase(matricula);
    while (lista != NULL) {
        if (strcmp(lista->matricula, matricula) == 0)
            return 1;
        lista = lista->prox;
    }
    return 0;
}

// Insere no fim da lista (se matrícula ainda não existir)
void inserirParticipante(Participante **lista, Participante *novo) {
    if (participanteExiste(*lista, novo->matricula)) {
        printf("Já existe um participante com essa matrícula.\n");
        free(novo);
        return;
    }

    novo->prox = NULL;
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

// Copia a lista de participantes
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

// Ordena por nome com Insertion Sort
Participante* insertionSortParticipantes(Participante *head) {
    Participante *sorted = NULL;

    while (head != NULL) {
        Participante *atual = head;
        head = head->prox;

        atual->ant = atual->prox = NULL;

        Participante *p = sorted;
        Participante *prev = NULL;

        while (p != NULL && strcmp(p->nome, atual->nome) < 0) {
            prev = p;
            p = p->prox;
        }

        if (prev == NULL) {
            atual->prox = sorted;
            if (sorted)
                sorted->ant = atual;
            sorted = atual;
        } else {
            atual->prox = prev->prox;
            atual->ant = prev;
            if (prev->prox)
                prev->prox->ant = atual;
            prev->prox = atual;
        }
    }

    return sorted;
}

// Lista participantes ordenados
void listarParticipantesOrdenado(Participante **lista) {
    if (*lista == NULL) {
        printf("Nenhum participante cadastrado.\n");
        return;
    }

    Participante *copia = copiarListaParticipantes(*lista);
    if (copia == NULL) {
        printf("Erro ao copiar a lista.\n");
        return;
    }

    copia = insertionSortParticipantes(copia);

    Participante *atual = copia;
    while (atual != NULL) {
        printf("\nNome: %s\n", atual->nome);
        printf("Matrícula: %s\n", atual->matricula);
        printf("Email: %s\n", atual->email);
        atual = atual->prox;
    }

    liberarParticipantes(&copia);
}

// Remove participante da lista e empilha
void removerParticipante(Participante **lista, char matricula[], Pilha *pilhaParticipantes) {
    if (*lista == NULL) {
        printf("Lista de participantes vazia.\n");
        return;
    }

    toLowerCase(matricula);

    Participante *atual = *lista;

    while (atual != NULL) {
        if (strcmp(atual->matricula, matricula) == 0) {
            if (atual->ant == NULL) {
                *lista = atual->prox;
                if (*lista != NULL)
                    (*lista)->ant = NULL;
            } else {
                atual->ant->prox = atual->prox;
                if (atual->prox != NULL)
                    atual->prox->ant = atual->ant;
            }

            atual->prox = NULL;
            atual->ant = NULL;
            pilha_inserir(pilhaParticipantes, (void *)atual);
            printf("Participante removido e salvo para desfazer.\n");
            return;
        }
        atual = atual->prox;
    }

    printf("Participante não encontrado.\n");
}

// Desfaz a última remoção
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

    inserirParticipante(listaParticipantes, participante);
    printf("Desfazer: participante '%s' restaurado com sucesso.\n", participante->nome);
}

// Libera memória dos participantes
void liberarParticipantes(Participante **lista) {
    Participante *atual = *lista;
    while (atual != NULL) {
        Participante *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    *lista = NULL;
}
