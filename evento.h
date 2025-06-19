#ifndef EVENTO_H
#define EVENTO_H

#include "atividade.h"

typedef struct Evento {
    char nome[100];
    char data[11];
    Atividade *atividades; // ponteiro para lista de atividades
    struct Evento *prox;
} Evento;

Evento* criarEvento(char nome[], char data[]);
void inserirEvento(Evento **lista, Evento *novo);
void listarEventos(Evento *lista);
void removerEvento(Evento **lista, char nome[]);

#endif