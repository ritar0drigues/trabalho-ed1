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