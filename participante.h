#ifndef PARTICIPANTE_H
#define PARTICIPANTE_H
#include "participante.h"
#include "pilha.h"
#include "utils.h"

// Funções para manipular a lista duplamente encadeada
typedef struct Participante{
    char nome[100];
    char matricula[20];
    char email[100];
    int registrado;
    struct Participante *ant;
    struct Participante *prox;
} Participante;

Participante* criarParticipante(char nome[], char matricula[], char email[]);
void inserirParticipante(Participante **lista, Participante *novo);
void listarParticipantes(Participante **lista);
Participante* copiarListaParticipantes(Participante *origem);
Participante* insertionSortParticipantes(Participante *head);
void listarParticipantesOrdenado(Participante **lista);
void removerParticipante(Participante **lista, char matricula[], Pilha *pilhaParticipantes);
void desfazerRemocaoParticipante(Pilha *pilhaParticipantes, Participante **listaParticipantes);
void liberarParticipantes(Participante **lista);

#endif

