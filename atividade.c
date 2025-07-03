#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // Para tolower
#include "atividade.h"
#include "pilha.h"

// Converte string para minúsculas
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Cria uma nova atividade
Atividade* criarAtividade(char titulo[], char horario[]) {
    Atividade *nova = malloc(sizeof(Atividade));
    if (!nova) {
        printf("Erro ao alocar memória para atividade.\n");
        exit(1);
    }
    toLowerCase(titulo);
    strcpy(nova->titulo, titulo);
    strcpy(nova->horario, horario);
    nova->participantes = NULL;
    nova->prox = NULL;
    return nova;
}

// Verifica se já existe atividade com mesmo título
int atividadeExiste(Atividade *lista, char titulo[]) {
    toLowerCase(titulo);
    while (lista != NULL) {
        if (strcmp(lista->titulo, titulo) == 0)
            return 1;
        lista = lista->prox;
    }
    return 0;
}

// Insere atividade no fim da lista (se não for duplicada)
void inserirAtividade(Atividade **lista, Atividade *nova) {
    if (atividadeExiste(*lista, nova->titulo)) {
        printf("Já existe uma atividade com esse título.\n");
        free(nova);  // evita vazamento de memória
        return;
    }

    nova->prox = NULL;

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

// Divide a lista em duas metades
void dividirLista(Atividade *origem, Atividade **frente, Atividade **tras) {
    Atividade *rapido;
    Atividade *lento;
    if (origem == NULL || origem->prox == NULL) {
        *frente = origem;
        *tras = NULL;
    } else {
        lento = origem;
        rapido = origem->prox;

        while (rapido != NULL) {
            rapido = rapido->prox;
            if (rapido != NULL) {
                lento = lento->prox;
                rapido = rapido->prox;
            }
        }

        *frente = origem;
        *tras = lento->prox;
        lento->prox = NULL;
    }
}

// Intercala duas listas ordenadas por horário
Atividade* intercalarListas(Atividade *a, Atividade *b) {
    Atividade *resultado = NULL;

    if (a == NULL) return b;
    else if (b == NULL) return a;

    if (strcmp(a->horario, b->horario) <= 0) {
        resultado = a;
        resultado->prox = intercalarListas(a->prox, b);
    } else {
        resultado = b;
        resultado->prox = intercalarListas(a, b->prox);
    }

    return resultado;
}

// Função principal de ordenação com Merge Sort
void mergeSortAtividades(Atividade **cabecaRef) {
    Atividade *cabeca = *cabecaRef;
    Atividade *a;
    Atividade *b;

    if ((cabeca == NULL) || (cabeca->prox == NULL)) {
        return;
    }

    dividirLista(cabeca, &a, &b);

    mergeSortAtividades(&a);
    mergeSortAtividades(&b);

    *cabecaRef = intercalarListas(a, b);
}

void listarAtividadesOrdenadas(Atividade *lista) {
    if (lista == NULL) {
        printf("Nenhuma atividade cadastrada.\n");
        return;
    }

    // Faz uma cópia da lista
    Atividade *copia = NULL;
    Atividade *atual = lista;
    while (atual != NULL) {
        Atividade *nova = criarAtividade(atual->titulo, atual->horario);
        inserirAtividade(&copia, nova);
        atual = atual->prox;
    }

    // Ordena a cópia
    mergeSortAtividades(&copia);

    // Imprime lista ordenada
    listarAtividadesSemOrdenar(copia);

    // Libera a cópia
    liberarAtividades(&copia);
}

void listarAtividadesSemOrdenar(Atividade *lista) {
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

    toLowerCase(titulo);

    Atividade *atual = *lista;
    Atividade *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->titulo, titulo) == 0) {
            if (anterior == NULL) {
                *lista = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            liberarParticipantes(&atual->participantes);
            atual->participantes = NULL;
            atual->prox = NULL;

            pilha_inserir(pilhaAtividades, (void *)atual);
            printf("Atividade removida e salva para desfazer.\n");
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }

    printf("Atividade não encontrada.\n");
}

// Desfaz a última remoção de atividade
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

    inserirAtividade(listaAtividades, atividade);
    printf("Desfazer: atividade '%s' restaurada com sucesso.\n", atividade->titulo);
}

// Busca uma atividade pelo título
Atividade* buscarAtividade(Atividade *lista, char titulo[]) {
    toLowerCase(titulo);
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
