#ifndef PARTICIPANTE_H
#define PARTICIPANTE_H
#include "participante.h"

typedef struct Participante{
    char nome[100];
    char matricula[20];
    char email[100];
    struct Participante *ant;
    struct Participante *prox;
} Participante;

// Funções para manipular a lista duplamente encadeada
Participante* criarParticipante(char nome[], char matricula[], char email[]);
void inserirParticipante(Participante **lista, Participante *novo);
void listarParticipantes(Participante *lista);
void removerParticipante(Participante **lista, char matricula[]);
Participante* buscarParticipante(Participante *lista, char matricula[]);
void liberarParticipantes(Participante **lista);

#endif

