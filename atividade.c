#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atividade.h"
#include "pilha.h"

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
    nova->prox= NULL; // limpa ponteiro antigo

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


// Remove atividade da lista e empilha a atividade removida
void removerAtividade(Atividade **lista, char titulo[], Pilha *pilhaAtividades) {
    if (*lista == NULL) {
        printf("Lista de atividades vazia.\n");
        return;
    }

    Atividade *atual = *lista;
    Atividade *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->titulo, titulo) == 0) {
            // Remove da lista encadeada
            if (anterior == NULL) {
                *lista = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            // Remove participantes internos para evitar memória pendente
            liberarParticipantes(&atual->participantes);
            atual->participantes = NULL;

            // Limpa ponteiro para evitar loops ao restaurar
            atual->prox = NULL;

            // Empilha o ponteiro da atividade removida para possível restauração
            pilha_inserir(pilhaAtividades, (void *)atual);

            printf("Atividade removida e salva para desfazer.\n");
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


// Desfaz a última remoção de atividade (restaura na lista)
void desfazerRemocaoAtividade(Pilha *pilhaAtividades, Atividade **listaAtividades) {
    if (pilha_vazia(pilhaAtividades)) {
        printf("Nenhuma remoção de atividade para desfazer.\n");
        return;
    }

    Atividade *atividade = (Atividade *) pilha_pop(pilhaAtividades);

    if (atividade == NULL) {
        printf("Erro ao recuperar atividade da pilha.\n");
        return;
    }

    // Reinsere atividade na lista
    inserirAtividade(listaAtividades, atividade);
    printf("Desfazer: atividade '%s' restaurada com sucesso.\n", atividade->titulo);
}
