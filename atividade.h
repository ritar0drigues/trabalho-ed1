#ifndef ATIVIDADE_H
#define ATIVIDADE_H

#include "participante.h"

typedef struct Atividade {
    char titulo[100];
    char horario[6];
    struct Participante *participantes;
    struct Atividade *prox;
} Atividade;

Atividade* criarAtividade(char titulo[], char horario[]);
void inserirAtividade(Atividade **lista, Atividade *novo);
void listarAtividades(Atividade *lista);
void removerAtividade(Atividade **lista, char nome[]);
Atividade* buscarAtividade(Atividade *lista, char titulo[]);
void liberarAtividades(Atividade **lista);

#endif