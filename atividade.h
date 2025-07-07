#ifndef ATIVIDADE_H
#define ATIVIDADE_H

#include "participante.h"
#include "pilha.h"
#include "utils.h"

typedef struct Atividade {
    char titulo[100];
    char horario[6];
    struct Participante *participantes;
    struct Atividade *prox;
} Atividade;

Atividade* criarAtividade(char titulo[], char horario[]);
void inserirAtividade(Atividade **lista, Atividade *novo);
void dividirLista(Atividade *origem, Atividade **frente, Atividade **tras);
Atividade* intercalarListas(Atividade *a, Atividade *b);
void mergeSortAtividades(Atividade **cabecaRef);
void listarAtividadesOrdenadas(Atividade *lista);
void listarAtividadesSemOrdenar(Atividade *lista);
void removerAtividade(Atividade **lista, char titulo[], Pilha *pilhaAtividades);
void desfazerRemocaoAtividade(Pilha *pilhaAtividades, Atividade **listaAtividades);
Atividade* buscarAtividade(Atividade *lista, char titulo[]);
void liberarAtividades(Atividade **lista);
// Converte string para minúsculas
void toLowerCase(char *str);

#endif