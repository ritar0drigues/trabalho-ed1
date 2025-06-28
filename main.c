#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento.h"
#include "atividade.h"
#include "participante.h"
#include "ordenacao.h"
#include "pilha.h"

void menu() {
    printf("\n===== MENU PRINCIPAL =====\n");
    printf("1. Cadastrar evento\n");
    printf("2. Listar eventos\n");
    printf("3. Remover evento\n");
    printf("4. Cadastrar atividade em evento\n");
    printf("5. Listar atividades de um evento\n");
    printf("6. Remover atividade de um evento\n");
    printf("7. Cadastrar participante em uma atividade\n");
    printf("8. Listar participantes de uma atividade\n");
    printf("9. Remover participante de uma atividade\n");
    printf("10. Desfazer remoção de atividade\n");
    printf("11. Desfazer remoção de participante\n");
    printf("0. Sair\n");
    printf("==========================\n");
    printf("Escolha uma opção: ");
}
int main() {
    Evento *eventos = NULL;
    Pilha *pilhaAtividades = pilha_cria();
    Pilha *pilhaParticipantes = pilha_cria();

    int opcao;
    char nome[100], data[11], titulo[100], horario[6], matricula[20], email[100];

    do {
        menu();
        scanf("%d", &opcao);
        getchar(); // consumir '\n'

        switch(opcao) {
            case 1: {
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

                    if (e){
                        inserirEvento(&eventos, e);
                        printf("Evento cadastrado com sucesso!\n");
                    } else {
                        printf("Erro ao cadastrar evento!\n"); 
                    }

                    printf("\nDeseja cadastrar outro evento?\n");
                    printf("Digite 's' para sim e 'n' para nao:");
                    scanf(" %c", &repetir);
                    printf("O valor de repetir é: %c\n", repetir);
                    getchar();
                }
            
                break;
            }

            case 2:
                listarEventos(eventos);
                break;

            case 3:{
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
                break;
            }

            case 4: {
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
                getchar();}
                break;

            }

            case 5: {
                printf("Nome do evento: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                Evento *e = buscarEvento(eventos, nome);
                if (e) {
                    listarAtividades(e->atividades);
                } else {
                    printf("Evento não encontrado.\n");
                }
                break;
            }

            case 6: {
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
                getchar();}
                break;
            }

            case 7: {
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

                printf("\nDeseja cadastrar outro participante?\n");
                printf("Digite 's' para sim e 'n' para nao:");
                scanf(" %c", &repetir);
                getchar();}
                break;
            }

            case 8: {
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

                listarParticipantes(a->participantes);
                break;
            }

            case 9: {
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
                getchar();}
                break;
            }

            case 10: {
                printf("Nome do evento: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;

                Evento *e = buscarEvento(eventos, nome);
                if (!e) {
                    printf("Evento não encontrado.\n");
                    break;
                }

                desfazerRemocaoAtividade(pilhaAtividades, &e->atividades);
                break;
            }

            case 11: {
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

                desfazerRemocaoParticipante(pilhaParticipantes, &a->participantes);
                break;
            }

            case 0:
                printf("Encerrando o sistema...\n");
                liberarEventos(&eventos);
                pilha_libera(pilhaAtividades);
                pilha_libera(pilhaParticipantes);
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
