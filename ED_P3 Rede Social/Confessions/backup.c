#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backup.h"
#include "cadastro.h"
#include "rede_amizade.h"       
#include "postagem.h"
#include "historico.h"

int salvar_backup(SistemaCadastro* sis, Grafo* g, PilhaHistorico* pi) {
    FILE* f_users = fopen("dados/usuarios.txt", "w");
    if (f_users != NULL && sis != NULL) {
        for (int i = 0; i < TAM_HASH; i++) {
            NoHash* atual = sis->tabela[i];
            while (atual != NULL) {
                Usuario* u = atual->user;
                fprintf(f_users, "%d;%s;%s\n", u->id, u->nome, u->login);
                atual = atual->prox;
            }
        }
        fclose(f_users);
    }

    FILE* f_posts = fopen("dados/postagens.txt", "w");
    if (f_posts != NULL && sis != NULL) {
        for (int i = 0; i < TAM_HASH; i++) {
            NoHash* atual = sis->tabela[i];
            while (atual != NULL) {
                Usuario* u = atual->user;
                if (u->publicacoes != NULL) {
                    NoPubli* p = u->publicacoes->inicio;
                    while (p != NULL) {
                        if (p->is_after == 0) { 
                            fprintf(f_posts, "%d;%s\n", u->id, p->texto);
                        }
                        p = p->prox;
                    }
                }
                atual = atual->prox;
            }
        }
        fclose(f_posts);
    }

FILE* f_amiz = fopen("dados/amizades.txt", "w");
    if (f_amiz != NULL && g != NULL) {
        NoVertice* v_atual = g->primeiro_vertice;
        
        while (v_atual != NULL) {
            NoAresta* a_atual = v_atual->amizades;
            
            while (a_atual != NULL) {
                if (v_atual->user->id < a_atual->vizinho->user->id) {
                    fprintf(f_amiz, "%d;%d\n", v_atual->user->id, a_atual->vizinho->user->id);
                }
                a_atual = a_atual->prox;
            }
            v_atual = v_atual->prox;
        }
        fclose(f_amiz);
    }

    FILE* f_hist = fopen("dados/historico.txt", "w");
    if (f_hist != NULL && pi != NULL) {
        for (int i = 0; i < pi->qtd; i++) {
            fprintf(f_hist, "%s\n", pi->dados[i].descricao);
        }
        fclose(f_hist);
    }

    return 1;
}

int carregar_backup(SistemaCadastro* sis, Grafo* g, PilhaHistorico* pi) {
    char linha[512];

    FILE* f_users = fopen("dados/usuarios.txt", "r");
    if (f_users != NULL) {
        while (fgets(linha, sizeof(linha), f_users)) {
            linha[strcspn(linha, "\n")] = 0;
            
            int id;
            char nome[MAX_NOME], login[MAX_LOGIN];
            
            if (sscanf(linha, "%d;%[^;];%[^\n]", &id, nome, login) == 3) {
                if (cadastrar_usuario(sis, id, nome, login) == 1) {
                    Usuario* u = buscar_por_id(sis, id);
                    if (u != NULL && g != NULL) {
                        adicionar_usuario_grafo(g, u);
                    }
                }
            }
        }
        fclose(f_users);
    }

    FILE* f_amiz = fopen("dados/amizades.txt", "r");
    if (f_amiz != NULL) {
        while (fgets(linha, sizeof(linha), f_amiz)) {
            linha[strcspn(linha, "\n")] = 0;
            int id1, id2;
            if (sscanf(linha, "%d;%d", &id1, &id2) == 2) {
                adicionar_amizade(g, id1, id2);
            }
        }
        fclose(f_amiz);
    }

    FILE* f_posts = fopen("dados/postagens.txt", "r");
    if (f_posts != NULL) {
        while (fgets(linha, sizeof(linha), f_posts)) {
            linha[strcspn(linha, "\n")] = 0;
            int id;
            char texto[MAX_TEXTO];
            
            if (sscanf(linha, "%d;%[^\n]", &id, texto) == 2) {
                Usuario* u = buscar_por_id(sis, id);
                if (u != NULL && u->publicacoes != NULL) {
                    adicionar_publicacao(u->publicacoes, texto, 0); 
                }
            }
        }
        fclose(f_posts);
    }

    FILE* f_hist = fopen("dados/historico.txt", "r");
    if (f_hist != NULL && pi != NULL) {
        char descricao[TAM_DESC];
        while (fgets(linha, sizeof(linha), f_hist)) {
            linha[strcspn(linha, "\n")] = 0;
            if (strlen(linha) > 0) {
                strncpy(descricao, linha, TAM_DESC - 1);
                descricao[TAM_DESC - 1] = '\0';
                
                if (pi->qtd < MAX_HISTORICO) {
                    strcpy(pi->dados[pi->qtd].descricao, descricao);
                    pi->qtd++;
                }
            }
        }
        fclose(f_hist);
    }

    return 1;
}