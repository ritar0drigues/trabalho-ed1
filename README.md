# Sistema de Organização de Eventos Acadêmicos

Este projeto implementa um sistema para organização de eventos acadêmicos, utilizando diferentes estruturas de dados dinâmicas em C. O sistema permite gerenciar eventos, atividades e participantes, além de realizar operações de check-in, desfazer remoções e ordenar dados.

## Estruturas de Dados Utilizadas

- **Lista Encadeada Circular:** Gerencia os eventos cadastrados.
- **Lista Encadeada Simples:** Gerencia as atividades de cada evento.
- **Lista Duplamente Encadeada:** Gerencia os participantes de cada atividade.
- **Fila:** Gerencia a ordem de check-in dos participantes em cada evento (FIFO).
- **Pilha:** Permite desfazer a última remoção de atividade ou participante (LIFO).
- **Algoritmos de Ordenação:** 
  - Merge Sort (recursivo) para ordenar atividades por horário.
  - Insertion Sort (iterativo) para ordenar participantes por nome.

## Funcionalidades

### 1. Eventos (Lista Encadeada Circular)
- **Cadastrar Evento:** Adiciona um novo evento com nome e data.
- **Listar Eventos:** Exibe todos os eventos cadastrados.
- **Remover Evento:** Remove um evento selecionado.

Cada evento possui uma lista de atividades associada.

### 2. Atividades (Lista Encadeada Simples)
- **Cadastrar Atividade:** Adiciona uma atividade (título, horário) a um evento.
- **Listar Atividades:** Exibe todas as atividades de um evento.
- **Remover Atividade:** Remove uma atividade de um evento.

Cada atividade possui uma lista de participantes associada.

### 3. Participantes (Lista Duplamente Encadeada)
- **Cadastrar Participante:** Adiciona um participante (nome, matrícula, e-mail) a uma atividade.
- **Listar Participantes:** Exibe todos os participantes de uma atividade.
- **Remover Participante:** Remove um participante de uma atividade.

### 4. Fila de Check-in
- **Registrar Check-in:** Adiciona participantes à fila de check-in do evento, controlando a ordem de chegada.
- **Listar Check-in:** Exibe a ordem de chegada dos participantes.

### 5. Pilha de Desfazer
- **Desfazer Remoção:** Permite restaurar a última atividade ou participante removido.

### 6. Algoritmos de Ordenação
- **Atividades por Horário:** Ordenação usando Merge Sort (recursivo).
- **Participantes por Nome:** Ordenação usando Insertion Sort (iterativo).

## Estrutura dos Dados

- **Evento:** Nome, data, ponteiro para lista de atividades.
- **Atividade:** Título, horário, ponteiro para lista de participantes.
- **Participante:** Nome, matrícula, e-mail.

## Como Usar

1. Clone este repositório:
   ```bash
   git clone https://github.com/seuusuario/seurepositorio.git
   cd seurepositorio
   ```

2. Compile o projeto:
   ```bash
   gcc main.c -o eventos
   ```

3. Execute o sistema:
   ```bash
   ./eventos
   ```

4. Siga o menu interativo para cadastrar, listar, remover e ordenar eventos, atividades e participantes.

## Exemplo de Uso

- Cadastrar um evento: Informe nome e data.
- Adicionar atividades ao evento: Informe título e horário.
- Adicionar participantes à atividade: Informe nome, matrícula e e-mail.
- Realizar check-in dos participantes no evento.
- Remover uma atividade ou participante e desfazer a remoção se necessário.
- Ordenar atividades por horário ou participantes por nome.

## Observações

- O sistema utiliza ponteiros para conectar as estruturas de dados.
- Todas as operações são realizadas em memória.
- O código é modularizado para facilitar manutenção e expansão.

## Licença

Este projeto é de uso acadêmico e livre para estudos.

---
