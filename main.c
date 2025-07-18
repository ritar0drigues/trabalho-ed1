#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento.h"
#include "atividade.h"
#include "participante.h"
#include "pilha.h"
#include "fila.h"

void credenciar_participantes(Fila *f);

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void menu() {
    printf("\n============================================\n");
    printf("           SISTEMA DE EVENTOS               \n");
    printf("============================================\n");
    printf("[1]  Cadastrar evento\n");
    printf("[2]  Listar eventos\n");
    printf("[3]  Remover evento\n");
    printf("[4]  Cadastrar atividade em evento\n");
    printf("[5]  Listar atividades de um evento\n");
    printf("[6]  Remover atividade de um evento\n");
    printf("[7]  Cadastrar participante em atividade\n");
    printf("[8]  Listar participantes de uma atividade\n");
    printf("[9]  Remover participante de uma atividade\n");
    printf("[10] Desfazer remoção de atividade\n");
    printf("[11] Desfazer remoção de participante\n");
    printf("[12] Listar ordem de chegada dos participantes\n");
    printf("[13] Credenciar participantes (FIFO)\n");
    printf("[0]  Sair\n");
    printf("============================================\n");
    printf("Digite sua opção: ");
}

void subMenuListagemAtividades() {
    printf("\n----------------------------------------\n");
    printf("Como deseja visualizar a lista?\n");
    printf("[1] Ordem original\n");
    printf("[2] Ordem de horário\n");
    printf("[0] Voltar\n");
    printf("----------------------------------------\n");
    printf("Escolha uma opção: ");
}

void subMenuListagemParticipantes() {
    printf("\n----------------------------------------\n");
    printf("Como deseja visualizar a lista?\n");
    printf("[1] Ordem original\n");
    printf("[2] Ordem ordem alfabética\n");
    printf("[0] Voltar\n");
    printf("----------------------------------------\n");
    printf("Escolha uma opção: ");
}



int main() {
    Evento *eventos = NULL;
    Pilha *pilhaAtividades = pilha_cria();
    Pilha *pilhaParticipantes = pilha_cria();
    Fila *filaChegada = fila_cria();

    int opcao;
    char nome[100], data[11], titulo[100], horario[6], matricula[20], email[100];

    do {
        limparTela();
        menu();
        scanf("%d", &opcao);
        getchar(); // consumir '\n'

        limparTela();
        switch(opcao) {
            case 1: {
                printf("============================================\n");
                printf("           CADASTRO DE EVENTO               \n");
                printf("============================================\n");
                char repetir;
                repetir = 's';
                while (repetir == 's' || repetir == 'S'){
                    printf("Nome do evento: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = 0;

                    printf("Data (dd/mm/aaaa): ");
                    fgets(data, sizeof(data), stdin);
                    data[strcspn(data, "\n")] = 0;

                    Evento *e = criarEvento(nome, data);
                    inserirEvento(&eventos, e);

                    printf("\nDeseja cadastrar outro evento?\n");
                    printf("Digite 's' para sim e 'n' para nao:");
                    scanf(" %c", &repetir);
                    getchar();
                }
                pausar();
                break;
            }

            case 2: {
                printf("============================================\n");
                printf("           LISTAGEM DE EVENTOS              \n");
                printf("============================================\n");
                listarEventos(eventos);
                pausar();
                break;
            }

            case 3:{
                printf("============================================\n");
                printf("           REMOÇÃO DE EVENTO                \n");
                printf("============================================\n");
                char repetir;
                repetir = 's';
                while(repetir == 's' || repetir == 'S'){
                    printf("Nome do evento a remover: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = 0;

                    removerEvento(&eventos, nome);

                    printf("\nDeseja remover outro evento?\n");
                    printf("Digite 's' para sim e 'n' para nao:");
                    scanf(" %c", &repetir);
                    getchar();
                }
                pausar();
                break;
            }

            case 4: {
                printf("============================================\n");
                printf("      CADASTRO DE ATIVIDADE EM EVENTO       \n");
                printf("============================================\n");
                char repetir;
                repetir = 's';
                while (repetir == 's' || repetir == 'S'){
                    printf("Nome do evento: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = 0;

                    Evento *e = buscarEvento(eventos, nome);
                    if (e == NULL) {
                        printf("Evento não encontrado.\n");
                        break;
                    }

                    printf("Título da atividade: ");
                    fgets(titulo, sizeof(titulo), stdin);
                    titulo[strcspn(titulo, "\n")] = 0;

                    printf("Horário (hh:mm): ");
                    fgets(horario, sizeof(horario), stdin);
                    horario[strcspn(horario, "\n")] = 0;

                    inserirAtividade(&e->atividades, criarAtividade(titulo, horario));
                    printf("\nDeseja cadastrar outra atividade?\n");
                    printf("Digite 's' para sim e 'n' para nao:");
                    scanf(" %c", &repetir);
                    getchar();
                }
                pausar();
                break;
            }

            case 5: {
                printf("============================================\n");
                printf("      LISTAGEM DE ATIVIDADES EM EVENTO      \n");
                printf("============================================\n");
                printf("Nome do evento: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                Evento *e = buscarEvento(eventos, nome);
                if (!e) {
                    printf("Evento não encontrado.\n");
                    pausar();
                    break;
                }

                subMenuListagemAtividades();
                int opcao;
                scanf("%d", &opcao);
                getchar(); // limpa o '\n'

                if (opcao == 1) {
                    listarAtividadesSemOrdenar(e->atividades);
                } else if (opcao == 2) {
                    listarAtividadesOrdenadas(e->atividades);
                } else {
                    printf("Opção inválida.\n");
                }
                pausar();
                break;
            }

            case 6: {
                printf("============================================\n");
                printf("      REMOÇÃO DE ATIVIDADE EM EVENTO        \n");
                printf("============================================\n");
                char repetir;
                repetir = 's';
                while(repetir == 's' || repetir == 'S'){
                    printf("Nome do evento: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = 0;

                    Evento *e = buscarEvento(eventos, nome);
                    if (e == NULL) {
                        printf("Evento não encontrado.\n");
                        break;
                    }

                    printf("Título da atividade a remover: ");
                    fgets(titulo, sizeof(titulo), stdin);
                    titulo[strcspn(titulo, "\n")] = 0;

                    removerAtividade(&e->atividades, titulo, pilhaAtividades);
                    printf("\nDeseja remover outra atividade?\n");
                    printf("Digite 's' para sim e 'n' para nao:");
                    scanf(" %c", &repetir);
                    getchar();
                }
                pausar();
                break;
            }

            case 7: {
                printf("============================================\n");
                printf("      CADASTRO DE PARTICIPANTE EM ATIVIDADE \n");
                printf("============================================\n");
                char repetir = 's';
                while (repetir == 's' || repetir == 'S'){
                    printf("Nome do evento: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = 0;

                    Evento *e = buscarEvento(eventos, nome);
                    if (!e) {
                        printf("Evento não encontrado.\n");
                        break;
                    }

                    printf("Título da atividade: ");
                    fgets(titulo, sizeof(titulo), stdin);
                    titulo[strcspn(titulo, "\n")] = 0;

                    Atividade *a = buscarAtividade(e->atividades, titulo);
                    if (!a) {
                        printf("Atividade não encontrada.\n");
                        break;
                    }

                    printf("Nome do participante: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = 0;

                    printf("Matrícula: ");
                    fgets(matricula, sizeof(matricula), stdin);
                    matricula[strcspn(matricula, "\n")] = 0;

                    printf("Email: ");
                    fgets(email, sizeof(email), stdin);
                    email[strcspn(email, "\n")] = 0;

                    Participante *p = criarParticipante(nome, matricula, email);
                    inserirParticipante(&a->participantes, p);
                    if (!p->registrado && !fila_contem_participante(filaChegada, matricula)) {
                        fila_inserir(filaChegada, p);
                        p->registrado = 1;  // Marca como já registrado
                    }

                    printf("\nDeseja cadastrar outro participante?\n");
                    printf("Digite 's' para sim e 'n' para nao:");
                    scanf(" %c", &repetir);
                    getchar();
                }
                pausar();
                break;
            }

            case 8: {
                printf("============================================\n");
                printf("      LISTAGEM DE PARTICIPANTES             \n");
                printf("============================================\n");
                printf("Nome do evento: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                Evento *e = buscarEvento(eventos, nome);
                if (!e) {
                    printf("Evento não encontrado.\n");
                    pausar();
                    break;
                }
                printf("Título da atividade: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0;

                Atividade *a = buscarAtividade(e->atividades, titulo);
                if (!a) {
                    printf("Atividade não encontrada.\n");
                    pausar();
                    break;
                }

                subMenuListagemParticipantes();
                int opcao;
                scanf("%d", &opcao);
                getchar(); // Limpa o \n do buffer

                if (opcao == 1) {
                    listarParticipantes(&a->participantes);
                } else if (opcao == 2) {
                    listarParticipantesOrdenado(&a->participantes);
                } else {
                    printf("Opção inválida.\n");
                }
                pausar();
                break;
            }

            case 9: {
                printf("============================================\n");
                printf("      REMOÇÃO DE PARTICIPANTE               \n");
                printf("============================================\n");
                char repetir = 's';
                while (repetir == 's' || repetir == 'S'){
                    printf("Nome do evento: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = 0;

                    Evento *e = buscarEvento(eventos, nome);
                    if (!e) {
                        printf("Evento não encontrado.\n");
                        break;
                    }

                    printf("Título da atividade: ");
                    fgets(titulo, sizeof(titulo), stdin);
                    titulo[strcspn(titulo, "\n")] = 0;

                    Atividade *a = buscarAtividade(e->atividades, titulo);
                    if (!a) {
                        printf("Atividade não encontrada.\n");
                        break;
                    }

                    printf("Matrícula do participante a remover: ");
                    fgets(matricula, sizeof(matricula), stdin);
                    matricula[strcspn(matricula, "\n")] = 0;

                    removerParticipante(&a->participantes, matricula, pilhaParticipantes);
                    printf("\nDeseja remover outro participante?\n");
                    printf("Digite 's' para sim e 'n' para nao:");
                    scanf(" %c", &repetir);
                    getchar();
                }
                pausar();
                break;
            }

            case 10: {
                printf("============================================\n");
                printf("      DESFAZER REMOÇÃO DE ATIVIDADE         \n");
                printf("============================================\n");
                printf("Nome do evento: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                Evento *e = buscarEvento(eventos, nome);
                if (!e) {
                    printf("Evento não encontrado.\n");
                    pausar();
                    break;
                }

                desfazerRemocaoAtividade(pilhaAtividades, &e->atividades);
                pausar();
                break;
            }

            case 11: {
                printf("============================================\n");
                printf("      DESFAZER REMOÇÃO DE PARTICIPANTE      \n");
                printf("============================================\n");
                printf("Nome do evento: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                Evento *e = buscarEvento(eventos, nome);
                if (!e) {
                    printf("Evento não encontrado.\n");
                    pausar();
                    break;
                }

                printf("Título da atividade: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0;

                Atividade *a = buscarAtividade(e->atividades, titulo);
                if (!a) {
                    printf("Atividade não encontrada.\n");
                    pausar();
                    break;
                }

                desfazerRemocaoParticipante(pilhaParticipantes, &a->participantes);
                pausar();
                break;
            }
            
            case 12: {
                printf("============================================\n");
                printf("      LISTAGEM DE ORDEM DE CHEGADA          \n");
                printf("============================================\n");
                fila_imprimir(filaChegada);
                pausar();
                break;
            }

            case 13: {
                credenciar_participantes(filaChegada);
                pausar();
                break;
            }

            case 0: {
                printf("============================================\n");
                printf("          ENCERRANDO O SISTEMA              \n");
                printf("============================================\n");
                printf("Salvando e liberando recursos...\n");
                liberarEventos(&eventos);
                pilha_libera(pilhaAtividades);
                pilha_libera(pilhaParticipantes);
                fila_libera(filaChegada);
                printf("Sistema encerrado com sucesso!\n");
                pausar();
                break;
            }

            default:
                printf("⚠️  Opção inválida! Tente novamente.\n");
                pausar();
        }

    } while (opcao != 0);

    return 0;
}
