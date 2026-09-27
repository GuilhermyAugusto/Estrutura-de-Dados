#include <stdio.h>
#include <stdlib.h>
#include "rede_amizade.h"


Grafo* inicializar_grafo() {
    Grafo* g = (Grafo*) malloc(sizeof(Grafo));
    if (g != NULL) {
        g->primeiro_vertice = NULL;
        g->num_vertices = 0;
    }
    return g;
}


int adicionar_usuario_grafo(Grafo* g, Usuario* user) {
    if (g == NULL || user == NULL) return 0;

    NoVertice* novo = (NoVertice*) malloc(sizeof(NoVertice));
    if (novo == NULL) return 0;

    novo->user = user;
    novo->amizades = NULL;
    

    novo->prox = g->primeiro_vertice;
    g->primeiro_vertice = novo;
    g->num_vertices++;

    return 1;
}


NoVertice* buscar_vertice(Grafo* g, int id) {
    if (g == NULL) return NULL;

    NoVertice* atual = g->primeiro_vertice;
    while (atual != NULL) {
        if (atual->user->id == id) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

int verificar_amizade_direta(Grafo* g, int id1, int id2) {
    NoVertice* v1 = buscar_vertice(g, id1);
    if (v1 == NULL) return 0;

    NoAresta* atual = v1->amizades;
    while (atual != NULL) {
        if (atual->vizinho->user->id == id2) {
            return 1; 
        }
        atual = atual->prox;
    }
    return 0;
}


int ligar_vertices(NoVertice* v1, NoVertice* v2) {
    NoAresta* nova_aresta = (NoAresta*) malloc(sizeof(NoAresta));
    if (nova_aresta == NULL) return 0;

    nova_aresta->vizinho = v2;
    nova_aresta->prox = v1->amizades;
    v1->amizades = nova_aresta;
    return 1;
}

int adicionar_amizade(Grafo* g, int id1, int id2) {
    if (id1 == id2) {
        printf(" ❌ Erro: Uma festa sozinho pode não ser tão legal. Chame outra pessoa para te acompanhar.\n");
        return 0;
    }

    if (verificar_amizade_direta(g, id1, id2)) {
        printf(" ❌ Erro: Vocês já são amigos.\n");
        return 0;
    }

    NoVertice* v1 = buscar_vertice(g, id1);
    NoVertice* v2 = buscar_vertice(g, id2);

    if (v1 == NULL || v2 == NULL) {
        printf(" ❌ Erro: Clubber não está na festa.\n");
        return 0;
    }


    ligar_vertices(v1, v2);
    ligar_vertices(v2, v1);

    return 1;
}

void desligar_vertices(NoVertice* v1, NoVertice* v2) {
    NoAresta* atual = v1->amizades;
    NoAresta* ant = NULL;

    while (atual != NULL && atual->vizinho != v2) {
        ant = atual;
        atual = atual->prox;
    }

    if (atual != NULL) {
        if (ant == NULL) {
            v1->amizades = atual->prox; 
        } else {
            ant->prox = atual->prox;
        }
        free(atual);
    }
}

int remover_amizade(Grafo* g, int id1, int id2) {
    if (!verificar_amizade_direta(g, id1, id2)) {
        printf(" ❌ Erro: Vocês não são amigos. \n");
        return 0;
    }

    NoVertice* v1 = buscar_vertice(g, id1);
    NoVertice* v2 = buscar_vertice(g, id2);

    desligar_vertices(v1, v2);
    desligar_vertices(v2, v1);

    return 1;
}


void exibir_amigos(Grafo* g, int id) {
    NoVertice* v = buscar_vertice(g, id);
    if (v == NULL) {
        printf(" ❌ Erro: Clubber não encontrado.\n");
        return;
    }

    printf("\n=== AMIGOS DE %s (ID: %d) ===\n", v->user->nome, v->user->id);
    NoAresta* atual = v->amizades;
    
    if (atual == NULL) {
        printf(" 😪 Ainda não há ninguém aqui... Que tal adicionarmos alguns novos?\n");
    } else {
        while (atual != NULL) {
            printf(" -> %s (Login: @%s)\n", atual->vizinho->user->nome, atual->vizinho->user->login);
            atual = atual->prox;
        }
    }
    printf("===================================\n");
}

void liberar_grafo(Grafo* g) {
    if (g == NULL) return;

    NoVertice* v_atual = g->primeiro_vertice;
    while (v_atual != NULL) {
        NoAresta* a_atual = v_atual->amizades;
        while (a_atual != NULL) {
            NoAresta* a_temp = a_atual;
            a_atual = a_atual->prox;
            free(a_temp);
        }
        
        NoVertice* v_temp = v_atual;
        v_atual = v_atual->prox;
        free(v_temp);
    }
    
    free(g);
}