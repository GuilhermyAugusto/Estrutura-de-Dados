#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "postagem.h"

#define AFTER_NEON "\033[38;2;226;255;0m" 
#define CONFESSIONS_PINK "\033[38;2;255;0;128m"
#define RESET "\033[0m"

ListaPubli* inicializar_publicacoes() {
    ListaPubli* lista = (ListaPubli*) malloc(sizeof(ListaPubli));
    if (lista != NULL) {
        lista->inicio = NULL;
        lista->qtd = 0;
    }
    return lista;
}

int adicionar_publicacao(ListaPubli* lista, const char* texto, int is_after) {
    if (lista == NULL || texto == NULL) return 0;

    NoPubli* novo = (NoPubli*) malloc(sizeof(NoPubli));
    if (novo == NULL) return 0;

    strncpy(novo->texto, texto, MAX_TEXTO - 1);
    novo->texto[MAX_TEXTO - 1] = '\0'; 
    novo->is_after = is_after; 

    novo->prox = lista->inicio;
    lista->inicio = novo;
    lista->qtd++;

    return 1;
}

void exibir_publicacoes(ListaPubli* lista) {
    if (lista == NULL || lista->inicio == NULL) {
        printf(" Pista vazia... Nenhuma publicacao encontrada. 🪩\n");
        return;
    }

    NoPubli* atual = lista->inicio;
    
    printf("\n" CONFESSIONS_PINK "=== THE FLOOR (PUBLICACOES: %d) ===" RESET "\n", lista->qtd);
    
    while (atual != NULL) {
        if (atual->is_after) {
            printf(AFTER_NEON " [AFTER 🌙] %s" RESET "\n", atual->texto);
        } else {
            printf(" [FLOOR 💿] %s\n", atual->texto);
        }
        atual = atual->prox;
    }
    printf(CONFESSIONS_PINK "=================================" RESET "\n");
}

void liberar_publicacoes(ListaPubli* lista) {
    if (lista == NULL) return;
    NoPubli* atual = lista->inicio;
    while (atual != NULL) {
        NoPubli* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(lista);
}