#ifndef EVENTO_H
#define EVENTO_H

#include "atividade.h"

typedef struct Participante {
    char nome[100];
    char matricula[10];
    char email[50];
    Atividade* atividades;
    Participante* ant;
    Participante* prox;
} Participante;

Participante* criarParticipante(char nome[], char matricula[], char email[]);
void inserirParticipante(Participante **lista, Participante *novo);
void listarParticipantes(Participante *lista);
void removerParticipante(Participante **lista, char matricula[]);
Participante* buscarParticipante(Participante *lista, char matricula[]);
void liberarParticipantes(Participante **lista);
#endif 