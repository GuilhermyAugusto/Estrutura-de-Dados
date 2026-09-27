#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "historico.h"

#define BRAT_GREEN "\033[38;2;138;226;52m"
#define RESET "\033[0m"

PilhaHistorico* inicializar_historico() {
    PilhaHistorico* pi = (PilhaHistorico*) malloc(sizeof(PilhaHistorico));
    if (pi != NULL) {
        pi->qtd = 0;
    }
    return pi;
}

int registrar_atividade(PilhaHistorico* pi, const char* desc) {
    if (pi == NULL || desc == NULL) return 0;

    if (pi->qtd >= MAX_HISTORICO) {
        for (int i = 0; i < MAX_HISTORICO - 1; i++) {
            strcpy(pi->dados[i].descricao, pi->dados[i+1].descricao);
        }
        pi->qtd--; 
    }
    
    strncpy(pi->dados[pi->qtd].descricao, desc, TAM_DESC - 1);
    pi->dados[pi->qtd].descricao[TAM_DESC - 1] = '\0';
    pi->qtd++;
    
    return 1;
}

void exibir_historico(PilhaHistorico* pi) {
    if (pi == NULL || pi->qtd == 0) {
        printf("\n 🕶️ A noite acabou de começar... Nenhuma historia pra contar ainda.\n");
        return;
    }
    
    printf("\n" BRAT_GREEN "=== WHAT HAPPENED LAST NIGHT? (Historico: %d) ===" RESET "\n", pi->qtd);
    
    for (int i = pi->qtd - 1; i >= 0; i--) {
        printf(" -> %s\n", pi->dados[i].descricao);
    }
    
    printf(BRAT_GREEN "=================================================" RESET "\n");
}

void liberar_historico(PilhaHistorico* pi) {
    if (pi != NULL) {
        free(pi);
    }
}