#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#endif

#include "dados_usuario.h"
#include "cadastro.h"
#include "rede_amizade.h"
#include "postagem.h"
#include "historico.h"
#include "sugeridos.h"
#include "backup.h"

#define BRAT_GREEN       "\033[38;2;138;226;52m"  
#define CONFESSIONS_PINK "\033[38;2;255;0;128m"  
#define DARK_GRAY        "\033[38;2;100;100;100m"
#define RESET      "\033[0m"
#define BOLD             "\033[1m"
#define ITALIC           "\033[3m"



void exibir_menu() {
    static int primeira_vez = 1;

    if (primeira_vez) {
        for (int i = 0; i < 3; i++) {
            printf("\033[2J\033[H"); 
            
            printf("\n");
            printf(BRAT_GREEN);
            printf("🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\n");
            printf("   ______                    ____                            _                          \n");
            printf("  / ____/   ____    ____    / __/   ___   _____   _____     (_)   ____    ____   _____   \n");
            printf(" / /       / __ \\  / __ \\  / /_    / _ \\ / ___/  / ___/    / /   / __ \\  / __ \\ / ___/   \n");
            printf("/ /___    / /_/ / / / / / / __/   /  __/ (__  )  (__  )   / /   / /_/ / / / / / (__  )   \n");
            printf("\\____/    \\____/ /_/ /_/ /_/      \\___/  /____/  /____/  /_/    \\____/ /_/ /_/  /____/  \n");
            printf("🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\n");
            printf(RESET);
            
            Sleep(300); 
            printf("\033[2J\033[H");
            
            printf("\n");
            printf(CONFESSIONS_PINK);
            printf("🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\n");
            printf("   ______                    ____                            _                          \n");
            printf("  / ____/   ____    ____    / __/   ___   _____   _____     (_)   ____    ____   _____   \n");
            printf(" / /       / __ \\  / __ \\  / /_    / _ \\ / ___/  / ___/    / /   / __ \\  / __ \\ / ___/   \n");
            printf("/ /___    / /_/ / / / / / / __/   /  __/ (__  )  (__  )   / /   / /_/ / / / / / (__  )   \n");
            printf("\\____/    \\____/ /_/ /_/ /_/      \\___/  /____/  /____/  /_/    \\____/ /_/ /_/  /____/  \n");
            printf("🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\n");
            printf(RESET);
            
            Sleep(300); 
        }
        primeira_vez = 0; 
        printf("\033[2J\033[H"); 
    }

    printf(BRAT_GREEN "🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\n" RESET);
    printf("%s", CONFESSIONS_PINK);
    printf("   ______                    ____                            _                          \n");
    printf("  / ____/   ____    ____    / __/   ___   _____   _____     (_)   ____    ____   _____   \n");
    printf(" / /       / __ \\  / __ \\  / /_    / _ \\ / ___/  / ___/    / /   / __ \\  / __ \\ / ___/   \n");
    printf("/ /___    / /_/ / / / / / / __/   /  __/ (__  )  (__  )   / /   / /_/ / / / / / (__  )   \n");
    printf("\\____/    \\____/ /_/ /_/ /_/      \\___/  /____/  /____/  /_/    \\____/ /_/ /_/  /____/  \n");
    printf("%s", RESET);
    printf("  %s%sCome on, meet me on the dance floor%s\n", BRAT_GREEN, ITALIC, RESET);
    printf("\n");
    printf(BRAT_GREEN "🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\n" RESET);
    printf("%s----------------------------------------------------------%s\n\n", DARK_GRAY, RESET);
    printf("\n");
    printf("\n");
      printf("%s", CONFESSIONS_PINK);
    printf("  [1] Join in the vip list (cadastrar novo usuario) 👤\n");
    printf("  [2] Who's on the dancefloor? (buscar usuario) 🔍\n");
    printf("  [3] Let's party (adicionar amizade) 👯\n");
    printf("  [4] Hung up (remover amizade) 💔\n");
    printf("  [5] Danceteria (exibir amigos) 💅\n");
    printf("  [6] The Rythm (verificar amizades) 🎧\n");
    printf("  [7] Club classics (sugestoes de amizades) 🟢\n");
    printf("  [8] Make a new confession (nova publicacao) 💿\n");
    printf("  [9] Get on the floor (exibir publicacoes) 🍸\n");
    printf(" [10] What happened last night? (historico) 🕶️\n");
    printf("  [0] Get in the car (salvar e sair) 🚗💨\n");
    printf("%s", RESET);
    printf(BRAT_GREEN "====================================================\n" RESET);
    printf(CONFESSIONS_PINK "Choose your track: " RESET);
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar_e_limpar() {
    printf(BRAT_GREEN "\n[Pressione ENTER para voltar ao menu...]" RESET);
    limpar_buffer();
    system("cls");
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif

    SistemaCadastro* sis = inicializar_cadastro();
    Grafo* g = inicializar_grafo();
    PilhaHistorico* pi = inicializar_historico();

    char buffer_hist[256];
    carregar_backup(sis, g, pi);
    
    int opcao;
    system("cls");

    do {
        exibir_menu();

        if (scanf("%d", &opcao) != 1) {
            printf(" ❌ Entrada inválida.\n");
            limpar_buffer();
            system("cls");
            continue;
        }
        limpar_buffer();
        system("cls");

    
        switch (opcao) {
           case 1: {
                int id;
                char nome[MAX_NOME];
                char login[MAX_LOGIN];

                printf(BRAT_GREEN "\n--- VIP LIST: NOVO CADASTRO ---\n" RESET);
                
                printf("ID do clubber (numero unico): ");
                if (scanf("%d", &id) != 1) {
                    printf(" ❌ Entrada invalida.\n");
                    limpar_buffer();
                    break;
                }
                limpar_buffer();

                printf("Login (@usuario): ");
                fgets(login, MAX_LOGIN, stdin);
                login[strcspn(login, "\n")] = 0;

                printf("Nome completo: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;

                int resultado = cadastrar_usuario(sis, id, nome, login);

                if (resultado == 1) {
                    Usuario* u = buscar_por_id(sis, id);
                    if (u != NULL) {
                        adicionar_usuario_grafo(g, u);
                    }
                    printf(CONFESSIONS_PINK " 🪩 Bem-vindo à pista, %s! VIP list atualizada.\n" RESET, nome);
                    
                    sprintf(buffer_hist, "Novo clubber na VIP list: %s (ID: %d)", nome, id);
                    registrar_atividade(pi, buffer_hist);
                } 
                else if (resultado == 0) {
                    printf("\033[38;2;255;0;128m ❌ VIP Negado: Ja existe um clubber com o ID %d na pista, tente novamente!\n" RESET, id);
                } 
                else if (resultado == -1) {
                    printf("\033[38;2;255;0;128m ❌ Quem chega cedo aproveita mais: O login '%s' ja esta sendo usado por outro clubber!\n" RESET, login);
                } 
                else if (resultado == -2) {
                    printf("\033[38;2;255;0;128m ❌ Gêmeas? : O nome '%s' ja esta cadastrado no vip!\n" RESET, nome);
                }
                pausar_e_limpar();
                break;
            }
           case 2: {
                printf(BRAT_GREEN "\n--- WHO'S ON THE DANCEFLOOR? (BUSCAR POR NOME) ---\n" RESET);
                printf("Digite o nome completo do clubber: ");
                
                char nome_busca[MAX_NOME];
                fgets(nome_busca, MAX_NOME, stdin);
                nome_busca[strcspn(nome_busca, "\n")] = 0;

                Usuario* encontrado = buscar_por_nome(sis, nome_busca);

                if (encontrado != NULL) {
                    printf(CONFESSIONS_PINK "\n 🪩 Clubber encontrado na pista!\n" RESET);
                    printf(" ID: %d\n", encontrado->id);
                    printf(" Nome: %s\n", encontrado->nome);
                    printf(" Login: @%s\n", encontrado->login);
                } else {
                    printf("\033[38;2;255;0;128m ❌ Ninguem chamado '%s' foi encontrado na festa...\n" RESET, nome_busca);
                }
                pausar_e_limpar();
                break;
            }
            case 3: {
                int id1, id2;
                printf(BRAT_GREEN "\n--- PARTY 4 U ---\n" RESET);
                
                printf("Digite o ID do primeiro clubber: ");
                if (scanf("%d", &id1) != 1) {
                    printf(" ❌ Entrada inválida.\n");
                    limpar_buffer();
                    break;
                }
                limpar_buffer();

                printf("Digite o ID do segundo clubber: ");
                if (scanf("%d", &id2) != 1) {
                    printf(" ❌ Entrada inválida.\n");
                    limpar_buffer();
                    break;
                }
                limpar_buffer();

                Usuario* u1 = buscar_por_id(sis, id1);
                Usuario* u2 = buscar_por_id(sis, id2);

                if (u1 == NULL || u2 == NULL) {
                    printf("\033[38;2;255;0;128m ❌ Um ou ambos os IDs não foram estão na pista!\n" RESET);
                    break;
                }

                if (adicionar_amizade(g, id1, id2)) {
                    printf(CONFESSIONS_PINK " 👯 %s e %s are now celebrating together!.\n" RESET, u1->nome, u2->nome);
                    
                    sprintf(buffer_hist, "Nova amizade na pista: %s & %s", u1->nome, u2->nome);
                    registrar_atividade(pi, buffer_hist);
                } else {
                    printf("\033[38;2;255;0;128m ❌ Erro: Esses clubbers já são amigos ou ocorreu uma falha na conexao.\n" RESET);
                }
                pausar_e_limpar();
                break;
            }

            case 4: {
                int id1, id2;
                printf(BRAT_GREEN "\n--- HUNG UP (REMOVER AMIZADE) ---\n" RESET);
                
                printf("Digite o ID do primeiro clubber: ");
                if (scanf("%d", &id1) != 1) {
                    printf(" ❌ Entrada inválida.\n");
                    limpar_buffer();
                    break;
                }
                limpar_buffer();

                printf("Digite o ID do segundo clubber: ");
                if (scanf("%d", &id2) != 1) {
                    printf(" ❌ Entrada inválida.\n");
                    limpar_buffer();
                    break;
                }
                limpar_buffer();

                Usuario* u1 = buscar_por_id(sis, id1);
                Usuario* u2 = buscar_por_id(sis, id2);

                if (u1 == NULL || u2 == NULL) {
                    printf("\033[38;2;255;0;128m ❌ Um ou ambos os IDs não estão na pista!\n" RESET);
                    break;
                }

                if (remover_amizade(g, id1, id2)) {
                    printf(CONFESSIONS_PINK " 💔 Time goes by so slowly... Amizade desfeita entre %s e %s..\n" RESET, u1->nome, u2->nome);
                    
                    sprintf(buffer_hist, " %s deu unfollow em %s", u1->nome, u2->nome);
                    registrar_atividade(pi, buffer_hist);
                } else {
                    printf("\033[38;2;255;0;128m ❌ Erro: Eles não eram amigos.\n" RESET);
                }
                pausar_e_limpar();
                break;
            }

            case 5: {
                int id;
                printf(BRAT_GREEN "\n--- DANCETERIA---\n" RESET);
                printf("Digite o ID: ");
                scanf("%d", &id);
                limpar_buffer();
                exibir_amigos(g, id);
                pausar_e_limpar();
                break;
            }
            case 6: {
                int id1, id2;
                printf(BRAT_GREEN "\n--- THE RYTHM ---\n" RESET);
                printf("ID 1: ");
                scanf("%d", &id1);
                printf("ID 2: ");
                scanf("%d", &id2);
                limpar_buffer();

                if (verificar_amizade_direta(g, id1, id2)) {
                    printf(CONFESSIONS_PINK " ✨ São amigos! E estão curtindo o mesmo set.\n" RESET);
                } else {
                    printf(" ❌ Não são amigos. Por enquanto dançam em pistas diferentes.\n");
                }
                pausar_e_limpar();
                break;
            }
            case 7: {
                int id;
                printf(BRAT_GREEN "\n--- CLUB CLASSICS (Usuários Sugeridos) ---\n" RESET);
                printf("Digite o seu ID para ver quem mais esta na sua vibe: ");
                scanf("%d", &id);
                limpar_buffer();
                sugerir_amizades(g, id);
                pausar_e_limpar();
                break;
            }
            case 8: {
                int id;
                char texto[MAX_TEXTO];
                printf(BRAT_GREEN "\n--- CONFESS YOUR SINS ---\n" RESET);
                printf("ID do autor: ");
                scanf("%d", &id);
                limpar_buffer();

                Usuario* u = buscar_por_id(sis, id);
                if (u == NULL) {
                    printf(" ❌ Erro: Clubber não encontrado.\n");
                } else {
                    int is_after = 0;
                    printf(CONFESSIONS_PINK "Essa confissão é para a pista principal ou para o AFTER? (0 = Principal, 1 = After): " RESET);
                    scanf("%d", &is_after);
                    limpar_buffer();

                    printf(BRAT_GREEN "O que voce quer confessar, %s? (Max 280 chars): \n> " RESET, u->nome);
                    fgets(texto, MAX_TEXTO, stdin);
                    texto[strcspn(texto, "\n")] = 0;

                    if (adicionar_publicacao(u->publicacoes, texto, is_after)) {
                        if (is_after) {
                            printf("\033[38;2;226;255;0m 🌙 Confissão mandada pro AFTER! (Vai sumir ao amanhecer)\n" RESET);
                        } else {
                            printf(CONFESSIONS_PINK " 💿 Confissão jogada na pista!\n" RESET);
                        }
                        
                        sprintf(buffer_hist, "Nova confissão de %s (ID: %d)", u->nome, u->id);
                        registrar_atividade(pi, buffer_hist);
                    }
                }
                pausar_e_limpar();
                break;
            }
            case 9: {
                int id;
                printf(BRAT_GREEN "\n--- THE FLOOR (POSTS) ---\n" RESET);
                printf("ID do clubber: ");
                scanf("%d", &id);
                limpar_buffer();
                
                Usuario* u = buscar_por_id(sis, id);
                if (u == NULL) {
                    printf(" ❌ Erro: Clubber não encontrado.\n");
                } else {
                    exibir_publicacoes(u->publicacoes);
                }
                pausar_e_limpar();
                break;
            }
            case 10: {
                exibir_historico(pi);
                pausar_e_limpar();
                break;
            }
            case 0:
                printf(BRAT_GREEN "\n Chamando o uber... 🚗💨\n" RESET);
                salvar_backup(sis, g, pi);
                break;
            default:
                printf(" ❌ Escolha uma opção válida.\n");
                pausar_e_limpar();
            }
        system("cls");
    

    } while (opcao != 0);

    liberar_grafo(g);
    liberar_cadastro(sis);
    liberar_historico(pi);

    printf(CONFESSIONS_PINK " See you on the dancefloor. 👋\n" RESET);
    Sleep(250); 
    return 0;
}