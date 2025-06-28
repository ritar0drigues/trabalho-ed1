#ifndef PILHA_H
#define PILHA_H

// Estrutura do nó da pilha genérica
typedef struct no {
    void *dado;         // Ponteiro genérico para qualquer tipo (Atividade ou Participante)
    struct no *prox;    // Próximo nó
} no;

// Estrutura da pilha
typedef struct {
    no *topo;           // Ponteiro para o topo da pilha
} Pilha;

// Cria e retorna uma nova pilha vazia
Pilha *pilha_cria(void);

// Insere um novo item no topo da pilha
void pilha_inserir(Pilha *p, void *dado);

// Remove e retorna o item do topo da pilha
void *pilha_pop(Pilha *p);

// Verifica se a pilha está vazia (1 = sim, 0 = não)
int pilha_vazia(Pilha *p);

// Libera toda a memória da pilha (mas não libera os dados)
void pilha_libera(Pilha *p);

#endif