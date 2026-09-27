#ifndef REDE_AMIZADE_H
#define REDE_AMIZADE_H

#include "dados_usuario.h"

typedef struct no_vertice NoVertice;
typedef struct no_aresta NoAresta;
typedef struct grafo Grafo;

struct no_aresta {
    NoVertice* vizinho;      
    struct no_aresta* prox;  
};
struct no_vertice {
    Usuario* user;            
    NoAresta* amizades;       
    struct no_vertice* prox;  
};
struct grafo {
    NoVertice* primeiro_vertice;
    int num_vertices;
};

Grafo* inicializar_grafo();
int adicionar_usuario_grafo(Grafo* g, Usuario* user);
int adicionar_amizade(Grafo* g, int id1, int id2);
int remover_amizade(Grafo* g, int id1, int id2);
int verificar_amizade_direta(Grafo* g, int id1, int id2);
void exibir_amigos(Grafo* g, int id);
void liberar_grafo(Grafo* g);

NoVertice* buscar_vertice(Grafo* g, int id);

#endif