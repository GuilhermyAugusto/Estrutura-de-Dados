#ifndef POSTAGEM_H
#define POSTAGEM_H

#include "dados_usuario.h"

#define MAX_TEXTO 280

typedef struct no_publi {
    char texto[MAX_TEXTO];
    int is_after;            
    struct no_publi* prox;
} NoPubli;

struct lista_publi {
    NoPubli* inicio;
    int qtd;
};

ListaPubli* inicializar_publicacoes();
int adicionar_publicacao(ListaPubli* lista, const char* texto, int is_after);
void exibir_publicacoes(ListaPubli* lista);
void liberar_publicacoes(ListaPubli* lista);

#endif