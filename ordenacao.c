#include <stdio.h>
#include <stdlib.h>
#include "ordenacao.h"
#include <string.h>
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

// Lista todos os participante
void bubbleSortlistarRecursiv(Participante *lista, int n) {
    if (n == 1) 
        return;

    Participante *atual = lista;
    int trocou = 0;

    for (int i = 0; i < n - 1; i++) {
        if (strcmp(atual->nome, atual->prox->nome) > 0) {
            // Troca de participantes
            char tempNome[100], tempMatricula[20], tempEmail[100];

            // Armazena os dados temporariamente para a troca
            strcpy(tempNome, atual->nome);
            strcpy(tempMatricula, atual->matricula);
            strcpy(tempEmail, atual->email);

            // Realiza a troca
            strcpy(atual->nome, atual->prox->nome);
            strcpy(atual->matricula, atual->prox->matricula);
            strcpy(atual->email, atual->prox->email);

            strcpy(atual->prox->nome, tempNome);
            strcpy(atual->prox->matricula, tempMatricula);
            strcpy(atual->prox->email, tempEmail);

            trocou = 1;
        }
        atual = atual->prox;
    }

    // Se houve troca, faz outra passagem
    if (trocou) {
        bubbleSortRecursivo(lista, n - 1);
    }
}

// Função para contar o número de participantes na lista
int contarParticipantes(Participante *lista) {
    int n = 0;
    while (lista != NULL) {
        n++;
        lista = lista->prox;
    }
    return n;
}

// Lista todos os participantes com a ordenação Bubble Sort recursiva
void listarParticipantes(Participante *lista) {
    if (lista == NULL) {
        printf("Nenhum participante cadastrado.\n");
        return;
    }

    // Conta o número de participantes
    int n = contarParticipantes(lista);

    // Ordena os participantes usando Bubble Sort recursivo
    bubbleSortRecursivo(lista, n);

    // Imprime a lista ordenada
    Participante *atual = lista;
    while (atual != NULL) {
        printf("\nNome: %s\n", atual->nome);
        printf("Matrícula: %s\n", atual->matricula);
        printf("Email: %s\n", atual->email);
        atual = atual->prox;
    }
}
