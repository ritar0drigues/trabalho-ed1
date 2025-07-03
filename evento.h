#ifndef EVENTO_H
#define EVENTO_H

#include "atividade.h" // Um evento possui uma lista de atividades

typedef struct Evento {
    char nome[100];
    char data[11]; // formato: dd/mm/aaaa
    Atividade *atividades; // lista encadeada simples de atividades
    struct Evento *prox;   // lista circular de eventos
} Evento;

// Cria um novo evento
Evento* criarEvento(char nome[], char data[]);

// Insere um evento na lista circular
void inserirEvento(Evento **lista, Evento *novo);

// Lista todos os eventos cadastrados
void listarEventos(Evento *lista);

// Remove um evento pelo nome
void removerEvento(Evento **lista, char nome[]);

// Busca evento pelo nome
Evento* buscarEvento(Evento *lista, char nome[]);

// Libera toda a lista de eventos (e suas atividades)
void liberarEventos(Evento **lista);

// Converte string para minúsculas
void toLowerCase(char *str);

#endif
