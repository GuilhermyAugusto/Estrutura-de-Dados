#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sugeridos.h"


typedef struct no_fila {
    NoVertice* vertice;
    int distancia;
    struct no_fila* prox;
} NoFila;

typedef struct {
    NoFila* inicio;
    NoFila* final;
} FilaBFS;

FilaBFS* inicializar_fila() {
    FilaBFS* f = (FilaBFS*) malloc(sizeof(FilaBFS));
    if (f != NULL) {
        f->inicio = NULL;
        f->final = NULL;
    }
    return f;
}

void enfileirar(FilaBFS* f, NoVertice* v, int dist) {
    if (f == NULL || v == NULL) return;
    
    NoFila* novo = (NoFila*) malloc(sizeof(NoFila));
    if (novo == NULL) return;
    
    novo->vertice = v;
    novo->distancia = dist;
    novo->prox = NULL;
    
    if (f->inicio == NULL) {
        f->inicio = novo;
    } else {
        f->final->prox = novo;
    }
    f->final = novo;
}

NoFila* desenfileirar(FilaBFS* f) {
    if (f == NULL || f->inicio == NULL) return NULL;
    
    NoFila* removido = f->inicio;
    f->inicio = f->inicio->prox;
    
    if (f->inicio == NULL) {
        f->final = NULL;
    }
    return removido;
}

void liberar_fila(FilaBFS* f) {
    while (f->inicio != NULL) {
        NoFila* temp = desenfileirar(f);
        free(temp);
    }
    free(f);
}


typedef struct {
    NoVertice* vertice;
    int amigos_comum;
} Sugestao;

void ordenar_sugestoes(Sugestao* array, int total) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            int trocar = 0;
            
            if (array[j].amigos_comum < array[j+1].amigos_comum) {
                trocar = 1;
            } 
            else if (array[j].amigos_comum == array[j+1].amigos_comum) {
                if (strcmp(array[j].vertice->user->nome, array[j+1].vertice->user->nome) > 0) {
                    trocar = 1;
                }
            }
            
            if (trocar) {
                Sugestao temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

void sugerir_amizades(Grafo* g, int id_alvo) {
    NoVertice* origem = buscar_vertice(g, id_alvo);
    if (origem == NULL) {
        printf(" ❌ Erro: Clubber não está na festa. \n");
        return;
    }

    int max_sugestoes = g->num_vertices;
    Sugestao* sugestoes = (Sugestao*) calloc(max_sugestoes, sizeof(Sugestao));
    int total_sugestoes = 0;

    FilaBFS* fila = inicializar_fila();
    enfileirar(fila, origem, 0);

    while (fila->inicio != NULL) {
        NoFila* atual = desenfileirar(fila);
        NoVertice* v_atual = atual->vertice;
        int dist_atual = atual->distancia;

        if (dist_atual < 2) {
            NoAresta* aresta = v_atual->amizades;
            while (aresta != NULL) {
                NoVertice* vizinho = aresta->vizinho;
                
                if (dist_atual == 0) {
                    enfileirar(fila, vizinho, 1);
                } 
                else if (dist_atual == 1) {
                    if (vizinho->user->id != origem->user->id && 
                        !verificar_amizade_direta(g, origem->user->id, vizinho->user->id)) {
                        
                        int encontrou = 0;
                        for (int i = 0; i < total_sugestoes; i++) {
                            if (sugestoes[i].vertice->user->id == vizinho->user->id) {
                                sugestoes[i].amigos_comum++;
                                encontrou = 1;
                                break;
                            }
                        }
                        if (!encontrou) {
                            sugestoes[total_sugestoes].vertice = vizinho;
                            sugestoes[total_sugestoes].amigos_comum = 1;
                            total_sugestoes++;
                        }
                    }
                }
                aresta = aresta->prox;
            }
        }
        free(atual);
    }
    
    liberar_fila(fila);

    printf("\n===  SUGESTÕES DE AMIZADES PARA %s ===\n", origem->user->nome);
    if (total_sugestoes == 0) {
        printf(" 😪 Não temos nenhuma sugestão no momento. Que tal procurar novos amigos no menu de buscas? \n");
    } else {
        ordenar_sugestoes(sugestoes, total_sugestoes);
        
        int exibir = (total_sugestoes > 3) ? 3 : total_sugestoes;
        for (int i = 0; i < exibir; i++) {
            printf("  %s (Login: @%s) - %d amigo(s) em comum\n", 
                   sugestoes[i].vertice->user->nome, 
                   sugestoes[i].vertice->user->login, 
                   sugestoes[i].amigos_comum);
        }
    }
    printf("=========================================\n");

    free(sugestoes);
}